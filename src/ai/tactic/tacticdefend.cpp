#include "tacticdefend.h"

TacticDefend::TacticDefend(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm, kn, "TacticDefend", parent)
{
    _skill = new SkillGotoPosition(wm, this);
    _total_def=0;
    _my_def=0;
}

Skill* TacticDefend::getSkill()
{
    _skill->setRID(_rid);
    Position ans;
    Vector2D gkp;
    gkp = Vector2D(_wm->ball.pos.loc.x+3025,_wm->ball.pos.loc.y);
    gkp.setLength(1100);

    if(_total_def == 1 || _total_def == 2)
    {
        if(gkp.dir().degree() - 2 < -90)
            gkp.setDir(-90 + 2);
        if(gkp.dir().degree() + 2 > 90)
            gkp.setDir(90 - 2);
        if(_my_def == 1)
            gkp.rotate(-2);
        if(_my_def == 2)
            gkp.rotate(2);
    }
    else if(_total_def == 3)
    {
        if(gkp.dir().degree() - 20 < -90)
            gkp.setDir(-90 + 20);
        if(gkp.dir().degree() + 20 > 90)
            gkp.setDir(90 - 20);
        if(_my_def == 1)
            gkp.rotate(-20);
//        if(_my_def == 2)
//            gkp;
        if(_my_def == 3)
            gkp.rotate(20);
    }


    gkp.x-=3025;

    //_total_def
    //_my_def
    ans.loc = gkp;
    ans.dir=Vector2D(_wm->ball.pos.loc.x+3025,_wm->ball.pos.loc.y).dir().radian();
    //    rc.TargetPos.dir=Vector2D(_wm->ball.pos.loc.x+3025,_wm->ball.pos.loc.y).dir().radian();

    _skill->setPosition(ans);
    return _skill;
}


//Skill* TacticDefend::getSkill()
//{
//    _skill->setRID(_rid);
//    Position ans;
//    Vector2D gkp;
//    gkp = Vector2D(_wm->ball.pos.loc.x+3025,_wm->ball.pos.loc.y);
//    gkp.setLength(1070);

//    if(_total_def == 1 || _total_def == 2)
//    {
//        if(gkp.dir().degree() - 10 < -90)
//            gkp.setDir(-90 + 10);
//        if(gkp.dir().degree() + 10 > 90)
//            gkp.setDir(90 - 10);
//        if(_my_def == 1)
//            gkp.rotate(-10);
//        if(_my_def == 2)
//            gkp.rotate(10);
//    }
//    else if(_total_def == 3)
//    {
//        if(gkp.dir().degree() - 40 < -90)
//            gkp.setDir(-90 + 40);
//        if(gkp.dir().degree() + 40 > 90)
//            gkp.setDir(90 - 40);
//        if(_my_def == 1)
//            gkp.rotate(-40);
//        if(_my_def == 2)
//            gkp;
//        if(_my_def == 3)
//            gkp.rotate(40);
//    }


//    gkp.x-=3025;

//    //_total_def
//    //_my_def
//    ans.loc = gkp;
//    ans.dir=Vector2D(_wm->ball.pos.loc.x+3025,_wm->ball.pos.loc.y).dir().radian();
//    //    rc.TargetPos.dir=Vector2D(_wm->ball.pos.loc.x+3025,_wm->ball.pos.loc.y).dir().radian();

//    _skill->setPosition(ans);
//    return _skill;
//}
