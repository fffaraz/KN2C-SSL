#ifndef ROBOTCOMMAND_H
#define ROBOTCOMMAND_H

#include "position.h"

struct RobotCommand
{
    Position TargetPos;
    Position FinalPos;
    float Speed;
    // Kick ...
    float kickspeedx;
    float kickspeedz;
    RobotCommand()
    {
        TargetPos=Position();
        FinalPos=Position();
        Speed=0;
        kickspeedx=0;
        kickspeedz=0;
    }
};


#endif // ROBOTCOMMAND_H
