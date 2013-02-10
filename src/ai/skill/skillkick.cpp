#include "skillkick.h"

SkillKick::SkillKick(WorldModel* wm, QObject *parent) :
    Skill(wm, "SkillKick", parent)
{
}

bool SkillKick::execute(RobotCommand &rc)
{
    if(_rid==-1) return false;

    Line2D l1(Vector2D(3025,0), _wm->ball.pos.loc);
    //Circle2D c1(_wm->ball.pos.loc, 10);
    Vector2D sol1, sol2, sol;
    //c1.intersection(l1, &sol1, &sol2);

    if((_wm->ball.pos.loc - _wm->ourRobot[_rid].pos.loc).length()>180)
    sol=(_wm->ball.pos.loc-Vector2D(3025,0)).setLengthVector(170)+_wm->ball.pos.loc;
    else
    sol=(_wm->ball.pos.loc-Vector2D(3025,0)).setLengthVector(80)+_wm->ball.pos.loc;

    //if((sol1-Vector2D(3025,0)).length2()>(sol2-Vector2D(3025,0)).length2())
     //   sol=sol1;
    //else
      //  sol=sol2;
    Position pos;
    pos.loc=sol;
    //
    pos.dir=(Vector2D(3025,0) - _wm->ball.pos.loc).dir().radian();
    rc.FinalPos=pos;
    rc.TargetPos=pos;
    double angle2 =  fabs((Vector2D(3025,0) - _wm->ball.pos.loc).dir().radian() - (_wm->ball.pos.loc-_wm->ourRobot[_rid].pos.loc).dir().radian());
    double angle =  fabs((Vector2D(3025,0) - _wm->ourRobot[_rid].pos.loc).dir().radian() - _wm->ourRobot[_rid].pos.dir);

    rc.Speed=1;

    if( (_wm->ball.pos.loc - _wm->ourRobot[_rid].pos.loc).length()<120 && (angle < (M_PI*7)/180 || (2*M_PI- angle<(M_PI*7)/180)) && (angle2<(M_PI*7)/180 || (2* M_PI-angle2)<(M_PI*7)/180))
    {
        rc.kickspeedx=5;
qDebug()<<"KICK000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    }
    return true;
}

bool SkillKick::SkillDone()
{
    return false;
}

void SkillKick::setTarget(const Vector2D &Target)
{
    _Target=Target;
}
