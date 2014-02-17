#include "sslrefbox.h"

SSLRefBox::SSLRefBox(QString ip, int port, TeamColorType color, float ball_min, WorldModel* wm, QObject *parent) :
    SSLReceiver(ip,port,parent),
    _cmdcounter(0),
    _color(color),
    _lastCMDCounter(0),
    _ball_min(ball_min),
    _wm(wm)
{
    wm->cmgs.init(color);
    connect(this, SIGNAL(newReceivedPacket(QByteArray,QString,int)), this, SLOT(readPendingPacket(QByteArray,QString,int)));
    qDebug() << "SSLRefBox Initialization...";
    qDebug() << "IP: " << ip;
    qDebug() << "Port: " << port;
    qDebug() << "Color: " << (_color==COLOR_BLUE?"Blue":"Yellow");
    qDebug() << "Ball Min: " << _ball_min;
}

void SSLRefBox::readPendingPacket(QByteArray data, QString ip, int port)
{
    // check for server ip (& port)
    if(ip=="" && port==0) return;

    GameStatePacket pck;
    pck.cmd=data[0];
    pck.cmd_counter=data[1];
    pck.goals_blue=data[2];
    pck.goals_yellow=data[3];
    pck.time_remaining=data[4]*256 + data[5];

    // save last gs packet
    _wm->refgs = pck;

    // parse it
    parse(pck);
}

void SSLRefBox::parse(GameStatePacket pck)
{
    bool ball_moved = (_lastBall.pos.loc - _wm->ball.pos.loc).length()>_ball_min;
    if(!_wm->referee_our_ui)
        _wm->cmgs.transition(pck.cmd, ball_moved);
    else
        _wm->cmgs.transition(_wm->get_ui_state(),_wm->get_ui_ball_moved());
    _wm->updatePlayMode();
    if(!_wm->referee_our_ui)
        updategs(pck.cmd, ball_moved);
    else
        updategs(_wm->get_ui_state(),_wm->get_ui_ball_moved());

    if(pck.cmd_counter != _lastCMDCounter) // new cmd
    {
        // save ball position
        _lastBall = _wm->ball;
        // update command counter
        _lastCMDCounter = pck.cmd_counter;
        // send signal
        newRefreeCommand();
    }
    else    // no new cmd
    {
    }
}

//GameState NextState=value;

//if (value == GameState.Free_kick_Opp || value == GameState.Kick_off_Opp || value == GameState.Kick_off_Our)
//{
//    Saved_Ball_Position = WorldModel.Instance.Ball.Position;
//    Check_Ball_Position = true;
//    Ball_Moved = false;
//    KLogger.Logger.Log("Ball Position Saved.", "GameInfo", KLogger.LogPriority.Info);
//}

void SSLRefBox::updategs(char cmd, bool)
{
    _wm->gs_last=_wm->gs;

    switch(cmd)
    {
    case COMM_HALT:
        _wm->gs=STATE_Halt;
        break;
    case COMM_STOP:
        _wm->gs=STATE_Stop;
        break;
    case COMM_READY:
        _wm->gs=STATE_Start;
        break;
    case COMM_START:
        _wm->gs=STATE_ForceStart;
        break;
    case COMM_KICKOFF_BLUE:
        if (_color)
            _wm->gs = STATE_Kick_off_Our;
        else
            _wm->gs = STATE_Kick_off_Opp;
        break;
    case COMM_KICKOFF_YELLOW:
        if (_color)
            _wm->gs = STATE_Kick_off_Opp;
        else
            _wm->gs = STATE_Kick_off_Our;
        break;
    case COMM_PENALTY_BLUE:
        if (_color)
            _wm->gs = STATE_Penalty_Our;
        else
            _wm->gs = STATE_Penalty_Opp;
        break;
    case COMM_PENALTY_YELLOW:
        if (_color)
            _wm->gs = STATE_Penalty_Opp;
        else
            _wm->gs = STATE_Penalty_Our;
        break;
    case COMM_DIRECT_BLUE:
        if (_color)
            _wm->gs = STATE_Free_kick_Our;
        else
            _wm->gs = STATE_Free_kick_Opp;
        break;
    case COMM_DIRECT_YELLOW:
        if (_color)
            _wm->gs = STATE_Free_kick_Opp;
        else
            _wm->gs = STATE_Free_kick_Our;
        break;
    case COMM_INDIRECT_BLUE:
        if (_color)
            _wm->gs = STATE_Indirect_Free_kick_Our;
        else
            _wm->gs = STATE_Indirect_Free_kick_Opp;
        break;
    case COMM_INDIRECT_YELLOW:
        if (_color)
            _wm->gs = STATE_Indirect_Free_kick_Opp;
        else
            _wm->gs = STATE_Indirect_Free_kick_Our;
        break;

    case COMM_TIMEOUT_BLUE:
    case COMM_TIMEOUT_YELLOW:
        _wm->gs = STATE_Halt;
        break;

    default:
        _wm->gs=STATE_Null;
        break;
    }
}

