#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include <QObject>
#include "worldmodel.h"
#include "strategyresult.h"
#include "role.h"

class Knowledge : public QObject
{
    Q_OBJECT
public:
    explicit Knowledge(WorldModel* wm, StrategyResult* sr, QObject *parent = 0);
    int CountActiveAgents();
    QList<int> ActiveAgents();
    QList<int> findRole(QString name);
    QList<int> findNearestTo(Vector2D loc);
    int findOppAttacker();

private:
    WorldModel* _wm;
    StrategyResult* _sr;

signals:

public slots:

};

#endif // KNOWLEDGE_H
