#include "behaviorgotostaticball.h"
#include <QDateTime>

BehaviorGoToStaticBall::BehaviorGoToStaticBall(WorldModel *wm, Knowledge *kn, QObject *parent)
    : Behavior(wm, kn, "BehaviorGoToStaticBall", parent)
{
    this->_state = GTSB_BEHINDBALL;
    this->_sgp = new SkillGotoPosition(wm, this);
}

bool BehaviorGoToStaticBall::execute(RobotCommand &rc)
{
    if (_wm->lastMode == Stop)
    {
        this->_state = GTSB_BEHINDBALL;
        //        qDebug() << "Reset!";
    }

    Position position;
    _state = getState(position);

    switch(_state)
    {
    case GTSB_BEHINDBALL:
        //        qDebug() << "BehindBall";
        _sgp->setPosition(position, 1);
        _sgp->setRID(rid());
        _sgp->setBallAsObstacle(true);
        return _sgp->execute(rc);
    case GTSB_MOVETOTURN:
        //        qDebug() << "MoveToTurn";
        _sgp->setPosition(position, 1);
        _sgp->setRID(rid());
        _sgp->setBallAsObstacle(true);
        return _sgp->execute(rc);
    case GTSB_WAIT:
        //        qDebug() << "Wait";
        _sgp->setPosition(position, 1);
        _sgp->setRID(rid());
        _sgp->setBallAsObstacle(true);
        return _sgp->execute(rc);
    case GTSB_STOP:
        //        qDebug() << "Stop";
        return false;
    }
}

GoToStaticBallState BehaviorGoToStaticBall::getState(Position &target)
{
    Vector2D ballPos = _wm->ball.pos.loc;
    Vector2D selfPos = _wm->ourRobot[_rid].pos.loc;

    Vector2D behindBallPos = ballPos - Vector2D::from_polar(ROBOT_RADIUS + BALL_RADIUS + 150, _bodyAngle * AngleDeg::RAD2DEG);
    Vector2D moveToTurnPos = ballPos - Vector2D::from_polar(ROBOT_RADIUS + BALL_RADIUS + 150, _bodyAngle * AngleDeg::RAD2DEG);

    switch(_state)
    {
    case GTSB_BEHINDBALL:
    {
        Line2D bodyLine (ballPos, _bodyAngle * AngleDeg::RAD2DEG);
        Line2D perpendicularBallLine = bodyLine.perpendicular(_wm->ball.pos.loc);

        //        qDebug() << "BehindBallPos to SelfPos : " << behindBallPos.dist(selfPos);

        float a0 = perpendicularBallLine.getA() * _wm->ourRobot[_rid].pos.loc.x
                + perpendicularBallLine.getB() * _wm->ourRobot[_rid].pos.loc.y
                + perpendicularBallLine.getC();

        float a1 = perpendicularBallLine.getA() * behindBallPos.x
                + perpendicularBallLine.getB() * behindBallPos.y
                + perpendicularBallLine.getC();

        if (a0 * a1 > 0 &&
                behindBallPos.dist(selfPos) < 50 &&
                bodyLine.dist(selfPos) < 20)
        {
            target.dir = _bodyAngle;
            target.loc = moveToTurnPos;
            return GTSB_MOVETOTURN;
        }
        else
        {
            target.dir = _bodyAngle;
            target.loc = behindBallPos;
            return GTSB_BEHINDBALL;
        }
    }
    case GTSB_MOVETOTURN:
    {
        Line2D bodyLine (ballPos, _bodyAngle * AngleDeg::RAD2DEG);

        //        qDebug() << _wm->ourRobot[_rid].pos.dir * AngleDeg::RAD2DEG << " : " << _bodyAngle * AngleDeg::RAD2DEG;
        //        qDebug() << moveToTurnPos.dist(selfPos);

        if (moveToTurnPos.dist(selfPos) < 40 &&
                bodyLine.dist(ballPos) < 10 &&
                (fabs(_bodyAngle - _wm->ourRobot[_rid].pos.dir) < M_PI / 36 ||
                 2 * M_PI - fabs(_bodyAngle - _wm->ourRobot[_rid].pos.dir) < M_PI / 36))
        {
            target.dir = _bodyAngle;
            target.loc = moveToTurnPos;
            _waitStart = QDateTime::currentDateTime().toTime_t();
            return GTSB_WAIT;
        }
        else
        {
            target.dir = _bodyAngle;
            target.loc = moveToTurnPos;
            return GTSB_MOVETOTURN;
        }
    }
    case GTSB_WAIT:
    {
        if (QDateTime::currentDateTime().toTime_t() - _waitStart >= 1)
        {
            return GTSB_STOP;
        }
        else
        {
            target.dir = _bodyAngle;
            target.loc = moveToTurnPos;
            return GTSB_WAIT;
        }
    }
    case GTSB_STOP:
    default:
    {
        return GTSB_STOP;
        break;
    }
    }
}
