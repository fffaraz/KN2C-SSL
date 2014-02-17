#include "behaviorshoot.h"

BehaviorShoot::BehaviorShoot(WorldModel *wm, Knowledge *kn, QObject *parent)
    : Behavior(wm, kn, "BehaviorShoot", parent)
{
    this->_skb = new SkillKickBall(_wm, this);
}

bool BehaviorShoot::execute(RobotCommand &rc)
{
    if (canShoot(_target, _targetAngle))
    {
        Position pos;
        pos.loc = _target;
        pos.dir = _targetAngle;

        this->_skb->setRID(rid());
        this->_skb->setSpeedX(SHOOT_KICK_SPEED);
        this->_skb->setSpeedZ(0);
        this->_skb->setKickPosition(pos);
        this->_skb->execute(rc);

        return true;
    }

    return false;
}


bool BehaviorShoot::canShoot(Vector2D &target, float &targetAngle)
{
    Vector2D ball = _wm->ball.pos.loc;

    Vector2D goal_l (FIELD_MAX_X, -GOAL_HALF_LENGTH);
    Vector2D goal_r (FIELD_MAX_X, +GOAL_HALF_LENGTH);

//    if (ball.dist((goal_l + goal_r) / 2) > FIELD_MAX_X)
//    {
//        return false;
//    }

#if 1
    goal_l.y += 2 * BALL_RADIUS;
    goal_r.y -= 2 * BALL_RADIUS;
#else
    goal_l.y += std::min(ROBOT_RADIUS,
                         goal_l.dist(_wm->ball.pos.loc) * tan(M_PI / 36));

    goal_r.y -= std::min(ROBOT_RADIUS,
                         goal_l.dist(_wm->ball.pos.loc) * tan(M_PI / 36));
#endif

    int DIST_DIVS = 4;
    int dist_step = fabs(goal_r.y - goal_l.y) / (DIST_DIVS - 1) * -ball.signY();

    Vector2D shot_point = ball.signY() > 0 ? goal_r : goal_l;

    Vector2D best_point = Vector2D::INVALIDATED;
    float best_score = std::numeric_limits< float >::min();

    AngleDeg totalAngle = ((goal_r - ball).dir() - (goal_l - ball).dir()).abs();

#if 1
    for (int i = 0; i < DIST_DIVS; i ++, shot_point.y += dist_step)
    {
        // NOTE: NEIGHBOR SECTORS CHECK

        AngleDeg relAngle = (shot_point - ball).dir();
        Sector2D sector (ball, // center
                         0, ball.dist(shot_point), // min_r, max_r
                         relAngle - totalAngle / (DIST_DIVS - 1), // start angle
                         relAngle + totalAngle / (DIST_DIVS - 1)); // end angle

#if BEHAVIOR_DEBUG
        qDebug() << __FILE__ << " : " << __LINE__
                 << "sector { (" << sector.center().x << "," << sector.center().y << "), "
                 << sector.radiusMin() << ", " << sector.radiusMax() << ", "
                 << sector.angleLeftStart().degree() << "," << sector.angleRightEnd().degree();
#endif

        float score = 0;
        bool safeArea = true;
        for (int id = 0; id < PLAYERS_MAX_NUM; id ++)
        {
            if (!_wm->oppRobot[id].isValid)
                continue;

            if (sector.contains(_wm->oppRobot[id].pos.loc))
            {
                safeArea = false;
                score -= 1000;
            }
        }

        if (safeArea)
            score += 1000;

        if (score > best_score)
        {
            best_point.x = shot_point.x;
            best_point.y = shot_point.y;
            best_score = score;
        }
    }
#else

    for (int i = 0; i < DIST_DIVS; i ++, shot_point.y += dist_step)
    {
        int score = 0;

        double ball_reach_step
                = calc_length_geom_series(BALL_MAX_SPEED, ball.dist(shot_point), BALL_DECAY);

        if (ball_reach_step < 1.0)
        {
            target.x = shot_point.x;
            target.y = shot_point.y;
            return true;
        }

        //
        // Can ball reach to goal after four step ?
        //

        score += ball_reach_step < 2.0 ? (4 - ball_reach_step) * 1000 : 0;
        Segment2D ballSegment (ball, shot_point);

        bool bRobotOnRoute = true;
        for (int i = 0; i < PLAYERS_MAX_NUM; i ++)
        {
            if (!_wm->oppRobot[i].isValid)
                continue;

            // NOTE: _wm->oppRobot[i].pos.dir ???

            Vector2D opp = _wm->oppRobot[i].pos.loc;
            Line2D oppLine (opp, -ballSegment.direction());
            Vector2D intersect = ballSegment.intersection(oppLine);

            if (!intersect.isValid())
            {
                bRobotOnRoute = false;
                continue;
            }
            else
            {
                float ball_dist = ball.dist(intersect);
                float dist = intersect.dist(opp);

                float ball_reach_intersect_step = ball_dist / BALL_MAX_SPEED;
                float opp_reach_intersect_step = dist / PLAYER_MAX_SPEED;
                score += (opp_reach_intersect_step - ball_reach_intersect_step) * 10000;
            }
        }

        if (bRobotOnRoute)
        {
            score += 1000;
        }

        if (score >= 0 && best_score <= score)
        {
            best_score = score;
            best_point.x = shot_point.x;
            best_point.y = shot_point.y;
        }
    }
#endif

    if (best_score > 0)
    {
        target.x = best_point.x;
        target.y = best_point.y;
        targetAngle = (target - _wm->ball.pos.loc).dir().radian();
        return true;
    }
    else
    {
        return false;
    }
}
