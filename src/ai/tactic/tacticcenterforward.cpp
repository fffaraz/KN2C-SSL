#include "tacticcenterforward.h"

TacticCenterForward::TacticCenterForward(WorldModel* wm , Knowledge* kn , QObject* parent) :
    Tactic(wm,kn,"TacticCenterForward",parent)
{
    _index = 4;
    _sgp = new SkillGotoPosition(wm,this);
    _skb = new SkillKickBall(wm,this);
    _bs = new BehaviorStop(wm, kn, this);
    _bfk = new BehaviorFreeKick(wm, kn, this,false);
    _bk = new BehaviorKickoff(wm, kn, this);
    _bp = new BehaviorPenalty(wm,kn,this);
}

//bool TacticCenterForward::execute(RobotCommand &rc)
//{
//    return doMove(rc);

//    if (_kn->isBallKickable(_rid) ||
//            _kn->ballKicker() == _rid ||
//            _kn->findNearestTeammateToPoint(_wm->ball.pos.loc) == _rid)
//    {
//#if TACTIC_DEBUG
//        qDebug() << "CenterForward(" << _rid << ") in Kick Mode";
//#endif
//        return doKick(rc);
//    }
//    else
//    {
//#if TACTIC_DEBUG
//        qDebug() << "CenterForward(" << _rid << ") in Move Mode";
//#endif
//        return doMove(rc);
//    }
//}

bool TacticCenterForward::doPlayOn(RobotCommand &rc)
{
    if(_kn->isBallKickable(_rid)||_kn->ballKicker()==_rid||_kn->findNearestTeammateToPoint(_wm->ball.pos.loc)==_rid)
        return doKick(rc);
    else
        return doMove(rc);
}

bool TacticCenterForward::doStop(RobotCommand &rc)
{
    _bs->setRID(RID());
    _bs->setNum(2);
    return _bs->execute(rc);
}

bool TacticCenterForward::doOurDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticCenterForward::doOurIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticCenterForward::doOurKickoff(RobotCommand &rc)
{
    _bk->setRID(_rid);
    _bk->setOur(true);
    _bk->setNum(1);
    return _bk->execute(rc);
}

bool TacticCenterForward::doOurPenalty(RobotCommand &rc)
{
    _bp->setRID(_rid);
        _bp->isOur(true);
        return _bp->execute(rc);
}

bool TacticCenterForward::doTheirDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticCenterForward::doTheirIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticCenterForward::doTheirKickoff(RobotCommand &rc)
{
    _bk->setRID(_rid);
    _bk->setOur(false);
    _bk->setNum(1);
    return _bk->execute(rc);
}

bool TacticCenterForward::doTheirPenalty(RobotCommand &rc)
{

}

bool TacticCenterForward::doKick(RobotCommand &rc)
{
    Position p;
    _skb->setRID(_rid);
    _skb->setSpeedX(SHOOT_KICK_SPEED);
    p.dir = (Vector2D(FIELD_MAX_X,0)-_wm->ourRobot[_rid].pos.loc).dir().radian();
    _skb->setKickPosition(p);
    return _skb->execute(rc);
}

bool TacticCenterForward::doMove(RobotCommand &rc)
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
        p.loc.x = 0;
        p.loc.y = 0;
    }

    _sgp->setPosition(p);
    _sgp->setRID(RID());
    return _sgp->execute(rc);
}
