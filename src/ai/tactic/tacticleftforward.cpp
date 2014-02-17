#include "tacticleftforward.h"

TacticLeftForward::TacticLeftForward(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm,kn,"TacticLeftForward",parent)
{
    _index = 4;
    _sgp = new SkillGotoPosition(wm,this);
    _skb = new SkillKickBall(wm,this);
    _bs = new BehaviorStop(wm, kn, this);
    _bfk = new BehaviorFreeKick(wm, kn, this,true);
    _bk = new BehaviorKickoff(wm, kn, this);
    _bp = new BehaviorPenalty(wm,kn,this);
}

//bool TacticLeftForward::execute(RobotCommand &rc)
//{
//    return doKick(rc);
//    if (_wm->ball.pos.loc.dist(_wm->ourRobot[_rid].pos.loc) >= ROBOT_RADIUS &&
//            (_kn->isBallKickable(_rid) ||
//             _kn->ballKicker() == _rid))
//    {
//#if TACTIC_DEBUG
//        qDebug() << "LeftForward(" << _rid << ") in Kick Mode";
//#endif
//        return doKick(rc);
//    }
//    else
//    {
//#if TACTIC_DEBUG
//        qDebug() << "LeftForward(" << _rid << ") in Move Mode";
//#endif
//        return doMove(rc);
//    }
//}

bool TacticLeftForward::doPlayOn(RobotCommand &rc)
{
    if(_kn->isBallKickable(_rid)||_kn->ballKicker()==_rid||_kn->findNearestTeammateToPoint(_wm->ball.pos.loc)==_rid)
        return doKick(rc);
    else
        return doMove(rc);
}

bool TacticLeftForward::doStop(RobotCommand &rc)
{
    _bs->setRID(RID());
    _bs->setNum(2);
    return _bs->execute(rc);
}

bool TacticLeftForward::doOurDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticLeftForward::doOurIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticLeftForward::doOurKickoff(RobotCommand &rc)
{
    _bk->setRID(_rid);
    _bk->setOur(true);
    _bk->setNum(1);
    return _bk->execute(rc);
}

bool TacticLeftForward::doOurPenalty(RobotCommand &rc)
{
    _bp->setRID(_rid);
        _bp->isOur(true);
        return _bp->execute(rc);
}

bool TacticLeftForward::doTheirDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticLeftForward::doTheirIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticLeftForward::doTheirKickoff(RobotCommand &rc)
{
    _bk->setRID(_rid);
    _bk->setOur(false);
    _bk->setNum(1);
    return _bk->execute(rc);
}

bool TacticLeftForward::doTheirPenalty(RobotCommand &rc)
{

}

bool TacticLeftForward::doKick(RobotCommand &rc)
{
    Position p;
    _skb->setRID(_rid);
    _skb->setSpeedX(SHOOT_KICK_SPEED);
    p.dir = (Vector2D(FIELD_MAX_X,0)-_wm->ourRobot[_rid].pos.loc).dir().radian();
    _skb->setKickPosition(p);
    return _skb->execute(rc);
}

bool TacticLeftForward::doMove(RobotCommand &rc)
{
    Position p;
    Vector2D vec = _wm->position(_index, 6, _wm->ball.pos.loc, GameOn);
    if (vec.isValid())
    {
        p.loc.x = vec.x;
        p.loc.y = vec.y;
    }
    else
    {
        p.loc.x = 0;
        p.loc.y = 300;
    }

    _sgp->setPosition(p);
    _sgp->setRID(RID());
    return _sgp->execute(rc);
}
