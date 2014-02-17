#ifndef BEHAVIORSTOP_H
#define BEHAVIORSTOP_H

#include "behavior.h"
#include "Skills.h"

class BehaviorStop : public Behavior
{
    Q_OBJECT
public:
    explicit BehaviorStop(WorldModel* wm, Knowledge *kn, QObject *parent = 0 );
    void setNum(int num){_point = num;}
    bool execute(RobotCommand &rc);

private:
    SkillGotoPosition* _sgp;
    int _point;
    
signals:
    
public slots:
    
};

#endif // BEHAVIORSTOP_H
