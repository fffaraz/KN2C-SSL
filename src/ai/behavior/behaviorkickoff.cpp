#include "behaviorkickoff.h"

BehaviorKickoff::BehaviorKickoff(WorldModel* wm, Knowledge* kn ,QObject *parent) :
    Behavior(wm,kn,"BehaviorKickoff",parent)
{
    _our = true;
    _point = 0;
    _sgp = new SkillGotoPosition(wm,parent);
    _skb = new SkillKickBall(wm,parent);
}

bool BehaviorKickoff::execute(RobotCommand &rc)
{
    if (_our)
    {
        Position pos;
        Vector2D sol;
        switch (_point)
        {
        case 0:
            if (_wm->canKick())
            {
                if(_wm->ourRobot[_rid].pos.loc.dist(_wm->ball.pos.loc)>+ROBOT_RADIUS+20)
                {
                    Position pos;
                    pos.loc = Vector2D(-20,0);
                    pos.dir = (Vector2D(FIELD_MAX_X,0)-_wm->ourRobot[_rid].pos.loc).dir().radian();
                    _sgp->setRID(rid());
                    _sgp->setPosition(pos);
                    return _sgp->execute(rc);
                }
                else
                {
                    _skb->setRID(_rid);
                    _skb->setSpeedX(SHOOT_KICK_SPEED);
                    pos.dir = (Vector2D(FIELD_MAX_X,0)-_wm->ourRobot[_rid].pos.loc).dir().radian();
                    _skb->setKickPosition(pos);
                    return _skb->execute(rc);
                }
            }
            else
            {
                Line2D ballLine(_wm->ball.pos.loc,Vector2D(-FIELD_MAX_X,0));
                Line2D line1(Vector2D(-200-ROBOT_RADIUS,-FIELD_MAX_Y),Vector2D(-200-ROBOT_RADIUS,FIELD_MAX_Y));
                Vector2D sol = Vector2D::INVALIDATED;
                sol = line1.intersection(ballLine);
                if(!sol.isValid())
                {
                    sol.x = -200;
                    sol.y = 0;
                }
                Position pos;
                pos.loc = sol;
                pos.dir = (sol-Vector2D(FIELD_MAX_X,0)).dir().radian()+M_PI;
                _sgp->setRID(rid());
                _sgp->setPosition(pos);
                return _sgp->execute(rc);
            }
            break;
        case 1:
            sol.x = -200 ;
            sol.y = FIELD_MAX_Y - 500;
            pos.loc = sol;
            pos.dir = (sol-Vector2D(FIELD_MAX_X,0)).dir().radian()+M_PI;
            _sgp->setRID(rid());
            _sgp->setPosition(pos);
            return _sgp->execute(rc);
            break;
        default:
            sol.x = -200 ;
            sol.y = -FIELD_MAX_Y + 500;
            pos.loc = sol;
            pos.dir = (sol-Vector2D(FIELD_MAX_X,0)).dir().radian()+M_PI;
            _sgp->setRID(rid());
            _sgp->setPosition(pos);
            return _sgp->execute(rc);
            break;
        }
    }
    else
    {
        Line2D line(Vector2D(-200,-FIELD_MAX_Y),Vector2D(-200,FIELD_MAX_Y));
        if (_point==0)
        {
            Line2D ballLine(_wm->ball.pos.loc,Vector2D(-FIELD_MAX_X,0));
            Line2D line1(Vector2D(-500-ROBOT_RADIUS,-FIELD_MAX_Y),Vector2D(-500-ROBOT_RADIUS,FIELD_MAX_Y));
            Vector2D sol = Vector2D::INVALIDATED;
            sol = line1.intersection(ballLine);
            if(!sol.isValid())
            {
                sol.x = -500;
                sol.y = 0;
            }
            Position pos;
            pos.loc = sol;
            pos.dir = (sol-_wm->ball.pos.loc).dir().radian()+M_PI;
            _sgp->setRID(rid());
            _sgp->setPosition(pos);
            return _sgp->execute(rc);
        }
        else if (_point==1)
        {
            Rect2D oppRobot(Vector2D(0,FIELD_MAX_Y-1500),Size2D(800,1500));
            Vector2D sol = Vector2D::INVALIDATED;
            for (int i = 0 ; i < PLAYERS_MAX_NUM ; i++)
            {
                if (!_wm->oppRobot[i].isValid)
                    continue;
                if(oppRobot.contains(_wm->oppRobot[i].pos.loc))
                {
                    Line2D oppLine(_wm->oppRobot[i].pos.loc,Vector2D(-FIELD_MAX_X,0));
                    sol = line.intersection(oppLine);
                    break;
                }
            }
            if(!sol.isValid())
            {
                if (_kn->countActiveRoles()==4)
                {
                    sol.x = -FIELD_MAX_X + 1000;
                    sol.y = 0;
                }
                else
                {
                    sol.x = -200 ;
                    sol.y = FIELD_MAX_Y - 500;
                }
            }
            Position pos;
            pos.loc = sol;
            pos.dir = (sol-Vector2D(-FIELD_MAX_X,0)).dir().radian();
            _sgp->setRID(rid());
            _sgp->setPosition(pos);
            return _sgp->execute(rc);
        }
        else
        {
            Rect2D oppRobot(Vector2D(0,-FIELD_MAX_Y),Size2D(800,1500));
            Vector2D sol = Vector2D::INVALIDATED;
            for (int i = 0 ; i < PLAYERS_MAX_NUM ; i++)
            {
                if (!_wm->oppRobot[i].isValid)
                    continue;
                if(oppRobot.contains(_wm->oppRobot[i].pos.loc))
                {
                    Line2D oppLine(_wm->oppRobot[i].pos.loc,Vector2D(-FIELD_MAX_X,0));
                    sol = line.intersection(oppLine);
                    break;
                }
            }
            if(!sol.isValid())
            {
                sol.x = -200;
                sol.y = -FIELD_MAX_Y + 500;
            }
            Position pos;
            pos.loc = sol;
            pos.dir = (sol-Vector2D(-FIELD_MAX_X,0)).dir().radian();
            _sgp->setRID(rid());
            _sgp->setPosition(pos);
            return _sgp->execute(rc);
        }
    }
}
