#ifndef BEHAVIORKICKOFF_H
#define BEHAVIORKICKOFF_H

#include "behavior.h"
#include "Skills.h"

class BehaviorKickoff : public Behavior
{
    Q_OBJECT
public:
    explicit BehaviorKickoff(WorldModel* wm, Knowledge* kn,QObject *parent = 0);
    bool execute(RobotCommand &rc);
    void setOur(bool our){_our = our;}
    void setNum(int num){_point = num;}


private:
    bool _our;
    int _point;
    SkillGotoPosition* _sgp;
    SkillKickBall* _skb;
    
signals:
    
public slots:
    
};

#endif // BEHAVIORKICKOFF_H
