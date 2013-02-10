#include "navigationdefault.h"

NavigationDefault::NavigationDefault(WorldModel *wm, QObject *parent) :
    Navigation(wm, "NavigationDefault", parent)
{
}

bool NavigationDefault::execute(int rid, Position FinalPos, Position &TargetPos)
{
    Vector2D currentLoc = robotLoc(rid,true);
    Vector2D nearestOBS;
    bool foundNearest = false;
    //for oppROBOTS
    for(int i=0; i < PLAYERS_MAX_NUM ;i++)
    {
        if(!_wm->oppRobot[i].isValid)
            continue;
        Vector2D rbTemp = _wm->oppRobot[i].pos.loc;
        if(intersectOBS(rbTemp,currentLoc,FinalPos.loc))
        {
            if(!foundNearest)
            {
                nearestOBS = rbTemp;
                foundNearest = true;
            }
            else if (currentLoc.dist2(rbTemp) <= currentLoc.dist2(nearestOBS) )
            {
                nearestOBS = rbTemp;
            }
        }
    }
    //for ourROBOT
    for(int i=0; i < PLAYERS_MAX_NUM ; i++)
    {
        if(!_wm->oppRobot[i].isValid)
            continue;
        if(i==rid)
            continue;
        Vector2D rbTemp = _wm->ourRobot[i].pos.loc;
        if(intersectOBS(rbTemp,currentLoc,FinalPos.loc))
        {
            if(!foundNearest)
            {
                nearestOBS = rbTemp;
                foundNearest = true;
            }
            else if (currentLoc.dist2(rbTemp) <= currentLoc.dist2(nearestOBS) )
            {
                nearestOBS = rbTemp;
            }
        }
    }
    //check ball
    if(_wm->ball.isValid)
    {
        Vector2D balltmp = _wm->ball.pos.loc;
        if(intersectOBS(balltmp,currentLoc,FinalPos.loc)){
            if(!foundNearest)
            {
                nearestOBS = balltmp;
                foundNearest = true;
            }
            else if (currentLoc.dist2(balltmp) <= currentLoc.dist2(nearestOBS) )
            {
                nearestOBS = balltmp;
            }
        }
    }
    if(!foundNearest)
        TargetPos = FinalPos;
    else {
        Line2D interline(currentLoc,nearestOBS);
        Circle2D obs(nearestOBS,300);
        Vector2D res1,res2;
        obs.intersection(interline.perpendicular(nearestOBS),&res1,&res2);
        if(FinalPos.loc.dist2(res1) <= FinalPos.loc.dist2(res2))
        {
            FinalPos.loc = res1;
            TargetPos = FinalPos;
        }else
        {
            FinalPos.loc = res2;
            TargetPos = FinalPos;
        }
    }
    return true;
}
bool NavigationDefault::intersectOBS(Vector2D robotOBSloc, Vector2D cur, Vector2D dest)
{
    Line2D way(cur,dest);
    bool outOfOBS = false;
    if(robotOBSloc.x > cur.x && robotOBSloc.x > dest.x)
    {
        outOfOBS = true;
    }
    if(robotOBSloc.x < cur.x && robotOBSloc.x < dest.x)
    {
        outOfOBS = true;
    }
    if(outOfOBS)
        return false;
    if(way.dist(robotOBSloc) < 300)
    {
        return true;
    }
    return false;
}
Vector2D NavigationDefault::robotLoc(int rid, bool ourRobot)
{
    if(ourRobot)
    {
        return _wm->ourRobot[rid].pos.loc;
    }
    return _wm->oppRobot[rid].pos.loc;
}
