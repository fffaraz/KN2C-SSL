#include "tactic.h"

Tactic::Tactic(WorldModel *wm, Knowledge *kn, QString name, QObject *parent) :
    QObject(parent),
    _name(name),
    _rid(-1),
    _index(-1),
    _wm(wm),
    _kn(kn)
{

}

bool Tactic::execute(RobotCommand &rc)
{
    switch (_wm->playMode())
    {
    case Halt:
        return doHalt(rc);
    case Stop:
        return doStop(rc);
    case KickOffOpp:
        return doTheirKickoff(rc);
    case KickOffOur:
        return doOurKickoff(rc);
    case IndirectFreeKickOpp:
        return doTheirIndirectFreeKick(rc);
    case IndirectFreeKickOur:
        return doOurIndirectFreeKick(rc);
    case DirectFreeKickOpp:
        return doTheirDirectFreeKick(rc);
    case DirectFreeKickOur:
        return doOurDirectFreeKick(rc);
    case PenaltyKickOpp:
        return doTheirPenalty(rc);
    case PenaltyKickOur:
        return doOurPenalty(rc);
    case NormalStart:
        switch (_wm->lastMode)
        {
        case KickOffOpp:
            return doTheirKickoff(rc);
        case KickOffOur:
            return doOurKickoff(rc);
        case PenaltyKickOpp:
            return doTheirPenalty(rc);
        case PenaltyKickOur:
            return doOurPenalty(rc);
        }
    default:
        return doPlayOn(rc);
    }
}

bool Tactic::doHalt(RobotCommand &rc)
{
    return false;
}
