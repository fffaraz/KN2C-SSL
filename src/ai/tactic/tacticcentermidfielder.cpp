#include "tacticcentermidfielder.h"
#include <limits>

TacticCenterMidfielder::TacticCenterMidfielder(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm,kn,"TacticCenterMidfielder",parent)
{
    _index = 3;
    _sgp = new SkillGotoPosition(wm,this);
    _skb = new SkillKickBall(wm,this);
    _bs = new BehaviorStop(wm, kn, this);
    _bfk = new BehaviorFreeKick(wm, kn, this,false);
    _bk = new BehaviorKickoff(wm,kn,this);
    _bp = new BehaviorPenalty(wm,kn,this);
}

//bool TacticCenterMidfielder::execute(RobotCommand &rc)
//{
//    return doMove(rc);

//    if (_kn->isBallKickable(_rid) ||
//            _kn->ballKicker() == _rid ||
//            _kn->findNearestTeammateToPoint(_wm->ball.pos.loc) == _rid)
//    {
//#if TACTIC_DEBUG
//        qDebug() << "CenterMidfielder(" << _rid << ") in Kick Mode";
//#endif
//        return doKick(rc);
//    }
//    else
//    {
//#if TACTIC_DEBUG
//        qDebug() << "CenterMidfielder(" << _rid << ") in Move Mode";
//#endif
//        return doMove(rc);
//    }
//}

bool TacticCenterMidfielder::doPlayOn(RobotCommand &rc)
{
    if(_kn->isBallKickable(_rid)||_kn->ballKicker()==_rid||_kn->findNearestTeammateToPoint(_wm->ball.pos.loc)==_rid)
        return doKick(rc);
    else
        return doMove(rc);
}

bool TacticCenterMidfielder::doStop(RobotCommand &rc)
{
    _bs->setRID(RID());
    _bs->setNum(1);
    return _bs->execute(rc);
}

bool TacticCenterMidfielder::doOurDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticCenterMidfielder::doOurIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticCenterMidfielder::doOurKickoff(RobotCommand &rc)
{
    _bk->setRID(_rid);
    _bk->setOur(true);
    _bk->setNum(0);
    return _bk->execute(rc);
}

bool TacticCenterMidfielder::doOurPenalty(RobotCommand &rc)
{
    _bp->setRID(_rid);
    _bp->isOur(true);
    return _bp->execute(rc);
}

bool TacticCenterMidfielder::doTheirDirectFreeKick(RobotCommand &rc)
{
    Vector2D sol;
    Position pos;
    Rect2D *checkArea;
    if (_wm->ball.pos.loc.y>0)
        checkArea = new Rect2D(Vector2D(-FIELD_MAX_X,0),Size2D(FIELD_MAX_X,FIELD_MAX_Y));
    else
        checkArea = new Rect2D(Vector2D(-FIELD_MAX_X,FIELD_MAX_Y),Size2D(FIELD_MAX_X,FIELD_MAX_Y));
    double minDist = std::numeric_limits < double > :: max();
    int index = -1;
    for(int i = 0 ; i < PLAYERS_MAX_NUM ; i++)
    {
        if (!_wm->oppRobot[i].isValid || _wm->ball.pos.loc.signY()*_wm->oppRobot[i].pos.loc.y > 0 )
            continue;
        if (_wm->oppRobot[i].pos.loc.dist(Vector2D(-FIELD_MAX_X , 0)) < minDist)
        {
            minDist = _wm->oppRobot[i].pos.loc.dist(Vector2D(-FIELD_MAX_X , 0));
            index = i;
        }
    }
    if (index!=-1)
    {
        Circle2D penaltyArea(Vector2D(-FIELD_MAX_X,0),ROBOT_RADIUS+PENALTY_AREA_RADIUS+PARALLEL_LINE_LENGTH/2);
        Line2D robotLine(_wm->oppRobot[index].pos.loc , Vector2D(-FIELD_MAX_X,0));
        Vector2D sol1,sol2;
        penaltyArea.intersection(robotLine,&sol1,&sol2);
        if (sol1.x < -FIELD_MAX_X)
            sol = sol2;
        else
            sol = sol1;
        pos.loc = sol;
        pos.dir = (Vector2D(-FIELD_MAX_X , 0)-sol).dir().radian()+M_PI;
        _sgp->setRID(_rid);
        _sgp->setPosition(pos);
        return _sgp->execute(rc);
    }
    else
    {
        this->_bfk->setOur(false);
        this->_bfk->setDirect(true);
        this->_bfk->setIndex(_index);
        this->_bfk->setRID(_rid);
        return this->_bfk->execute(rc);
    }
}

bool TacticCenterMidfielder::doTheirIndirectFreeKick(RobotCommand &rc)
{
    Vector2D sol;
    Position pos;
    Rect2D *checkArea;
    if (_wm->ball.pos.loc.y>0)
        checkArea = new Rect2D(Vector2D(-FIELD_MAX_X,0),Size2D(FIELD_MAX_X,FIELD_MAX_Y));
    else
        checkArea = new Rect2D(Vector2D(-FIELD_MAX_X,FIELD_MAX_Y),Size2D(FIELD_MAX_X,FIELD_MAX_Y));
    double minDist = std::numeric_limits < double > :: max();
    int index = -1;
    for(int i = 0 ; i < PLAYERS_MAX_NUM ; i++)
    {
        if (!_wm->oppRobot[i].isValid || _wm->ball.pos.loc.signY()*_wm->oppRobot[i].pos.loc.y > 0 )
            continue;
        if (_wm->oppRobot[i].pos.loc.dist(Vector2D(-FIELD_MAX_X , 0)) < minDist)
        {
            minDist = _wm->oppRobot[i].pos.loc.dist(Vector2D(-FIELD_MAX_X , 0));
            index = i;
        }
    }
    if (index!=-1)
    {
        Circle2D penaltyArea(Vector2D(-FIELD_MAX_X,0),ROBOT_RADIUS+PENALTY_AREA_RADIUS+PARALLEL_LINE_LENGTH/2);
        Line2D robotLine(_wm->oppRobot[index].pos.loc , Vector2D(-FIELD_MAX_X,0));
        Vector2D sol1,sol2;
        penaltyArea.intersection(robotLine,&sol1,&sol2);
        if (sol1.x < -FIELD_MAX_X)
            sol = sol2;
        else
            sol = sol1;
        pos.loc = sol;
        pos.dir = (Vector2D(-FIELD_MAX_X , 0)-sol).dir().radian()+M_PI;
        _sgp->setRID(_rid);
        _sgp->setPosition(pos);
        return _sgp->execute(rc);
    }
    else
    {
        this->_bfk->setOur(false);
        this->_bfk->setDirect(false);
        this->_bfk->setIndex(_index);
        this->_bfk->setRID(_rid);
        return this->_bfk->execute(rc);
    }
}

bool TacticCenterMidfielder::doTheirKickoff(RobotCommand &rc)
{
    _bk->setRID(_rid);
    _bk->setOur(false);
    _bk->setNum(0);
    return _bk->execute(rc);
}

bool TacticCenterMidfielder::doTheirPenalty(RobotCommand &rc)
{

}

bool TacticCenterMidfielder::doKick(RobotCommand &rc)
{
    Position p;
    _skb->setRID(_rid);
    _skb->setSpeedX(SHOOT_KICK_SPEED);
    p.dir = (Vector2D(FIELD_MAX_X,0)-_wm->ourRobot[_rid].pos.loc).dir().radian();
    _skb->setKickPosition(p);
    return _skb->execute(rc);
}

bool TacticCenterMidfielder::doMove(RobotCommand &rc)
{
    Position p;
    int roles = _kn->countActiveRoles();
    Vector2D vec = _wm->position(_index, roles, _wm->ball.pos.loc, _wm->playMode());

    if (vec.isValid())
    {
        p.loc.x = vec.x;
        p.loc.y = vec.y;
    }
    else
    {
        p.loc.x = - 1000;
        p.loc.y = -600;
    }

    _sgp->setPosition(p);
    _sgp->setRID(RID());
    return _sgp->execute(rc);
}
