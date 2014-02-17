#include "tacticrightforward.h"

TacticRightForward::TacticRightForward(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm,kn,"TacticRightForward",parent)
{
    _index = 5;
    _sgp = new SkillGotoPosition(wm,this);
    _skb = new SkillKickBall(wm,this);
    _bs = new BehaviorStop(wm, kn, this);
    _bfk = new BehaviorFreeKick(wm, kn, this,true);
    _bk = new BehaviorKickoff(wm,kn,this);
    _bp = new BehaviorPenalty(wm,kn,this);
}

//bool TacticRightForward::execute(RobotCommand &rc)
//{
//    return doMove(rc);

//    if (_kn->isBallKickable(_rid) ||
//            _kn->ballKicker() == _rid ||
//            _kn->findNearestTeammateToPoint(_wm->ball.pos.loc) == _rid)
//    {
//#if TACTIC_DEBUG
//        qDebug() << "RightForward(" << _rid << ") in Kick Mode";
//#endif
//        return doKick(rc);
//    }
//    else
//    {
//#if TACTIC_DEBUG
//        qDebug() << "RightForward(" << _rid << ") in Move Mode";
//#endif
//        _kickerState = KS_GoBehindBall;
//        return doMove(rc);
//    }
//}

bool TacticRightForward::doPlayOn(RobotCommand &rc)
{
    if(_kn->isBallKickable(_rid)||_kn->ballKicker()==_rid||_kn->findNearestTeammateToPoint(_wm->ball.pos.loc)==_rid)
        return doKick(rc);
    else
        return doMove(rc);
}

bool TacticRightForward::doStop(RobotCommand &rc)
{
    _bs->setRID(RID());
    _bs->setNum(3);
    return _bs->execute(rc);
}

bool TacticRightForward::doOurDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticRightForward::doOurIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticRightForward::doOurKickoff(RobotCommand &rc)
{
    _bk->setRID(_rid);
    _bk->setOur(true);
    _bk->setNum(2);
    return _bk->execute(rc);
}

bool TacticRightForward::doOurPenalty(RobotCommand &rc)
{
        _bp->setRID(_rid);
        _bp->isOur(true);
        return _bp->execute(rc);
}

bool TacticRightForward::doTheirDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticRightForward::doTheirIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticRightForward::doTheirKickoff(RobotCommand &rc)
{
    _bk->setRID(_rid);
    _bk->setOur(false);
    _bk->setNum(2);
    return _bk->execute(rc);
}

bool TacticRightForward::doTheirPenalty(RobotCommand &rc)
{

}

bool TacticRightForward::doKick(RobotCommand &rc)
{
    Position p;
    _skb->setRID(_rid);
    _skb->setSpeedX(SHOOT_KICK_SPEED);
    p.dir = (Vector2D(FIELD_MAX_X,0)-_wm->ourRobot[_rid].pos.loc).dir().radian();
    _skb->setKickPosition(p);
    return _skb->execute(rc);
}

bool TacticRightForward::doMove(RobotCommand &rc)
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
        p.loc.y = -300;
    }

    _sgp->setPosition(p);
    _sgp->setRID(RID());
    return _sgp->execute(rc);
}
