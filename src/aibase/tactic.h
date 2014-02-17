#ifndef TACTIC_H
#define TACTIC_H

#include <QObject>

#include "robotcommand.h"
#include "knowledge.h"

#include "Skills.h"
#include "Behaviors.h"


class WorldModel;
class Knowledge;
class Skill;

class Tactic : public QObject
{
    Q_OBJECT

public:
    explicit Tactic(WorldModel* wm, Knowledge* kn, QString name, QObject *parent = 0);
    QString Name() { return _name; }
    bool execute(RobotCommand &rc);
    virtual bool doKick(RobotCommand &rc)=0;
    virtual bool doMove(RobotCommand &rc)=0;
    virtual void setRID(int rid) { _rid=rid; }
    virtual int RID() { return _rid; }

    virtual bool doPlayOn(RobotCommand &rc)=0;
    virtual bool doOurIndirectFreeKick(RobotCommand &rc)=0;
    virtual bool doTheirIndirectFreeKick(RobotCommand &rc)=0;
    virtual bool doOurDirectFreeKick(RobotCommand &rc)=0;
    virtual bool doTheirDirectFreeKick(RobotCommand &rc)=0;
    virtual bool doStop(RobotCommand &rc)=0;
    virtual bool doOurPenalty(RobotCommand &rc)=0;
    virtual bool doTheirPenalty(RobotCommand &rc)=0;
    virtual bool doOurKickoff(RobotCommand &rc)=0;
    virtual bool doTheirKickoff(RobotCommand &rc)=0;

    bool doHalt(RobotCommand &rc);

protected:
    QString _name;
    int _rid;
    int _index;
    Knowledge* _kn;
    WorldModel* _wm;
};

#endif // TACTIC_H
