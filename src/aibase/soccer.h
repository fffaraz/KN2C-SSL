#ifndef SOCCER_H
#define SOCCER_H

#include <QtCore>
#include <QObject>
#include <QtCore>
#include <QDebug>
#include <QTimer>
#include <QMap>
#include "settings.h"
#include "transmitter.h"
#include "visionresult.h"
#include "visiontracker.h"
#include "worldmodel.h"
#include "sslrefbox.h"
#include "sslvision.h"
#include "visionrecorder.h"
#include "wpacket.h"
#include "grsim.h"
#include "outputbuffer.h"
#include "scriptengine.h"
#include "controller.h"
#include "agent.h"
#include "ai.h"
#include "formationparser.h"

class ScriptEngine;
class Controller;
class Transmitter;
class grSim;
class Agent;
class AI;

class Soccer : public QObject
{
    Q_OBJECT
public:
    explicit Soccer(QObject *parent = 0);

//private:
    GameModeType gamemode;
    VisionResult* vr;
    WorldModel* wm;
    VisionTracker* visiontracker;
    SSLVision* sslvision;
    VisionRecorder* visionrecorder;
    SSLRefBox* sslrefbox;
    OutputBuffer* outputbuffer;
    Transmitter* transmitter;
    grSim* grsim;
    ScriptEngine* scriptengine;
    Controller* controller;
    AI *ai;


signals:

public slots:

};

#endif // SOCCER_H
