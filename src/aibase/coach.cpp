#include "coach.h"

#include "strategydefault.h"
#include "strategytest.h"

Coach::Coach(WorldModel *wm, QMap<int,Agent*> &agents, QObject *parent) :
    QObject(parent),
    _timer(this),
    _wm(wm),
    _agents(agents)
{
    qDebug() << "Coach Initialization...";
    _strategy = new StrategyDefault(_wm, agents, this);

    _timer.setInterval(COACH_TIMER);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
}

void Coach::timer_timeout()
{
    _strategy->ExecuteStrategyEngine();

    //    foreach(Agent* agent, _agents)
    //    {
    //        // here is skills executions!
    //    }
}

void Coach::Start()
{
    qDebug() << "Coach::Start";
    _timer.start();
}

void Coach::Stop()
{
    qDebug() << "Coach::Stop";
    _timer.stop();
}
