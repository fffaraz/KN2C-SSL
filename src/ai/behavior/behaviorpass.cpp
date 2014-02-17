#include "behaviorpass.h"

#include "skill/skillkickball.h"

BehaviorPass::BehaviorPass(WorldModel *wm, Knowledge *kn, QObject *parent)
    : Behavior(wm, kn, "BehaviorPass", parent)
{
    this->_skb = new SkillKickBall(_wm, this);
}

bool BehaviorPass::execute(RobotCommand &rc)
{
    if (canPass(_receiver, _receiverAngle, _receiverRid))
    {
        Position pos;
        pos.loc = _receiver;
        pos.dir = _receiverAngle;

        if (pos.loc.dist(_wm->ball.pos.loc)
                < PASS_KICK_MAX_TRAVEL)
            this->_skb->setSpeedX(SHOOT_KICK_SPEED);
        else
            this->_skb->setSpeedX(PASS_KICK_SPEED);

        this->_skb->setRID(rid());
        this->_skb->setSpeedZ(0);
        this->_skb->setKickPosition(pos);
        this->_skb->execute(rc);

        return true;
    }

    return false;
}

bool BehaviorPass::canPass(Vector2D &target, float &targetAngle, int &targetId)
{
    int best_id = -1;
    float best_score = std::numeric_limits<float>::min();
    Vector2D best_point = Vector2D::INVALIDATED;

    for (int id = 0; id < PLAYERS_MAX_NUM; id ++)
    {
        if (!_wm->ourRobot[id].isValid) // not valid - rejected
            continue;

        if (id == _rid) // self - rejected
            continue;

        if (id == GOALIE_ID) // our goalie - rejected
            continue;

        if (_wm->ourRobot[id].pos.loc.x < -FIELD_MAX_X / 3) // too back - rejected
            continue;

        if (_wm->ourRobot[id].pos.loc.absX() > FIELD_MAX_X - ROBOT_RADIUS ||
                _wm->ourRobot[id].pos.loc.absY() > FIELD_MAX_Y - ROBOT_RADIUS) // out of pitch - rejected
            continue;

        if (_wm->ourRobot[id].pos.loc.dist(_wm->ball.pos.loc)
                > PASS_MAX_DIST) // too far - rejected
            continue;

        if (_wm->ourRobot[id].pos.loc.dist(_wm->ball.pos.loc)
                < PASS_MIN_DIST) // too near - rejected
            continue;

        float score = 0;
        bool safeArea = true;

        Vector2D rel = _wm->ourRobot[id].pos.loc - _wm->ball.pos.loc;
        double dist = rel.r();
        AngleDeg angle = rel.dir();

        Sector2D sector (_wm->ball.pos.loc, 0, dist, angle - 10, angle + 10);

        for (int opp = 0; opp < PLAYERS_MAX_NUM; opp ++)
        {
            if (!_wm->oppRobot[opp].isValid)
                continue;

            if (sector.contains(_wm->oppRobot[opp].pos.loc))
            {
                score -= 100;
                safeArea = false;
            }
        }

        if (safeArea)
            score += 200;

        if (score > best_score)
        {
            best_point.x = _wm->ourRobot[id].pos.loc.x;
            best_point.y = _wm->ourRobot[id].pos.loc.y;
            best_id = id;
            best_score = score;
        }
    }

    if (best_score > 0)
    {
        target.x = best_point.x;
        target.y = best_point.y;
        targetAngle = (target - _wm->ball.pos.loc).dir().radian();
        targetId = best_id;
        return true;
    }

    target = Vector2D::INVALIDATED;
    return false;
}

Vector2D BehaviorPass::receiver()
{
    return this->_receiver;
}

float BehaviorPass::receiverAngle()
{
    return this->_receiverAngle;
}

int BehaviorPass::receiverRid()
{
    return this->_receiverRid;
}
