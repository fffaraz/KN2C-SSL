#ifndef VISIONRESULT_H
#define VISIONRESULT_H

#include <QList>
#include <QDebug>
#include "constants.h"
#include "base.h"
#include "visionball.h"
#include "visionrobot.h"
#include "geom.h"
#include "game_state.h"
#include "ref_protocol.h"

class VisionResult
{
public:
    VisionResult();
    double time;
    VisionBall ball;
    VisionRobot ourRobot[PLAYERS_MAX_NUM];
    VisionRobot oppRobot[PLAYERS_MAX_NUM];
};

#endif // VISIONRESULT_H
