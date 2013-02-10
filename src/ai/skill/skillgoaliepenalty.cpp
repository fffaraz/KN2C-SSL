#include "skillgoaliepenalty.h"

SkillGoaliePenalty::SkillGoaliePenalty(WorldModel* wm, QObject *parent) :
    Skill(wm, "SkillGoalie", parent)
{
}

bool SkillGoaliePenalty::execute(RobotCommand &rc)
{
    if(_rid==-1) return false;

    Line2D lineGoal(Vector2D(-3025,-2025),Vector2D(-3025,2025));
    Vector2D gdir, gloc;
    gdir=Vector2D();
    gloc=Vector2D();

    int kickerID=-1;
    float minDist=9000000,temp;

    for(int i=0; i<PLAYERS_MAX_NUM;i++)
    {
        if(_wm->oppRobot[i].isValid)
        {
            temp=_wm->oppRobot[i].pos.loc.dist2(_wm->ball.pos.loc);
            if(temp<minDist)
            {
                minDist=temp;
                kickerID=i;
            }
        }
    }
    //////

    if(kickerID!=-1)
    {
        gdir=Vector2D(1,0);
        gloc=Vector2D(-3025,0);
    }
    else
    {
        Vector2D ins;
        Line2D l1(_wm->oppRobot[kickerID].pos.loc,AngleDeg(_wm->oppRobot[kickerID].pos.dir*AngleDeg::RAD2DEG));

        ins = l1.intersection(lineGoal);

        if(ins.y>265)
        {
            ins.y=265;
        }
        else if(ins.y<-265)
        {
            ins.y=-265;
        }
        ins.x=-3025;

        gdir=Vector2D(1,0);

        gloc=ins;
    }

    if(gloc.x<-3010)
        gloc.x=-3010;

    rc.FinalPos.loc=gloc;
    rc.TargetPos.loc=gloc;
    rc.FinalPos.dir=gdir.dir().radian();
    rc.TargetPos.dir=gdir.dir().radian();
    rc.Speed=1;
    return true;
}

bool SkillGoaliePenalty::SkillDone()
{
    return false;
}
