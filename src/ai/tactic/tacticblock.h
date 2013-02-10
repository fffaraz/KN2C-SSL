#ifndef TACTICBLOCK_H
#define TACTICBLOCK_H

#include <QObject>
#include "tactic.h"
#include "skills.h"

class TacticBlock : public Tactic
{
    Q_OBJECT
public:
    explicit TacticBlock(WorldModel* wm, Knowledge* kn, QObject *parent = 0);
    Skill* getSkill();
    void setTotalBlock(int tb) { _total_Block = tb; }
    void setMyBlock(int mb) { _my_Block = mb; }
    QMap<int,int> blocks;

private:
    SkillGotoPosition* _skill;
    int _total_Block;
    int _my_Block;
    //return OPP ID if finds intersect point with OPP
    //and Ray dif witch should difence it.
    //else return -1
    int intersectOPP(Ray2D dif,Vector2D* res);
};

#endif // TACTICBLOCK_H
