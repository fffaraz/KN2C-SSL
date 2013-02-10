#include "coach.h"

#include "strategydefault.h"

Coach::Coach(WorldModel *wm, QMap<int,Agent*> &agents, QObject *parent) :
    QObject(parent),
    _timer(this),
    _wm(wm),
    _agents(agents)
{
    qDebug() << "Coach Initialization...";

    // Strategy Selection
    _strategy = new StrategyDefault(_wm, this);


    _timer.setInterval(COACH_TIMER);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
}

void Coach::timer_timeout()
{
    //_agents[0]->AssignSkill(new SkillBallTracking());
    //_agents[1]->AssignSkill(new SkillMilad());
    //_agents[2]->AssignSkill(new SkillGKP());
    //_agents[3]->AssignSkill(new SkillBallTracking());
    //_agents[4]->AssignSkill(new SkillBallTracking());

    _strategy->ExecuteStrategyEngine();
    //_strategy->FindRoles();
    ///_strategy->FindTactics();
    foreach(Agent* agent, _agents)
    {
//        // Role Assignment
//        Role* role = _strategy->GetRole(agent->RID());
//        agent->AssignRole(role);
//        // Tactic Assignment
//        Tactic* tactic = _strategy->GetTactic(agent->RID());
//        agent->AssignTactic(tactic);
//        // Skill Assignment
//        Skill* skill = agent->getTactic()->CurrentSkill();

        Skill* skill = _strategy->getSkill(agent->RID());
        skill->setRID(agent->RID());
        agent->AssignSkill(skill);

    }
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
