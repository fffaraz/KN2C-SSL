#ifndef SKILL_H
#define SKILL_H

#include <QObject>
#include "robotcommand.h"
#include "worldmodel.h"

class Agent;

class Skill : public QObject
{
    Q_OBJECT

public:
    explicit Skill(WorldModel* wm, QString name, QObject *parent = 0);
    virtual bool execute(RobotCommand& rc) = 0;
    QString Name() { return _name; }
    virtual void setRID(int rid) { _rid=rid; }
    virtual bool SkillDone() = 0;

protected:
    QString _name;
    int _rid;
    WorldModel* _wm; 

};

#endif // SKILL_H
