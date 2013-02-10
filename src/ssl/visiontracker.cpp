#include "visiontracker.h"

VisionTracker::VisionTracker(VisionResult *vr, WorldModel *wm, VisionRecorder *recorder, QObject *parent) :
    QObject(parent),
    _vr(vr),
    _wm(wm),
    _recorder(recorder),
    _state(false)
{
}

void VisionTracker::Start()
{
    _state=true;
}

void VisionTracker::Stop()
{
    _state=false;
}

void VisionTracker::newVisionResult()
{
    if(_state)
    {
        Vector2D newpos;
        newpos=_wm->ball.pos.loc.scale(9.0);
        newpos.add(_vr->ball.pos);
        newpos = newpos.scale(1.0/10.0);
        _wm->ball.pos.loc=newpos;
        _wm->ball.pos.dir=0;
        _wm->ball.isValid=_vr->ball.isValid;
        _wm->ball.time=_vr->ball.time;
        _wm->ball.vel=getBallSpeed();

        for(int i=0;i<PLAYERS_MAX_NUM; i++)
        {
            newpos=_wm->ourRobot[i].pos.loc.scale(9.0);
            newpos.add(_vr->ourRobot[i].pos);
            newpos = newpos.scale(1.0/10.0);
            _wm->ourRobot[i].pos.loc=newpos;

            newpos=_wm->oppRobot[i].pos.loc.scale(9.0);
            newpos.add(_vr->oppRobot[i].pos);
            newpos = newpos.scale(1.0/10.0);
            _wm->oppRobot[i].pos.loc=newpos;

            _wm->ourRobot[i].pos.dir=_vr->ourRobot[i].angle;
            _wm->oppRobot[i].pos.dir=_vr->oppRobot[i].angle;
            _wm->ourRobot[i].id=_vr->ourRobot[i].id;
            _wm->oppRobot[i].id=_vr->oppRobot[i].id;
            _wm->ourRobot[i].isValid=_vr->ourRobot[i].isValid;
            _wm->oppRobot[i].isValid=_vr->oppRobot[i].isValid;
            _wm->ourRobot[i].time=_vr->ourRobot[i].time;
            _wm->oppRobot[i].time=_vr->oppRobot[i].time;

            _wm->ourRobot[i].vel = getOurRobotSpeed(i);
            _wm->oppRobot[i].vel = getOppRobotSpeed(i);
        }
        _wm->time=_vr->time;

        // Signal New Worldmodel
        newWorldModel();
    }
}

Position VisionTracker::getBallSpeed()
{
    int count=0;
    //qDebug()<<"BALL TIME: "<<_recorder->getWM(10)->ball.time;
    double diftime;
    Vector2D sum(0,0);
    Vector2D temp;
    for(int j=30;j>0;j--)
    {
        diftime=_recorder->getWM(j-1)->ball.time - _recorder->getWM(j)->ball.time;
        if(diftime==0)
            continue;
        temp=(_recorder->getWM(j-1)->ball.pos.loc - _recorder->getWM(j)->ball.pos.loc);
        temp.scale(1.0/diftime);
        sum+=temp;
        count++;
    }
    sum.scale((double)1.0/count);
    Position speed;
    speed.loc=sum;
    speed.dir=0;
    return speed;
}

Position VisionTracker::getOurRobotSpeed(int rid)
{
    int count=0;
    double diftime;
    Vector2D sum(0,0);
    Vector2D temp;
    for(int j=30;j>0;j--)
    {
        diftime=_recorder->getWM(j-1)->ourRobot[rid].time - _recorder->getWM(j)->ourRobot[rid].time;
        if(diftime==0)
            continue;
        temp=(_recorder->getWM(j-1)->ourRobot[rid].pos.loc - _recorder->getWM(j)->ourRobot[rid].pos.loc);
        temp.scale(1.0/diftime);
        sum+=temp;
        count++;
    }
    sum.scale((double)1.0/count);
    Position speed;
    speed.loc=sum;
    speed.dir=(_recorder->getWM(0)->ourRobot[rid].pos.dir-_recorder->getWM(1)->ourRobot[rid].pos.dir)/diftime;
    return speed;
}

Position VisionTracker::getOppRobotSpeed(int rid)
{
    int count=0;
    double diftime;
    Vector2D sum(0,0);
    Vector2D temp;
    for(int j=30;j>0;j--)
    {
        diftime=_recorder->getWM(j-1)->oppRobot[rid].time - _recorder->getWM(j)->oppRobot[rid].time;
        if(diftime==0)
            continue;
        temp=(_recorder->getWM(j-1)->oppRobot[rid].pos.loc - _recorder->getWM(j)->oppRobot[rid].pos.loc);
        temp.scale(1.0/diftime);
        sum+=temp;
        count++;
    }
    sum.scale((double)1.0/count);
    Position speed;
    speed.loc=sum;
    //for(int j=0;j<)
    speed.dir=(_recorder->getWM(0)->oppRobot[rid].pos.dir-_recorder->getWM(1)->oppRobot[rid].pos.dir)/diftime;
    return speed;
}





/*

        Vector2D difloc;
        double difang;
        double diftime;
        difloc = _vr->ball.pos - _wm->ball.pos.loc;
        _wm->ball.vel.loc=difloc.scale(1.0/(_vr->ball.time-_wm->ball.time));
        _wm->ball.vel.dir=0;

        difloc=_wm->ball.pos.loc - _recorder->getWM(10)->ball.pos.loc;
        diftime=_wm->ball.time - _recorder->getWM(10)->ball.time;
        _wm->ball.vel.loc=difloc.scale(1.0/diftime);


            difloc=_vr->ourRobot[i].pos - _wm->ourRobot[i].pos.loc;
            _wm->ourRobot[i].vel.loc=difloc.scale(1.0/(_vr->ourRobot[i].time-_wm->ourRobot[i].time));
            _wm->oppRobot[i].vel.loc=Vector2D(0,0);
            _wm->ourRobot[i].vel.dir=1000*(_vr->ourRobot[i].angle - _wm->ourRobot[i].pos.dir)/(_vr->ourRobot[i].time-_wm->ourRobot[i].time);
            _wm->oppRobot[i].vel.dir=0;


            difloc=Vector2D(0,0);
            Vector2D tempp;
            for(int j=10;j>0;j--)
            {
                diftime=_recorder->getWM(j)->ourRobot[i].time - _recorder->getWM(j-1)->ourRobot[i].time;
                tempp=(_recorder->getWM(j)->ourRobot[i].pos.loc - _recorder->getWM(j-1)->ourRobot[i].pos.loc);
                tempp.scale(1.0/diftime);
                difloc+=tempp;
            }
            difloc.scale(0.1);

            difang=_wm->ourRobot[i].pos.dir - _recorder->getWM(1)->ourRobot[i].pos.dir;

            _wm->ourRobot[i].vel.loc=difloc;
            _wm->ourRobot[i].vel.dir=difang/diftime;

            difloc=Vector2D(0,0);
            for(int j=10;j>0;j--)
            {
                diftime=_recorder->getWM(j)->oppRobot[i].time - _recorder->getWM(j-1)->oppRobot[i].time;
                tempp=(_recorder->getWM(j)->oppRobot[i].pos.loc - _recorder->getWM(j-1)->oppRobot[i].pos.loc);
                tempp.scale(1/diftime);
                difloc+=tempp;
            }
            difloc.scale(0.1);

            difang=_wm->oppRobot[i].pos.dir - _recorder->getWM(1)->oppRobot[i].pos.dir;

            _wm->oppRobot[i].vel.loc=difloc;
            _wm->oppRobot[i].vel.dir=difang/diftime;



  */
