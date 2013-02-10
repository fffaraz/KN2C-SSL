#ifndef COACH_H
#define COACH_H

#include <QObject>
#include <QTimer>
#include "constants.h"
#include "worldmodel.h"
#include "agent.h"

class Agent;
class Strategy;

class Coach : public QObject
{
    Q_OBJECT
public:
    explicit Coach(WorldModel* wm, QMap<int,Agent*> &agents, QObject *parent = 0);

private:
    QTimer _timer;
    bool _isStarted;
    WorldModel* _wm;
    QMap<int,Agent*> &_agents;
    Strategy* _strategy;

signals:

private slots:
    void timer_timeout();

public slots:
    void Start();
    void Stop();

};

#endif // COACH_H
