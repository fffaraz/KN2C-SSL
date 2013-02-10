#ifndef TACTIC_H
#define TACTIC_H

#include <QObject>

class WorldModel;
class Knowledge;
class Skill;

class Tactic : public QObject
{
    Q_OBJECT

public:
    explicit Tactic(WorldModel* wm, Knowledge* kn, QString name, QObject *parent = 0);
    QString Name() { return _name; }
    virtual Skill* getSkill() =0;
    virtual void setRID(int rid) { _rid=rid; }
    virtual int RID() { return _rid; }

protected:
    QString _name;
    int _rid;
    WorldModel* _wm;
    Knowledge* _kn;
};

#endif // TACTIC_H
