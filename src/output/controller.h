#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QtCore>
#include <QDebug>
#include <QMap>
#include "position.h"
#include "scriptengine.h"

#define GRSIM true

class ScriptEngine;

class ControllerData : public QObject
{
    Q_OBJECT
public:
    Position curpos;
    Position curvel;
    Position target;
    int rid;
    float fdest;
    float speed;
};

struct RobotSpeed
{
    int RID;
    float VX;
    float VY;
    float VW;
};

struct MotorSpeed
{
    float M1;
    float M2;
    float M3;
    float M4;
};

struct ControllerResult
{
    RobotSpeed rs;
    MotorSpeed ms3;
    MotorSpeed ms4;
};

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(ScriptEngine* engine, QObject *parent = 0);
    ControllerResult calc(Position curpos, Position curvel, Position target, int rid, float fdest, float speed);

private:
    ScriptEngine* _engine;
    RobotSpeed calcRobotSpeed(ControllerData& data);
    MotorSpeed calcMotorSpeed3(RobotSpeed rs);
    MotorSpeed calcMotorSpeed4(RobotSpeed rs);

    int MAXMOTORSRPM;
    float WHEELDIAMETER;
    float ROBOTRADIUS;

    QMap<int, double> err; //=1;
    QMap<int, Vector2D> PastDist;

signals:

public slots:

};

#endif // CONTROLLER_H
