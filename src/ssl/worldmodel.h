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
#include "formationdata.h"
#include "geom/formation_dt.h"
#include "game_state_our_UI.h"

class WorldModel
{
public:
    explicit WorldModel();
    PlayMode playMode();
    int goalsOpp();
    int goalsOur();
    void updatePlayMode();
    Vector2D position(int _rid, int activeRobots, Vector2D focusPoint, PlayMode pm);

    bool canKick();

public:
    double time;
    Ball ball;
    Robot ourRobot[PLAYERS_MAX_NUM];
    Robot oppRobot[PLAYERS_MAX_NUM];
    GameStatePacket refgs;
    GameStateType gs;
    GameStateType gs_last;
    GameState cmgs;

    //Formations
    FormationDT *sixNormalFormation;
    FormationDT *sixFreeKickOurFormation;
    FormationDT *sixFreeKickOppFormation;

    FormationDT *fiveNormalFormation;
    FormationDT *fiveFreeKickOurFormation;
    FormationDT *fiveFreeKickOppFormation;

    int slider[4];
    bool referee_our_ui;
    PlayMode lastMode;

private:
    PlayMode _playMode;
    bool _canKick;
    char ui_state;
    bool ui_ball_moved;
   public:
       char get_ui_state(){return ui_state;}
       bool get_ui_ball_moved(){return ui_ball_moved;}
       void set_ui_state(char ui_state,bool ui_ball_moved){this->ui_state=ui_state;
                                                           this->ui_ball_moved=ui_ball_moved;}
   };


#endif // WORLDMODEL_H
