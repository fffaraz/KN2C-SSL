#include "tacticstop.h"

TacticStop::TacticStop(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm, kn, "TacticStop", parent)
{
    _skillstop = new SkillGotoPosition(wm,this);
    _distance=0;
    _defence=0;
    _total_stop=0;
    _my_stop=0;
}

Skill* TacticStop::getSkill()
{
    Circle2D cir(_target, _distance);
    Line2D lin(_target, _defpoint);
    Vector2D sol,sol1,sol2;
    cir.intersection(lin, &sol1, &sol2);
    if(_defence)
        if( (sol1-_defpoint).length2() < (sol2-_defpoint).length2() )
            sol=sol1;
        else
            sol=sol2;
    else
        if( (sol1-_defpoint).length2() < (sol2-_defpoint).length2() )
            sol=sol2;
        else
            sol=sol1;

    Circle2D cir1(sol,2*ROBOT_RADIUS);
    cir.intersection(cir1,&sol1,&sol2);
    if(_my_stop == 2)
        sol = sol1;
    else if(_my_stop == 3)
        sol = sol2;

    Position pos;
    pos.loc = sol;
    pos.dir=(_target - _wm->ourRobot[_rid].pos.loc).dir().radian();

    _skillstop->setRID(_rid);
    _skillstop->setPosition(pos);
    return _skillstop;
}
