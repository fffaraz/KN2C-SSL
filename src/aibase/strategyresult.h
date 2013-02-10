#ifndef STRATEGYRESULT_H
#define STRATEGYRESULT_H

#include <QMap>
#include "constants.h"

class Play;
class Role;
class Tactic;
class Skill;

struct StrategyResult
{
    Play* play;
    QMap<int,Role*> roles;
    QMap<int,Tactic*> tactics;
    QMap<int,Skill*> skills;
    bool useSkill[PLAYERS_MAX_NUM];
};

#endif // STRATEGYRESULT_H
