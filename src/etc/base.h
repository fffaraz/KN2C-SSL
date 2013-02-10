#ifndef BASE_H
#define BASE_H

enum TeamSideType
{
    SIDE_RIGHT,
    SIDE_LEFT
};

enum TeamColorType
{
    COLOR_BLUE = 0,
    COLOR_YELLOW = 1
};

enum CameraConfigType
{
    CAMERA_NONE = 0,
    CAMERA_0 = 1,
    CAMERA_1 = 2,
    CAMERA_BOTH = 4
};

enum GameModeType
{
    MODE_REAL,
    MODE_SIMULATION
};

enum GameStateType
{
    STATE_Null = 0,

    STATE_Halt = 1, // OK!
    STATE_Stop = 2, // OK!

    STATE_Start = 3,
    STATE_ForceStart= 4, // OK!

    STATE_Kick_off_Our = 5, // OK!
    STATE_Kick_off_Opp = 6, // OK!

    STATE_Penalty_Our = 7, // OK!
    STATE_Penalty_Opp = 8, // OK!

    STATE_Free_kick_Our = 9,
    STATE_Free_kick_Opp = 10,

    STATE_Indirect_Free_kick_Our = 11,
    STATE_Indirect_Free_kick_Opp = 12,


};

#endif // BASE_H
