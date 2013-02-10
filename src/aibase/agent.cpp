#include "agent.h"

Agent::Agent(int rid, OutputBuffer *outputbuffer, WorldModel *wm, QObject *parent) :
    QObject(parent),
    _timer(this),
    _outputbuffer(outputbuffer),
    _rid(rid),
    _wm(wm),
    _FLG(0),
    _ASK(0)
{
    qDebug() << "Agent Initialization... (ID=" << _rid <<")";
    _skill=0;
    _timer.setInterval(AGENT_TIMER);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
}

void Agent::timer_timeout()
{
    RobotCommand rc;
    bool ans=false;
    if(_skill)
        ans = _skill->execute(rc);
    if(ans && _wm->ourRobot[_rid].isValid)
        SendCommand(rc);
    else if(_wm->ourRobot[_rid].isValid)
        Halt();
}

void Agent::AssignSkill(Skill *skill)
{
    _skill=skill;
}

void Agent::SendCommand(RobotCommand rc)
{
    Position mypos=_wm->ourRobot[_rid].pos;
    Position myvel=_wm->ourRobot[_rid].vel;
    float fdest = (rc.FinalPos.loc-rc.TargetPos.loc).length();
    ControllerResult ctrlres = _outputbuffer->ctrl->calc(mypos,myvel,rc.TargetPos,_rid, fdest, rc.Speed);
    // Real Game Packet
    RobotData reRD;
    reRD.RID = _rid;
    reRD.M1 = ctrlres.ms3.M1;
    reRD.M2 = ctrlres.ms3.M2;
    reRD.M3 = ctrlres.ms3.M3;
    reRD.M4 = 0; // we have 3 motors!
    reRD.KCK = (rc.kickspeedx>0)?1:0;
    reRD.FLG = _FLG;
    reRD.ASK = _ASK;
    _outputbuffer->wpck.AddRobot(reRD);
    // grSim Packet
    grRobotData grRD;
    grRD.rid=_rid;
    grRD.velx = ctrlres.rs.VX;
    grRD.vely = ctrlres.rs.VY;
    grRD.velw = ctrlres.rs.VW;
    grRD.wheel1=ctrlres.ms4.M1;
    grRD.wheel2=ctrlres.ms4.M2;
    grRD.wheel3=ctrlres.ms4.M3;
    grRD.wheel4=ctrlres.ms4.M4;
    grRD.kickspeedx=rc.kickspeedx;
    grRD.kickspeedz=rc.kickspeedz;
    grRD.spinner=0;
    _outputbuffer->grpck.AddRobot(grRD);
}

void Agent::Start()
{
    qDebug() << "Agent::Start (" << _rid <<")";
    _timer.start();
}

void Agent::Stop()
{
    qDebug() << "Agent::Stop (" << _rid <<")";
    _timer.stop();
}

void Agent::Halt()
{
    // Real Game Packet
    RobotData reRD;
    reRD.RID = _rid;
    reRD.M1 = 0;
    reRD.M2 = 0;
    reRD.M3 = 0;
    reRD.M4 = 0;
    reRD.KCK = 0;
    reRD.FLG = 0;
    reRD.ASK = 0;
    _outputbuffer->wpck.AddRobot(reRD);
    // grSim Packet
    grRobotData grRD;
    grRD.rid=_rid;
    grRD.velx = 0;
    grRD.vely = 0;
    grRD.velw = 0;
    grRD.wheel1=0;
    grRD.wheel2=0;
    grRD.wheel3=0;
    grRD.wheel4=0;
    grRD.kickspeedx=0;
    grRD.kickspeedz=0;
    grRD.spinner=0;
    _outputbuffer->grpck.AddRobot(grRD);
}
