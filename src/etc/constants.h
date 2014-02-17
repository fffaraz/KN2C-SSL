#ifndef CONSTANTS_H
#define CONSTANTS_H

// Math Constans
#define EPS 1.0E-6

// Global constants
#define PLAYERS_MAX_NUM 12
#define FIELD_MAX_X 3025.0
#define FIELD_MAX_Y 2025.0
#define GOAL_HALF_LENGTH 350.0
#define PARALLEL_LINE_LENGTH 350.0
#define BALL_RADIUS 20.0
#define ROBOT_RADIUS 85.0
#define PENALTY_AREA_RADIUS 800.0

#define PASS_MAX_DIST 5000.0
#define PASS_MIN_DIST 300

// Speeds
#define PLAYER_MAX_SPEED 4000.0 / 30.0
#define BALL_DECAY 360.0 / 30.0

#define BALL_OUR_SPEED 5000.0 / 30.0
#define BALL_MAX_SPEED 8000.0 / 30.0

#define PASS_KICK_MAX_TRAVEL 4000

#define KICKER_DIST_TO_ROBOT_CENTER 55

#define SHOOT_KICK_SPEED 4
#define PASS_KICK_SPEED 2

// Default Robot ID
#define GOALIE_ID 0
#define OPP_GOALIE_ID 0

// Debug Modes
#define RRT_DEBUG false
#define SKILL_DEBUG false
#define TACTIC_DEBUG false
#define BEHAVIOR_DEBUG false
#define NAVIGATION_DEBUG false

// Vision constants
#define CAMERA_OFFSET 250.0
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

#endif // CONSTANTS_H
