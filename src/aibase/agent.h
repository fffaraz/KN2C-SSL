#ifndef AGENT_H
#define AGENT_H

#include <QObject>
#include <QTimer>
#include "constants.h"
#include "outputbuffer.h"
#include "controller.h"
#include "worldmodel.h"
#include "robotcommand.h"
#include "skill.h"
#include "tactic.h"
#include "Tactics.h"


class Agent : public QObject
{
    Q_OBJECT
public:
    explicit Agent(int rid, OutputBuffer* outputbuffer, WorldModel* wm, QObject *parent = 0);
    int RID() { return _rid; }
    RobotCommand rc;
    void assignTactic(Tactic* tactic);
    bool isDummy();
    QString temp(){return _tactic->Name();}
    Tactic* tactic();


private:
    QTimer _timer;
    OutputBuffer* _outputbuffer;
    int _rid;
    WorldModel* _wm;
    Skill* _skill;
    Tactic* _tactic;

    //////////////////
    char _FLG;
    char _ASK;
    /////////////////

private slots:
    void timer_timeout();
    void SendCommand(RobotCommand rc);

signals:

public slots:
    void Start();
    void Stop();
    void Halt();

};

#endif // AGENT_H
