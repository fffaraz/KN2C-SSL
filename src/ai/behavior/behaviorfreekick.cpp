#include "behaviorfreekick.h"

#include <limits>
#include <QList>
#include <QDateTime>

BehaviorFreeKick::BehaviorFreeKick(WorldModel *wm, Knowledge *kn, QObject *parent, bool readSixFormation)
    :    Behavior(wm, kn, "BehaviorFreeKick", parent)
{
    this->_our = true;
    this->_direct = true;
    this->_behavior = DEFAULT;
    this->_sgp = new SkillGotoPosition(_wm, this);
    this->_skb = new SkillKickBall(_wm, this);
    this->_bp = new BehaviorPass(_wm, _kn, this);
    this->_bs = new BehaviorShoot(_wm, _kn, this);
    this->_bgtsb = new BehaviorGoToStaticBall(_wm, _kn, this);
    this->_readSixFormation = readSixFormation;
}

bool BehaviorFreeKick::execute(RobotCommand &rc)
{
    if (this->_our)
    {
        int nearestToBall = _kn->findNearestTeammateToPointByStaticPosition(
                    _wm->ball.pos.loc, DirectFreeKickOur);

        if (_index == nearestToBall)
        {
            return doKickOurFreeKick(rc);
        }
        else
        {
            return doMoveOurFreeKick(rc);
        }
    }
    else
    {
        return doMoveTheirFreeKick(rc);
    }

    return false;
}

bool BehaviorFreeKick::doKickOurFreeKick(RobotCommand &rc)
{
    this->_bgtsb->setRID(rid());
    this->_bgtsb->setIndex(index());
    this->_bgtsb->setBodyAngle(getKickPosition().dir);

    if (this->_bgtsb->execute(rc))
        return true;

    if (this->_bgtsb->state() == GTSB_WAIT)
        return false;

    rc.FinalPos = rc.TargetPos = _wm->ball.pos;
    rc.FinalPos.dir = rc.TargetPos.dir = getKickPosition().dir;
    rc.Speed = 0.4;
    rc.kickspeedx = SHOOT_KICK_SPEED;
    return true;
}

bool BehaviorFreeKick::doMoveOurFreeKick(RobotCommand &rc)
{
    Vector2D homePos = _wm->position(_index,
                                     _readSixFormation ? 6 : _kn->countActiveRoles(),
                                     _wm->ball.pos.loc, DirectFreeKickOur);

    Position pos;
    pos.dir = (Vector2D(FIELD_MAX_X, 0) - homePos).dir().radian();
    Circle2D penaltyArea(Vector2D(FIELD_MAX_X,0),200+ROBOT_RADIUS+PENALTY_AREA_RADIUS+PARALLEL_LINE_LENGTH/2);
    if (penaltyArea.contains(homePos))
    {
        Line2D line(penaltyArea.center(),homePos);
        Vector2D sol1,sol2;
        penaltyArea.intersection(line,&sol1,&sol2);
        if (sol1.x > FIELD_MAX_X)
            homePos = sol2;
        else
            homePos = sol1;
    }
    pos.loc = homePos;
    _sgp->setPosition(pos);
    _sgp->setRID(rid());
    _sgp->execute(rc);

    return true;
}

bool BehaviorFreeKick::doMoveTheirFreeKick(RobotCommand &rc)
{
    Position pos;
        Vector2D homePos = _wm->position(_index,
                                         _readSixFormation ? 6 : _kn->countActiveRoles(),
                                         _wm->ball.pos.loc, DirectFreeKickOpp);
        pos.dir = (Vector2D(FIELD_MAX_X, 0) - homePos).dir().radian();
        pos.loc = homePos;

//    if (_direct)
//    {
//        switch (_index)
//        {
//        case 3:
//            if (_wm->ball.pos.loc.y < 0)
//            {
//                Rect2D area(Vector2D(-FIELD_MAX_X,0),Size2D(FIELD_MAX_X,FIELD_MAX_Y));
//                double minDist = std::numeric_limits <double> :: max();
//                int index = -1;
//                for (int i = 0 ; i < PLAYERS_MAX_NUM ; i++)
//                {
//                    if (!_wm->oppRobot[i].isValid || !area.contains(_wm->ball.pos.loc))
//                        continue;
//                    if (Vector2D(-FIELD_MAX_X,0).dist(_wm->ball.pos.loc)<minDist)
//                    {
//                        minDist = Vector2D(-FIELD_MAX_X,0).dist(_wm->ball.pos.loc);
//                        index = i;
//                    }
//                }
//                if (index != -1)
//                {
//                    Vector2D vec = _wm->ourRobot[index].pos.loc;
//                    vec += Vector2D::from_polar(ROBOT_RADIUS,(Vector2D(-FIELD_MAX_X,0)-vec).dir());
//                    if (_kn->isInPenaltyArea(vec))
//                    {
//                        pos.loc = vec;
//                        pos.dir = (_wm->oppRobot[index].pos.loc - vec).dir().radian();
//                    }
//                }
//            }
//            else
//            {
//                Rect2D area(Vector2D(-FIELD_MAX_X,FIELD_MAX_Y),Size2D(FIELD_MAX_X,FIELD_MAX_Y));
//            }
//            break;
//        case 4:
//            break;
//        default :
//            break;
//        }

        _sgp->setPosition(pos);
        _sgp->setRID(rid());
        return _sgp->execute(rc);
//    }
//    else
//    {

//    }
}

Position BehaviorFreeKick::getKickPosition()
{
    Position pos;

    if (this->_direct)
    {
        this->_bs->setRID(rid());
        this->_bs->setIndex(index());

        if (this->_bs->canShoot(pos.loc, pos.dir))
        {
            this->_behavior = SHOOT;
            return pos;
        }
    }

#if 0
    this->_bp->setRID(rid());
    this->_bp->setIndex(index());

    int targetId;
    if (this->_bp->canPass(pos.loc, pos.dir, targetId))
    {
        this->_behavior = PASS;
        return pos;
    }
#endif

    pos.dir = (Vector2D(FIELD_MAX_X, 0) - _wm->ball.pos.loc).dir().radian();
    pos.loc = Vector2D(FIELD_MAX_X, 0);
    this->_behavior = DEFAULT;
    return pos;
}
