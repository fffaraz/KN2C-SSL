#include "behaviorstop.h"

BehaviorStop::BehaviorStop(WorldModel* wm, Knowledge *kn, QObject *parent) :
    Behavior(wm, kn, "BehaviorStop", parent)
{
    _sgp = new SkillGotoPosition(wm);
    _point = 1;
}

bool BehaviorStop::execute(RobotCommand &rc)
{
    Position pos;
    Vector2D sol;
    if(_kn->isInPenaltyArea(_wm->ball.pos.loc))
    {
        if (_point==1)
        {
            sol.x = -FIELD_MAX_X + PENALTY_AREA_RADIUS + 1000;
            sol.y = 0;
        }
        else if(_point==2)
        {
            sol.x = -FIELD_MAX_X + PENALTY_AREA_RADIUS + 1000;
            sol.y = 500;
        }
        else
        {
            sol.x = -FIELD_MAX_X + PENALTY_AREA_RADIUS + 1000;
            sol.y = -500;
        }
    }
    else
    {
        Circle2D ballArea(_wm->ball.pos.loc , 500+ROBOT_RADIUS);
        Line2D goalLine(_wm->ball.pos.loc , Vector2D(-FIELD_MAX_X,0));
        Vector2D sol1,sol2;
        ballArea.intersection(goalLine,&sol1,&sol2);
        if (!_kn->isInPenaltyArea(sol1))
        {
            if (!_kn->isInPenaltyArea(sol2))
                sol = (sol1.x < sol2.x) ? sol1 : sol2;
            else
                sol = sol1;
        }
        else
        {
            sol = sol2;
        }
        Circle2D robotArea(sol,2*ROBOT_RADIUS);
        ballArea.intersection(robotArea,&sol1,&sol2);
        if(_point==2)
            sol = sol1;
        else if (_point==3)
            sol = sol2;
    }
    pos.loc = sol;
    pos.dir = (sol-_wm->ball.pos.loc).dir().radian()+M_PI;
    _sgp->setRID(rid());
    _sgp->setPosition(pos);
    return _sgp->execute(rc);
}
