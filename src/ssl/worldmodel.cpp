#include "worldmodel.h"
#include "formationparser.h"

WorldModel::WorldModel()
{
    time=0;
    refgs.cmd=0;
    gs = STATE_Null;
    gs_last = STATE_Null;
    updatePlayMode();

    sixNormalFormation = new FormationDT(6);
    sixFreeKickOurFormation = new FormationDT(6);
    sixFreeKickOppFormation = new FormationDT(6);

    fiveNormalFormation = new FormationDT(5);
    fiveFreeKickOurFormation = new FormationDT(5);
    fiveFreeKickOppFormation = new FormationDT(5);
}

int WorldModel::goalsOpp()
{
    // Blue   --> 0
    // Yellow --> 1
    if (cmgs.getColor())
        return refgs.goals_blue;
    else
        return refgs.goals_yellow;
}

int WorldModel::goalsOur()
{
    // Blue   --> 0
    // Yellow --> 1
    if (cmgs.getColor())
        return refgs.goals_yellow;
    else
        return refgs.goals_blue;
}

Vector2D WorldModel::position(int rid, int activeRobots, Vector2D focusPoint, PlayMode pm)
{

    switch(pm)
    {
    case KickOffOur:
    case KickOffOpp:
    case GameOn:
    case Halt:
    case Stop:
    {
        switch(activeRobots)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        {
            return fiveNormalFormation->getPosition(rid, focusPoint);
        }
        case 6:
        {
            return sixNormalFormation->getPosition(rid, focusPoint);
        }
        default:
        {
            break;
        }
        }
    }
    case DirectFreeKickOur:
    case IndirectFreeKickOur:
    {
        switch(activeRobots)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        {
            return fiveFreeKickOurFormation->getPosition(rid, focusPoint);
        }
        case 6:
        {
            return sixFreeKickOurFormation->getPosition(rid, focusPoint);
        }
        default:
        {
            break;
        }
        }
    }
    case DirectFreeKickOpp:
    case IndirectFreeKickOpp:
    {
        switch(activeRobots)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        {
            return fiveFreeKickOppFormation->getPosition(rid, focusPoint);
        }
        case 6:
        {
            return sixFreeKickOppFormation->getPosition(rid, focusPoint);
        }
        default:
        {
            break;
        }
        }
    }
    case PenaltyKickOur:
    case PenaltyKickOpp:
    default:
    {
        break;
    }
    }

    return Vector2D::INVALIDATED;
}

PlayMode WorldModel::playMode()
{
    return _playMode;
}

void WorldModel::updatePlayMode()
{
    if (cmgs.canKickBall() && !cmgs.gameOn() && !cmgs.ourFreeKick())
    {
        if (_playMode!=NormalStart)
            lastMode = _playMode;
        _playMode = NormalStart;
        _canKick = true;
        return;
    }
    if(gs == STATE_Stop)
    {
        lastMode = _playMode;
        _playMode = Stop;
        _canKick = false;
        return;
    }
    if(cmgs.canMove()==false)
    {
        lastMode = _playMode;
        _playMode = Halt;
        _canKick = false;
        return;
    }
    if(cmgs.theirFreeKick() && cmgs.theirIndirectKick())
    {
        lastMode = _playMode;
        _playMode = IndirectFreeKickOpp;
        _canKick = false;
        return;
    }
    if(cmgs.theirFreeKick() && cmgs.theirDirectKick() )
    {
        lastMode = _playMode;
        _playMode = DirectFreeKickOpp;
        _canKick = false;
        return;
    }
    if(cmgs.ourFreeKick() && cmgs.ourIndirectKick())
    {
        lastMode = _playMode;
        _playMode = IndirectFreeKickOur;
        _canKick = false;
        return;
    }
    if(cmgs.ourFreeKick() && cmgs.ourDirectKick())
    {
        lastMode = _playMode;
        _playMode = DirectFreeKickOur;
        _canKick = false;
        return;
    }
    if(cmgs.theirKickoff())
    {
        lastMode = _playMode;
        _playMode = KickOffOpp;
        _canKick = false;
        return;
    }
    if(cmgs.ourKickoff())
    {
        lastMode = _playMode;
        _playMode = KickOffOur;
        _canKick = false;
        return;
    }
    if(cmgs.theirPenaltyKick())
    {
        lastMode = _playMode;
        _playMode = PenaltyKickOpp;
        _canKick = false;
        return;
    }
    if(cmgs.ourPenaltyKick())
    {
        lastMode = _playMode;
        _playMode = PenaltyKickOur;
        _canKick = false;
        return;
    }
    if(cmgs.gameOn())
    {
        lastMode = _playMode;
        _playMode = GameOn;
        _canKick = true;
        return;
    }
}

bool WorldModel::canKick()
{
    return _canKick;
}
