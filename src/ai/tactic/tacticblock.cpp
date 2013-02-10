#include "tacticblock.h"

TacticBlock::TacticBlock(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm, kn, "TacticBlock", parent)
{
    _skill = new SkillGotoPosition(wm, this);
    _total_Block=0;
    _my_Block=0;
}

Skill* TacticBlock::getSkill()
{
    if(_rid==-1) return 0;
    _skill->setRID(_rid);
    Position pos;
    //default Y defend Distance start point
    double distToMiddle = 1000;
    //default Y Distance start point
    double posToMiddle = 1500;
    //default X distance to middle
    double xPos = -300;

   if(_total_Block == 1 || _total_Block == 2)
   {
       if(_my_Block == 1)
       {
           //chapi
           Vector2D minY(-xPos,distToMiddle);
           Ray2D min(minY,90);
           Vector2D res;
           int tmp = intersectOPP(min,&res);
           if(tmp != -1)
           {
               pos.loc = res;
               pos.dir = (_wm->oppRobot[tmp].pos.loc - _wm->ourRobot[_rid].pos.loc).dir().radian();
           }
           else
           {
               pos.loc.y = posToMiddle;
               pos.loc.x = -xPos;
               pos.dir = 0;
           }
       }
       if(_my_Block == 2)
       {
           //rasti
           Vector2D minY(-xPos,-distToMiddle);
           Ray2D min(minY,270);
           Vector2D res;
           int tmp = intersectOPP(min,&res);
           if(tmp != -1)
           {
               pos.loc = res;
               pos.dir = (_wm->oppRobot[tmp].pos.loc - _wm->ourRobot[_rid].pos.loc).dir().radian();
           }
           else
           {
               pos.loc.y = -posToMiddle;
               pos.loc.x = -xPos;
               pos.dir = 0;
           }

       }

   }

    _skill->setPosition(pos);
    return _skill;
}

int TacticBlock::intersectOPP(Ray2D dif, Vector2D *res)
{
    double OppRobotMinX = 600;
    for(int i; i < PLAYERS_MAX_NUM ;i++)
    {
        if(!_wm->oppRobot[i].isValid)
            continue;

        if(dif.origin().y >= 0)
            if(_wm->oppRobot[i].pos.loc.y > dif.origin().y || _wm->oppRobot[i].pos.loc.x > OppRobotMinX)
             continue;

        if(dif.origin().y <= 0)
         if(_wm->oppRobot[i].pos.loc.y < dif.origin().y || _wm->oppRobot[i].pos.loc.x > OppRobotMinX)
             continue;

        Ray2D opp(_wm->oppRobot[i].pos.loc , _wm->oppRobot[i].pos.dir*AngleDeg::RAD2DEG);

        Vector2D ans = opp.intersection(dif);
        if(ans != Vector2D::INVALIDATED)
        {
            *res = ans;
            return i;
        }
    }
    return -1;
}

