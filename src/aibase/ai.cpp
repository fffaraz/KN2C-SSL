#include "ai.h"

AI::AI(WorldModel *worldmodel, ScriptEngine *scriptengine, OutputBuffer *outputbuffer, QObject *parent) :
    QObject(parent),
    _wm(worldmodel),
    _script(scriptengine)
{
    qDebug() << "AI Initialization...";

    // Agents
    for(int i=0; i<PLAYERS_MAX_NUM; i++)
        _agents[i] = new Agent(i, outputbuffer, _wm, this);

    // Coach
    _coach = new Coach(_wm, _agents, this);
}

void AI::Start()
{
    qDebug() << "AI::Start";
    _coach->Start();
    foreach(Agent* agent, _agents)
        agent->Start();
}

void AI::Stop()
{
    qDebug() << "AI::Stop";
    _coach->Stop();
    foreach(Agent* agent, _agents)
        agent->Stop();
}


