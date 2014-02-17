#include "behaviorpenalty.h"

#define _id 1
#define _behind_ball 130

BehaviorPenalty::BehaviorPenalty(WorldModel *wm, Knowledge *kn, QObject *parent)
    : Behavior(wm, kn, "BehaviorPass", parent)
{
    _sgp = new SkillGotoPosition(wm,this);
    _sta = new SkillTurnToAngle(wm,this);
    _skb = new SkillKickBall(wm,this);
}

bool BehaviorPenalty::execute(RobotCommand &rc)
{
    rc.kickspeedx=0;
    if(_wm->ourRobot[_id].isValid)
    {
        if(_rid==_id)
        {
            if((_wm->ourRobot[_rid].pos.loc-_wm->ball.pos.loc).length()>160)
                return GoBehindBall(rc);
            else
            {
                    if(_wm->canKick())
                    {
                        if((_wm->ourRobot[_rid].pos.loc-_wm->ball.pos.loc).length()>130)
                            return GoBehindBall2(rc);
                        return KickBall(rc);
                    }


            }
            return GoBehindBall(rc);
        }
        else
        {
            Position p;
            p.loc=Vector2D(FIELD_MAX_X/2.0,_rid*300-400);
            p.dir=(_wm->ourRobot[_rid].pos.loc - _wm->ball.pos.loc).dir().radian();
            _sgp->setPosition(p);
            _sgp->setRID(_rid);
            return _sgp->execute(rc);
        }
    }
    else
    {
        int nearestToBall = _kn->findNearestTeammateToPointByStaticPosition(
                    _wm->ball.pos.loc, DirectFreeKickOur);
        if(_rid==_kn->findNearestTeammateToPoint(_wm->ball.pos.loc))
        {

            if((_wm->ourRobot[_rid].pos.loc-_wm->ball.pos.loc).length()>160)
                return GoBehindBall(rc);
            else
            {
                    if(_wm->canKick())
                    {
                        if((_wm->ourRobot[_rid].pos.loc-_wm->ball.pos.loc).length()>130)
                            return GoBehindBall2(rc);
                        double angle3 = fabs((Vector2D(3025,250) - _wm->ourRobot[_rid].pos.loc).dir().radian());
                        double angle4 = fabs((Vector2D(3025,250) - _wm->ball.pos.loc).dir().radian());

                        if(fabs(angle4-angle3)>(M_PI*3)/180)
                             return TurnToGoalCorner(rc);
                        return KickBall(rc);
                    }


            }
            return GoBehindBall(rc);
        }
        else
        {
            Position p;
            p.loc=Vector2D(FIELD_MAX_X/2.0,_rid*300-400);
            p.dir=(_wm->ourRobot[_rid].pos.loc - _wm->ball.pos.loc).dir().radian();
            _sgp->setPosition(p);
            _sgp->setRID(_rid);
            return _sgp->execute(rc);
        }

    }

}
bool BehaviorPenalty::GoBehindBall(RobotCommand &rc)
{
//    qDebug()<<"GoBehindBall";
    Position p;
    p.dir=(Vector2D(FIELD_MAX_X,0) - _wm->ball.pos.loc).dir().radian();
    p.loc=Vector2D(_wm->ball.pos.loc.x-_behind_ball-25,_wm->ball.pos.loc.y);
    _sgp->setPosition(p);
    _sgp->setRID(_rid);
    return _sgp->execute(rc);
}

bool BehaviorPenalty::GoBehindBall2(RobotCommand &rc)
{
//    qDebug()<<"GoBehindBall";
    Position p;
    p.dir=(Vector2D(FIELD_MAX_X,0) - _wm->ball.pos.loc).dir().radian();
    p.loc=Vector2D(_wm->ball.pos.loc.x-_behind_ball,_wm->ball.pos.loc.y);
    _sgp->setPosition(p);
    _sgp->setRID(_rid);
    return _sgp->execute(rc);
}
bool BehaviorPenalty::TurnToGoalCorner(RobotCommand &rc)
{
//    qDebug()<<"TurnToGoalCorner";
    Position p;
    p.dir=(Vector2D(FIELD_MAX_X,250) - _wm->ball.pos.loc).dir().radian();
    p.loc=_wm->ball.pos.loc+Vector2D::from_polar(-_behind_ball+20,AngleDeg((Vector2D(FIELD_MAX_X,250) - _wm->ball.pos.loc).dir()));//Vector2D(_wm->ball.pos.loc.x-_behind_ball ,_wm->ball.pos.loc.y);
    _sgp->setPosition(p);
    _sgp->setRID(_rid);
    return _sgp->execute(rc);
}
bool BehaviorPenalty::KickBall(RobotCommand &rc)
{
//    qDebug()<<"kickball";
    Position p;
    p.dir=(Vector2D(FIELD_MAX_X,0) - _wm->ball.pos.loc).dir().radian();
    p.loc=_wm->ball.pos.loc+Vector2D::from_polar(-_behind_ball+25,AngleDeg((Vector2D(FIELD_MAX_X,0) - _wm->ball.pos.loc).dir()));//Vector2D(_wm->ball.pos.loc.x-_behind_ball ,_wm->ball.pos.loc.y);
    _sgp->setPosition(p);
    _sgp->setRID(_rid);
    //if((_wm->ball.pos.loc-_wm->ourRobot[_rid].pos.loc).length()>115)
    rc.kickspeedx=11;
    return _sgp->execute(rc);
    /*_skb->setKickPosition(p);
    _skb->setSpeedX(11);
    _skb->setSpeedZ(0);
    _skb->setRID(_rid);
    _skb->setKickPosition(p);
    return _skb->execute(rc);*/
}
