#ifndef CONSTANTS_H
#define CONSTANTS_H

// global constants
#define PLAYERS_MAX_NUM 12
#define FIELD_MAX_X 3100
#define FIELD_MAX_Y 2100
#define BALL_RADIUS 22
#define ROBOT_RADIUS 90
//public static double MaxX = 3010;
//public static double MinX = -1500;
//public static double MaxY = 2025;
//public static double MinY = -2025;


// Vision constants
#define CAMERA_NUM 2
#define VOBJ_MAX_NUM 5
#define MIN_CONF 0.1
#define MAX_NOT_SEEN 100
#define VISION_TIMEDOUT 1000.0
#define MAX_RADIOUS 2000


// Timer speeds
#define TRANSMITTER_TIMER 50
#define AI_TIMER 40
#define AGENT_TIMER 20
#define COACH_TIMER 40

//public static int PLAYER_THREAD_SLEEP = 30;
//public static int COACH_THREAD_SLEEP = 20;
//public static int TRACKER_THREAD_SLEEP = 10;


//public static Vector2D ourGoal = new Vector2D(-3010, 0);
//public static Vector2D oppGoal = new Vector2D(3010, 0);
//public static Vector2D Center = new Vector2D(0, 0);
//public static Vector2D oppPenalty = new Vector2D(2560, 0);
//public static Vector2D ourPenalty = new Vector2D(-2560, 0);

//public static Vector2D ourGoal_R = new Vector2D(-3010, 350);
//public static Vector2D ourGoal_L = new Vector2D(-3010, -350);

//public static Vector2D oppPenalty_Shoot = new Vector2D(3010, 500);

//public static Vector2D MidField_R = new Vector2D((-ConstVars.ROBOT_RADIUS)*2.5, -1800);
//public static Vector2D MidField_L = new Vector2D((-ConstVars.ROBOT_RADIUS)*2.5, 1800);

//public static Vector2D P1 = new Vector2D(-2510, 175);
//public static Vector2D P2 = new Vector2D(-2510, -175);

//public static double BALL_OBSTACLE = ROBOT_RADIUS * 2;
//public static double PASS_RADIUS = 2000;

//public static double MAX_KICKABLE_DISTANCE = ROBOT_RADIUS + 30;
//public static double MAX_KICKABLE_ANGLE = 20*System.Math.PI/180;

//public static double HEADING_ANGLE_TRESHOLD = System.Math.PI/3;
//public static double MAX_AHEAD_OPP_DISTANCE = 200;

#endif // CONSTANTS_H
