#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <QObject>
#include <QString>

#include "knowledge.h"
#include "worldmodel.h"
#include "robotcommand.h"

class Behavior : public QObject
{
    Q_OBJECT
public:
    explicit Behavior(WorldModel *wm, Knowledge *kn, QString name, QObject *parent = 0);
    void setRID(int rid) { this->_rid = rid; }
    void setIndex(int index) { this->_index = index; }
    void setName(QString name) { this->_name = name; }

    QString name() { return this->_name; }
    int rid () { return this->_rid; }
    int index() { return this->_index; }

    virtual bool execute(RobotCommand &rc) = 0;

protected:
    Knowledge *_kn;
    WorldModel *_wm;
    QString _name;
    int _rid;
    int _index; // used for static position.
};

#endif // BEHAVIOR_H
