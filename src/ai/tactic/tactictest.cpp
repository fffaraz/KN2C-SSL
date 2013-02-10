#include "tactictest.h"

TacticTest::TacticTest(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm, kn, "TacticTest", parent)
{
    _state=0;
    _p1.loc = Vector2D(1000,0);
    _p2.loc = Vector2D(-1000,0);
    _p1.dir=0;
    _p2.dir=0;
}

Skill* TacticTest::getSkill()
{
    switch(_state)
    {
    default:
    case 0:
        _sp->setPosition(_p1);
        _sp->setRID(_rid);
        if(_sp->SkillDone())
        {
            _sw->ResetTime();
            _state++;
        }
        return _sp;
        break;
    case 1:
        _sw->setTime(5000);
        _sw->setRID(_rid);
        _sw->setPosition(_p1);
        if(_sw->SkillDone()) _state++;
        return _sw;
        break;
    case 2:
        _sp->setPosition(_p2);
        _sp->setRID(_rid);
        if(_sp->SkillDone())
        {
            _sw->ResetTime();
            _state++;
        }
        return _sp;
        break;
    case 3:
        _sw->setTime(5000);
        _sw->setRID(_rid);
        _sw->setPosition(_p2);
        if(_sw->SkillDone()) _state=0;
        return _sw;
        break;
    }
}
