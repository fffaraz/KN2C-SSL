#include "skillgoalie.h"

SkillGoalie::SkillGoalie(WorldModel* wm, QObject *parent) :
    Skill(wm, "SkillGoalie", parent)
{
}

bool SkillGoalie::execute(RobotCommand &rc)
{
    if(_rid==-1) return false;

    Ray2D ballRay(_wm->ball.pos.loc,AngleDeg(_wm->ball.vel.loc.dir().degree()));
    Line2D lineGoal(Vector2D(-3025,-2025),Vector2D(-3025,2025));
    Vector2D gdir, gloc;
    gdir=Vector2D();
    gloc=Vector2D();

    int kickerID=-1;
    float minDist=9000000,temp;


    Vector2D ballContact = ballRay.intersection(lineGoal);

    if(_wm->ball.pos.loc.dist2(Vector2D(-3025,175))<=640000 || _wm->ball.pos.loc.dist2(Vector2D(-3025,-175))<=640000 || (_wm->ball.pos.loc.x<=-2225 && _wm->ball.pos.loc.y<=175 && _wm->ball.pos.loc.y>=-175))
    {
        if(ballContact.y>=-350 && ballContact.y<=350)
        {
            gloc=_wm->ball.pos.loc+_wm->ball.vel.loc.setLengthVector(90);
        }
        else
        {
            gloc=_wm->ball.pos.loc;
            gloc.x-=90;
        }
        gdir.x=1;
        gdir.y=0;
    }
    else
    {
        if(ballContact.y>=-350 && ballContact.y<=350)
        {
            gloc=ballContact-_wm->ball.vel.loc.setLengthVector(350);
            gdir=-_wm->ball.vel.loc;
        }
        else
        {
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

            if(kickerID!=-1)
            {
                if(_wm->oppRobot[kickerID].pos.dir>=-M_PI_2 && _wm->oppRobot[kickerID].pos.dir<=M_PI_2)
                {
                    Vector2D rTarget,rTemp;
                    Ray2D tRay(_wm->oppRobot[kickerID].pos.loc,AngleDeg(_wm->oppRobot[kickerID].pos.dir*AngleDeg::RAD2DEG));
                    minDist=100000000;
                    for(int i=0;i<PLAYERS_MAX_NUM;i++)
                    {
                        rTemp=tRay.intersection(Ray2D(_wm->oppRobot[i].pos.loc,AngleDeg(_wm->oppRobot[i].vel.loc.dir().degree())));
                        temp=_wm->ball.pos.loc.dist2(rTemp);
                        if(temp<minDist)
                        {
                            rTarget=rTemp;
                            minDist=temp;
                        }
                    }
                    gdir=(rTarget-Vector2D(-3025,0)).setLengthVector(500);
                    gloc=Vector2D(-3025,0)+gdir;
                }
                else
                {
                    Vector2D ins;
                    Line2D l1(_wm->oppRobot[kickerID].pos.loc,AngleDeg(_wm->oppRobot[kickerID].pos.dir*AngleDeg::RAD2DEG));

                    ins = l1.intersection(lineGoal);

                    if(ins.y>350)
                    {
                        ins.y=350;
                    }
                    else if(ins.y<-350)
                    {
                        ins.y=-350;
                    }
                    ins.x=-3025;

                    gdir=(_wm->ball.pos.loc-ins).setLengthVector(500);

                    gloc=gdir+ins;
                }
            }
            else
            {
                gdir=(_wm->ball.pos.loc-Vector2D(-3025,0)).setLengthVector(500);
                gloc=Vector2D(-3025,0)+gdir;
            }
        }
    }

    if(gloc.x<-2980)
        gloc.x=-2980;

    rc.FinalPos.loc=gloc;
    rc.TargetPos.loc=gloc;
    rc.FinalPos.dir=gdir.dir().radian();
    rc.TargetPos.dir=gdir.dir().radian();
    rc.Speed=1;
    return true;
}

bool SkillGoalie::SkillDone()
{
    return false;
}


//bool SkillGoalie::execute(RobotCommand &rc)
//{
//    if(_rid==-1) return false;
//    Vector2D gkp;

//    gkp = Vector2D(_wm->ball.pos.loc.x+3025,_wm->ball.pos.loc.y);


//    if(gkp.length() < 2250)
//        gkp.setLength(530*(gkp.length()/2250)+350);
//    else
//        gkp.setLength(880);
//    if(fabs(gkp.dir().degree()) > 90)
//        gkp.setDir(sign(gkp.dir().degree())*90);
//    gkp.x-=3025;
//    rc.FinalPos.loc=gkp;
//    rc.TargetPos.loc=gkp;
//    rc.FinalPos.dir=Vector2D(_wm->ball.pos.loc.x+3025,_wm->ball.pos.loc.y).dir().radian();
//    rc.TargetPos.dir=Vector2D(_wm->ball.pos.loc.x+3025,_wm->ball.pos.loc.y).dir().radian();
//    rc.Speed=1;
//    return true;
//}
