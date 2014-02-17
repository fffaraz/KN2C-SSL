#include "tacticrightmidfielder.h"

TacticRightMidfielder::TacticRightMidfielder(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm,kn,"TacticRightMidfielder",parent)
{
    _sgp = new SkillGotoPosition(wm,this);
    _bfk = new BehaviorFreeKick(wm, kn, this,false);
    _bp = new BehaviorPenalty(wm,kn,this);
}
//bool TacticRightMidfielder::execute(RobotCommand &rc)
//{
//    return doMove(rc);

//    if (_kn->isBallKickable(_rid) ||
//            _kn->ballKicker() == _rid ||
//            _kn->findNearestTeammateToPoint(_wm->ball.pos.loc) == _rid)
//    {
//#if TACTIC_DEBUG
//        qDebug() << "RightMidfielder(" << _rid << ") in Kick Mode";
//#endif
//        return doKick(rc);
//    }
//    else
//    {
//#if TACTIC_DEBUG
//        qDebug() << "RightMidfielder(" << _rid << ") in Move Mode";
//#endif
//        _kickerState = KS_GoBehindBall;
//        return doMove(rc);
//    }
//}

bool TacticRightMidfielder::doPlayOn(RobotCommand &rc)
{
    return doMove(rc);
}

bool TacticRightMidfielder::doStop(RobotCommand &rc)
{

}

bool TacticRightMidfielder::doOurDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticRightMidfielder::doOurIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticRightMidfielder::doOurKickoff(RobotCommand &rc)
{

}

bool TacticRightMidfielder::doOurPenalty(RobotCommand &rc)
{
    _bp->setRID(_rid);
        _bp->isOur(true);
        return _bp->execute(rc);
}

bool TacticRightMidfielder::doTheirDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticRightMidfielder::doTheirIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticRightMidfielder::doTheirKickoff(RobotCommand &rc)
{

}

bool TacticRightMidfielder::doTheirPenalty(RobotCommand &rc)
{

}

bool TacticRightMidfielder::doKick(RobotCommand &rc)
{
    return false;
}

bool TacticRightMidfielder::doMove(RobotCommand &rc)
{
    Position p;
//    Vector2D vec = _wm->position(_index, _kn->countActiveAgents(), _wm->ball.pos.loc, _wm->playMode());
    Vector2D vec = Vector2D::INVALIDATED;

    if (vec.isValid())
    {
        p.loc.x = vec.x;
        p.loc.y = vec.y;
    }
    else
    {
        p.loc.x = -500;
        p.loc.y = -300;
    }

    _sgp->setPosition(p);
    _sgp->setRID(RID());
    return _sgp->execute(rc);
}
