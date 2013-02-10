#ifndef TACTICSTOP_H
#define TACTICSTOP_H

#include <QObject>
#include <QMap>
#include "vector_2d.h"
#include "tactic.h"
#include "skills.h"

class TacticStop : public Tactic
{
    Q_OBJECT
public:
    explicit TacticStop(WorldModel* wm, Knowledge* kn, QObject *parent = 0);
    Skill* getSkill();
    void setTotalStop(int ts) { _total_stop=ts; }
    void setMyStop(int ms) { _my_stop=ms; }
    void setTarget(Vector2D target,Vector2D defpoit,float distance,bool defence) { _target=target; _defpoint=defpoit; _distance=distance; _defence = defence; }

    QMap<int,int> stops;

private:
    SkillGotoPosition* _skillstop;

    Vector2D _target;
    Vector2D _defpoint;
    float _distance;
    bool _defence;

    int _total_stop;
    int _my_stop;
};

#endif // TACTICSTOP_H
