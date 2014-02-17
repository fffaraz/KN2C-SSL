#include "tacticcenterback.h"

TacticCenterBack::TacticCenterBack(WorldModel *wm, Knowledge *kn, QObject *parent):
    Tactic(wm,kn,"TacticCenterBack",parent)
{
    _avoidance = false;
    _index = 1;
    _sgp = new SkillGotoPosition(wm,this);
    _skb = new SkillKickBall(wm,this);
    _bfk = new BehaviorFreeKick(wm, kn, this,false);
    _bk = new BehaviorKickoff(wm, kn, this);
    _bp = new BehaviorPenalty(wm,kn,this);
}

//bool TacticCenterBack::execute(RobotCommand &rc)
//{
//    return doMove(rc);

//    if (_kn->isBallKickable(_rid) ||
//            _kn->ballKicker() == _rid ||
//            _kn->findNearestTeammateToPoint(_wm->ball.pos.loc) == _rid)
//    {
//#if TACTIC_DEBUG
//        qDebug() << "CenterBack(" << _rid << ") in Kick Mode";
//#endif
//        return doKick(rc);
//    }
//    else
//    {
//#if TACTIC_DEBUG
//        qDebug() << "CenterBack(" << _rid << ") in Move Mode";
//#endif
//        return doMove(rc);
//    }
//}

bool TacticCenterBack::doPlayOn(RobotCommand &rc)
{
    _avoidance = false;
    if((_kn->isBallKickable(_rid)||_kn->ballKicker()==_rid||_kn->findNearestTeammateToPoint(_wm->ball.pos.loc)==_rid) && _wm->ball.pos.loc.x < -FIELD_MAX_X/2)
        return doKick(rc);
    else
        return doMove(rc);
}

bool TacticCenterBack::doStop(RobotCommand &rc)
{
    _avoidance = true;
    return doMove(rc);
}

bool TacticCenterBack::doOurDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticCenterBack::doOurIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticCenterBack::doOurKickoff(RobotCommand &rc)
{
    _bk->setRID(_rid);
    _bk->setOur(true);
    _bk->setNum(0);
    return _bk->execute(rc);
}

bool TacticCenterBack::doOurPenalty(RobotCommand &rc)
{
    _bp->setRID(_rid);
    _bp->isOur(true);
    return _bp->execute(rc);
}

bool TacticCenterBack::doTheirDirectFreeKick(RobotCommand &rc)
{
//    this->_bfk->setOur(false);
//    this->_bfk->setDirect(true);
//    this->_bfk->setIndex(_index);
//    this->_bfk->setRID(_rid);
//    return this->_bfk->execute(rc);
    _avoidance = true;
    return doMove(rc);
}

bool TacticCenterBack::doTheirIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticCenterBack::doTheirKickoff(RobotCommand &rc)
{
    _bk->setRID(_rid);
    _bk->setOur(false);
    _bk->setNum(0);
    return _bk->execute(rc);
}

bool TacticCenterBack::doTheirPenalty(RobotCommand &rc)
{

}

bool TacticCenterBack::doKick(RobotCommand &rc)
{
    Position p;
    _skb->setRID(_rid);
    _skb->setSpeedX(SHOOT_KICK_SPEED);
    p.dir = (Vector2D(FIELD_MAX_X,0)-_wm->ourRobot[_rid].pos.loc).dir().radian();
    p.dir = _wm->ourRobot[_rid].pos.dir;
    _skb->setKickPosition(p);
    return _skb->execute(rc);
}

bool TacticCenterBack::doMove(RobotCommand &rc)
{
    Position p;
    Vector2D sol;
    //    if (_avoidance)
    //    {
    //        Circle2D penaltyArea(Vector2D(-FIELD_MAX_X,0),200+ROBOT_RADIUS+PENALTY_AREA_RADIUS+PARALLEL_LINE_LENGTH/2);
    //        Line2D ballLine(_wm->ball.pos.loc , Vector2D(-FIELD_MAX_X,0));
    //        Vector2D sol1,sol2;
    //        if (penaltyArea.intersection(ballLine,&sol1,&sol2)!=0)
    //        {
    //            if (sol1.x < -FIELD_MAX_X)
    //                sol = sol2;
    //            else
    //                sol = sol1;
    //        }
    //        else
    //        {
    //            sol.x = 200+ROBOT_RADIUS+PENALTY_AREA_RADIUS+PARALLEL_LINE_LENGTH/2;
    //            sol.y = 0;
    //        }
    //        Circle2D robotCircle(sol,ROBOT_RADIUS);
    //        robotCircle.intersection(penaltyArea,&sol1,&sol2);
    //    }
    //    else
    //    {
    Circle2D penaltyArea(Vector2D(-FIELD_MAX_X,0),ROBOT_RADIUS+PENALTY_AREA_RADIUS+PARALLEL_LINE_LENGTH/2);
    Line2D ballLine(_wm->ball.pos.loc , Vector2D(-FIELD_MAX_X,0));
    Vector2D sol1,sol2;
    if (penaltyArea.intersection(ballLine,&sol1,&sol2)!=0)
    {
        if (sol1.x < -FIELD_MAX_X)
            sol = sol2;
        else
            sol = sol1;
    }
    else
    {
        sol.x = -FIELD_MAX_X+ROBOT_RADIUS+PENALTY_AREA_RADIUS+PARALLEL_LINE_LENGTH/2;
        sol.y = 0;
    }
    Circle2D robotCircle(sol,ROBOT_RADIUS);
    robotCircle.intersection(penaltyArea,&sol1,&sol2);
    //    }

    //
    if (_avoidance && sol.dist(_wm->ball.pos.loc)<500+ROBOT_RADIUS)
    {
        sol = _wm->ball.pos.loc + Vector2D::from_polar(500 + ROBOT_RADIUS,(sol-_wm->ball.pos.loc).dir());
        if (penaltyArea.contains(sol))
            sol = _wm->ball.pos.loc - Vector2D::from_polar(500 + ROBOT_RADIUS,(sol-_wm->ball.pos.loc).dir());
    }

    //

    p.loc = sol;
    p.dir = (sol - _wm->ball.pos.loc).dir().radian()+M_PI;
    _sgp->setPosition(p);
    _sgp->setRID(RID());
    return _sgp->execute(rc);
}
