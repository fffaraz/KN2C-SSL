#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <QList>
#include <QDebug>
#include "constants.h"
#include "base.h"
#include "ball.h"
#include "robot.h"
#include "geom.h"
#include "game_state.h"
#include "ref_protocol.h"

class WorldModel
{
public:
    explicit WorldModel();
    double time;
    Ball ball;
    Robot ourRobot[PLAYERS_MAX_NUM];
    Robot oppRobot[PLAYERS_MAX_NUM];
    GameStatePacket refgs;
    GameStateType gs;
    GameStateType gs_last;
    GameState cmgs;
};

#endif // WORLDMODEL_H
