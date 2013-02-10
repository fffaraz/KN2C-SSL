#include "sslvision.h"

SSLVision::SSLVision(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, VisionResult* visionresult, QObject *parent) :
    SSLReceiver(ip,port,parent),
    _color(color),
    _side(side),
    _camera(camera),
    _fpscam0(parent),
    _fpscam1(parent),
    _vr(visionresult)
{
    _time.start();
    connect(this, SIGNAL(newReceivedPacket(QByteArray,QString,int)), this, SLOT(readPendingPacket(QByteArray,QString,int)));

    // reset notseen counters
    _vframe[0].reset();
    _vframe[1].reset();

    // Log
    qDebug() << "SSLVision Initialization...";
    qDebug() << "IP: " << ip;
    qDebug() << "Port: " << port;
    qDebug() << "Color: " << (color==COLOR_BLUE?"Blue":"Yellow");
    qDebug() << "Side: " << (side==SIDE_RIGHT?"Right":"Left");
    qDebug() << "Camera: " << ((int)camera);
}

void SSLVision::readPendingPacket(QByteArray data, QString ip, int port)
{
    // check for server ip (& port)
    if(ip=="" && port==0) return;

    // unpack sslvision packet
    SSL_WrapperPacket packet;
    bool ans=packet.ParseFromArray(data.data(), data.size());
    if(!ans) return;
    if(packet.has_detection()==false) return;
    SSL_DetectionFrame pck = packet.detection();

    // parse detection frame
    parse(pck);
    // merge cameras frames after each vision packet
    merge();
    // update vision result
    updateresult();
    // update world model
    updatewm();
}

void SSLVision::updateresult()
{
    double cur_time = _vmframe.time;
    _vrframe.time_c = _vmframe.time_c;
    _vrframe.time = _vmframe.time;

    // remove old objects
    REMOVE_OLD_OBJECTS(balls);
    for(int rid=0; rid<PLAYERS_MAX_NUM; ++rid)
    {
        REMOVE_OLD_OBJECTS(ourRobots[rid]);
        REMOVE_OLD_OBJECTS(oppRobots[rid]);
    }

    // append new objects
    APPEND_NEW_OBJECTS(balls);
    for(int rid=0; rid<PLAYERS_MAX_NUM; ++rid)
    {
        APPEND_NEW_OBJECTS(ourRobots[rid]);
        APPEND_NEW_OBJECTS(oppRobots[rid]);
    }
}

void SSLVision::updatewm()
{
    FIND_BEST_OBJ(balls, ball, VisionBall);

    for(int rid=0; rid<PLAYERS_MAX_NUM; ++rid)
    {
        FIND_BEST_OBJ(ourRobots[rid], ourRobot[rid], VisionRobot);
        FIND_BEST_OBJ(oppRobots[rid], oppRobot[rid], VisionRobot);
    }

    // world model time
    _vr->time = _vrframe.time;

    newVisionResult();
}


void SSLVision::parse(SSL_DetectionFrame &pck)
{
    // update camera fps
    int cid = pck.camera_id();
    if(cid == 0) _fpscam0.Pulse();
    if(cid == 1) _fpscam1.Pulse();

    // update vision frame
    _vframe[cid].clear();
    _vframe[cid].frame_number =  pck.frame_number();
    _vframe[cid].time_c = pck.t_capture();
    _vframe[cid].time = _time.elapsed();

    // fill ball & robots data
    fillframe(_vframe[cid], pck);

    // vision frame is now overwrtiten
    _vframe[cid].updated=true;
}

void SSLVision::merge()
{
    VisionFrame emptyframe;
    emptyframe.reset();
    emptyframe.clear();

    VisionFrame* frm[CAMERA_NUM];

    switch(_camera)
    {
    case CAMERA_BOTH:
        frm[0]=&_vframe[0];
        frm[1]=&_vframe[1];
        break;
    case CAMERA_0:
        frm[0]=&_vframe[0];
        frm[1]=&emptyframe;
        break;
    case CAMERA_1:
        frm[0]=&emptyframe;
        frm[1]=&_vframe[1];
        break;
    case CAMERA_NONE:
    default:
        frm[0]=&emptyframe;
        frm[1]=&emptyframe;
    }

    _vmframe.clear();
    _vmframe.time_c = max(frm[0]->time_c, frm[1]->time_c);
    _vmframe.time = max(frm[0]->time, frm[1]->time);
    _vmframe.frame_number = max(frm[0]->frame_number, frm[1]->frame_number);
    _vmframe.notseen_ball = min(frm[0]->notseen_ball, frm[1]->notseen_ball);

    for(int cid=0; cid<CAMERA_NUM; ++cid)
    {
        // skip if it not updated yet
        if(frm[cid]->updated == false) continue;

        // add balls
        _vmframe.balls.append(frm[cid]->balls);

        // add robots
        for(int rid=0; rid<PLAYERS_MAX_NUM; ++rid)
        {
            _vmframe.ourRobots[rid].append(frm[cid]->ourRobots[rid]);
            _vmframe.oppRobots[rid].append(frm[cid]->oppRobots[rid]);
        }
    }

    // update not seen counters
    for(int rid=0; rid<PLAYERS_MAX_NUM; ++rid)
    {
        _vmframe.notseen_ourRobot[rid] = min(frm[0]->notseen_ourRobot[rid],frm[1]->notseen_ourRobot[rid]);
        _vmframe.notseen_oppRobot[rid] = min(frm[0]->notseen_oppRobot[rid],frm[1]->notseen_oppRobot[rid]);
    }

    _vmframe.updated = true;
    frm[0]->updated = false;
    frm[1]->updated = false;
}

void SSLVision::fillframe(VisionFrame &frm, SSL_DetectionFrame &pck)
{
    // Team side Coefficient
    float ourSide = (_side == SIDE_RIGHT)? -1.0f : 1.0f;
    double time = frm.time; //frm.time_c;

    // insert balls
    bool seen_ball=false;
    int max_balls=min(VOBJ_MAX_NUM, pck.balls_size());
    for(int i=0; i<max_balls; ++i)
    {
        auto b=pck.balls(i);
        if(b.has_confidence() && b.has_x() && b.has_y())
            if(b.confidence() > MIN_CONF && fabs(b.x()) < FIELD_MAX_X && fabs(b.y()) < FIELD_MAX_Y)
            {
                frm.balls.append(VisionBall(Vector2D(b.x()*ourSide, b.y()*ourSide), time));
                frm.notseen_ball=0;
                seen_ball=true;
            }
    }
    if(!seen_ball) ++frm.notseen_ball;

    // flags for seen robots
    bool seen_our[PLAYERS_MAX_NUM]={};
    bool seen_opp[PLAYERS_MAX_NUM]={};

    if(_color == COLOR_BLUE)
    {
        APPEND_ROBOTS(blue, our);
        APPEND_ROBOTS(yellow, opp);
    }
    else // _color == COLOR_YELLOW
    {
        APPEND_ROBOTS(yellow, our);
        APPEND_ROBOTS(blue, opp);
    }

    // update not seen robots
    for(int i=0; i<PLAYERS_MAX_NUM; ++i)
    {
        if(!seen_opp[i]) ++frm.notseen_oppRobot[i];
        if(!seen_our[i]) ++frm.notseen_ourRobot[i];
    }
}
