#include "tacticleftmidfielder.h"

TacticLeftMidfielder::TacticLeftMidfielder(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm,kn,"TacticLeftMidfielder",parent)
{
    _sgp = new SkillGotoPosition(wm,this);
    _bfk = new BehaviorFreeKick(wm, kn, this,false);
    _bp = new BehaviorPenalty(wm,kn,this);
}

bool TacticLeftMidfielder::doPlayOn(RobotCommand &rc)
{
    return doMove(rc);
}

bool TacticLeftMidfielder::doStop(RobotCommand &rc)
{

}

bool TacticLeftMidfielder::doOurDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticLeftMidfielder::doOurIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(true);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticLeftMidfielder::doOurKickoff(RobotCommand &rc)
{

}

bool TacticLeftMidfielder::doOurPenalty(RobotCommand &rc)
{
    _bp->setRID(_rid);
        _bp->isOur(true);
        return _bp->execute(rc);
}

bool TacticLeftMidfielder::doTheirDirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(true);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticLeftMidfielder::doTheirIndirectFreeKick(RobotCommand &rc)
{
    this->_bfk->setOur(false);
    this->_bfk->setDirect(false);
    this->_bfk->setIndex(_index);
    this->_bfk->setRID(_rid);
    return this->_bfk->execute(rc);
}

bool TacticLeftMidfielder::doTheirKickoff(RobotCommand &rc)
{

}

bool TacticLeftMidfielder::doTheirPenalty(RobotCommand &rc)
{

}

bool TacticLeftMidfielder::doKick(RobotCommand &rc)
{
    return false;
}

bool TacticLeftMidfielder::doMove(RobotCommand &rc)
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
        p.loc.y = 300;
    }

    p.dir = (Vector2D(FIELD_MAX_X, 0) - vec).dir().radian();

    _sgp->setPosition(p);
    _sgp->setRID(RID());
    return _sgp->execute(rc);
}
