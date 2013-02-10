#include "visionresult.h"

VisionResult::VisionResult()
{
    time = 0;
    ball = VisionBall(Vector2D(0,0), 0);
    ball.isValid=false;

    for(int i=0; i<PLAYERS_MAX_NUM; ++i)
    {
        ourRobot[i] = VisionRobot(Vector2D(0,0), 0, 0, i);
        ourRobot[i].isValid =false;
        oppRobot[i] = VisionRobot(Vector2D(0,0), 0, 0, i);
        oppRobot[i].isValid =false;
    }
}
