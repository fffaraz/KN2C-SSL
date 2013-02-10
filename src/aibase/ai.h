#ifndef AI_H
#define AI_H

#include <QtCore>
#include <QObject>
#include "constants.h"
#include "agent.h"
#include "scriptengine.h"
#include "coach.h"

class Agent;
class Coach;
class ScriptEngine;

class AI : public QObject
{
    Q_OBJECT
public:
    explicit AI(WorldModel* worldmodel, ScriptEngine* scriptengine, OutputBuffer* outputbuffer, QObject *parent = 0);

signals:

public slots:
    void Start();
    void Stop();

private:
    WorldModel* _wm;
    ScriptEngine* _script;
    QMap<int,Agent*> _agents;
    Coach* _coach;
    QTimer _timer;


};

#endif // AI_H
