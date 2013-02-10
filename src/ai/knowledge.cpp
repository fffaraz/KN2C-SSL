#include "knowledge.h"
#include "strategy.h"

Knowledge::Knowledge(WorldModel *wm, StrategyResult *sr, QObject *parent) :
    QObject(parent),
    _wm(wm),
    _sr(sr)
{

}

int Knowledge::CountActiveAgents()
{
    int counter=0;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
        if(_wm->ourRobot[i].isValid) counter++;
    return counter;
}

QList<int> Knowledge::ActiveAgents()
{
    QList<int> ans;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
        if(_wm->ourRobot[i].isValid)
            ans.append(i);
    return ans;
}

QList<int> Knowledge::findRole(QString name)
{
    QList<int> ans;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
    {
        if(_sr->roles[i]->Name() == name && _wm->ourRobot[i].isValid)
            ans.append(i);
    }
    return ans;
}

QList<int> Knowledge::findNearestTo(Vector2D loc)
{
    QMap<double, int> smap;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
    {
        if(_wm->ourRobot[i].isValid==false) continue;
        double dist=(_wm->ourRobot[i].pos.loc-loc).length();
        smap.insert(dist, i);
    }
    QList<int> ans;
    for(auto i=smap.begin(); i!=smap.end(); i++)
        ans.append(i.value());
    return ans;
}

int Knowledge::findOppAttacker()
{
    int ans=0;
    double mindist=1000000;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
    {
        if(_wm->oppRobot[i].isValid==false) continue;
        double dist=(_wm->oppRobot[i].pos.loc-_wm->ball.pos.loc).length();
        if(dist<mindist)
        {
            mindist=dist;
            ans=i;
        }
    }
    return ans;
}

