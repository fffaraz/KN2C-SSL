#include "skillkickball.h"

SkillKickBall::SkillKickBall(WorldModel *wm, QObject *parent) :
    Skill(wm, "SkillKickBall", parent)
{
    this->_done = false;
}

bool SkillKickBall::execute(RobotCommand& rc)
{
    if (_wm->ball.pos.loc.dist(_wm->ourRobot[_rid].pos.loc) < BALL_RADIUS + ROBOT_RADIUS + 50)
    {
#if SKILL_DEBUG
        qDebug() << "Kick Ball";
#endif
        rc.kickspeedx = this->_speedX;
        rc.kickspeedz = this->_speedZ;
        rc.FinalPos = rc.TargetPos = _wm->ball.pos;
        rc.FinalPos.dir = rc.TargetPos.dir = _kickPos.dir;
        rc.Speed = 0.4;
        this->_done = true;
    }
    else
    {
#if SKILL_DEBUG
        qDebug() << "Move To Kick Ball";
#endif
        rc.kickspeedx = rc.kickspeedz = 0;
        rc.FinalPos.loc = rc.TargetPos.loc = _wm->ball.pos.loc;
        rc.FinalPos.dir = rc.TargetPos.dir = _kickPos.dir;
        rc.Speed = 0.7;
        this->_done = false;
    }

    return true;
}

bool SkillKickBall::done()
{
    return this->_done;
}
