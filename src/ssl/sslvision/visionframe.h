#ifndef VISIONFRAME_H
#define VISIONFRAME_H

#include <QList>
#include "constants.h"
#include "visionball.h"
#include "visionrobot.h"


struct VisionFrame
{
    int frame_number;
    double time_c; // capture time
    int time;
    bool updated;

    QList<VisionBall>  balls;
    int notseen_ball;
    QList<VisionRobot> ourRobots[PLAYERS_MAX_NUM];
    QList<VisionRobot> oppRobots[PLAYERS_MAX_NUM];
    int  notseen_ourRobot[PLAYERS_MAX_NUM];
    int  notseen_oppRobot[PLAYERS_MAX_NUM];

    void clear()
    {
        balls.clear();
        for(int i=0; i<PLAYERS_MAX_NUM; ++i)
        {
            ourRobots[i].clear();
            oppRobots[i].clear();
        }
    }

    void reset()
    {
        frame_number=-1;
        time_c = -1;
        time = -1;
        updated = false;

        notseen_ball = MAX_NOT_SEEN;
        for(int i=0; i<PLAYERS_MAX_NUM; ++i)
        {
            notseen_ourRobot[i] = MAX_NOT_SEEN;
            notseen_oppRobot[i] = MAX_NOT_SEEN;
        }

    }
};

#endif // VISIONFRAME_H
