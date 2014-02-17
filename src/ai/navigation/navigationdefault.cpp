#include "navigationdefault.h"

#define plusX 3025
#define plusY 2025

#define rrtAttempts 1000

NavigationDefault::NavigationDefault(WorldModel *wm, QObject *parent) :
    Navigation(wm, "NavigationDefault", parent)
{

}

bool NavigationDefault::execute(int rid, Position FinalPos, Position &Solution, float &RobotSpeed, bool ballAsObstacle)
{
    _plannerInitGoal->setInitVector(_wm->ourRobot[rid].pos.loc.x + plusX,
                                    _wm->ourRobot[rid].pos.loc.y + plusY);
    _plannerInitGoal->setGoalVector(FinalPos.loc.x + plusX,
                                    FinalPos.loc.y + plusY);

    _plannerGoalInit->setInitVector(FinalPos.loc.x + plusX,
                                    FinalPos.loc.y + plusY);
    _plannerGoalInit->setGoalVector(_wm->ourRobot[rid].pos.loc.x + plusX,
                                    _wm->ourRobot[rid].pos.loc.y + plusY);

    if (FinalPos.loc.dist(_wm->ourRobot[rid].pos.loc) < ROBOT_RADIUS)
    {
        Solution.loc.x = FinalPos.loc.x;
        Solution.loc.y = FinalPos.loc.y;
        Solution.dir = FinalPos.dir;
        RobotSpeed = 1;
#if NAVIGATION_DEBUG
        qDebug() << "Robot(" << rid << ") Reached to Final Position";
#endif
        return true;
    }

    _plannerInitGoal->clearObstacle();
    _plannerGoalInit->clearObstacle();

    Obstacles obstacles;
    Obstacle::indexProvider = 0;

//    for (int i = 0; i < PLAYERS_MAX_NUM; i ++)
//    {
//        if (_wm->oppRobot[i].isValid)
//        {
//            obstacles.push_back(
//                        new Obstacle(new Circle2D(_wm->oppRobot[i].pos.loc + Vector2D(plusX, plusY),
//                                                  ROBOT_RADIUS * 2)));
//        }

//        if (i != rid &&
//                _wm->ourRobot[i].isValid)
//        {
//            obstacles.push_back(
//                        new Obstacle(new Circle2D(_wm->ourRobot[i].pos.loc + Vector2D(plusX, plusY),
//                                                  ROBOT_RADIUS * 2)));
//        }
//    }

    if (rid != GOALIE_ID) // Not goalie
        obstacles.push_back(new Obstacle(new Circle2D(Vector2D(0,FIELD_MAX_Y), PARALLEL_LINE_LENGTH/2+PENALTY_AREA_RADIUS+ROBOT_RADIUS+50)));

    //rects_out_of_pitch
    /*
         ______________________________
        |_|__________________________|_|
        | |                          | |
        | | OUT OF PITCH             | |
        | |            AS            | |
        | |             OBSTACLE     | |
        |_|__________________________|_|
        |_|__________________________|_|
     */

    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(1000,-200), Size2D(2 * FIELD_MAX_X - 2000, 200))));
    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(1000, 2 * FIELD_MAX_Y), Size2D(2 * FIELD_MAX_X - 2000, 200))));
    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(-200, 500), Size2D(200, 2 * FIELD_MAX_Y - 1000))));
    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(2 * FIELD_MAX_X, 500), Size2D(200, 2 * FIELD_MAX_Y - 1000))));

    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(-200, -200), Size2D(1200, 100))));
    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(-200, 2 * FIELD_MAX_Y + 100), Size2D(1200, 100))));
    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(-200, -200), Size2D(100, 700))));
    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(-200, 2 * FIELD_MAX_Y + 100), Size2D(100, 700))));

    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(2 * FIELD_MAX_X - 1000, -200), Size2D(1200, 100))));
    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(2 * FIELD_MAX_X + 100, -200), Size2D(100, 700))));
    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(2 * FIELD_MAX_X - 1000, 2 * FIELD_MAX_Y - 100), Size2D(1200, 100))));
    obstacles.push_back(new Obstacle(new Rect2D(Vector2D(2 * FIELD_MAX_X + 100, 2 * FIELD_MAX_Y - 500), Size2D(100, 700))));

    //ball_as_obstacle
    if ( _wm->ball.isValid)
        obstacles.push_back(
                    new Obstacle(new Circle2D(_wm->ball.pos.loc + Vector2D(plusX, plusY),
                                              BALL_RADIUS + ROBOT_RADIUS + 10)));

#if NAVIGATION_DEBUG
    qDebug() << "---------------------------------------------";
#endif
    foreach(Obstacle* ob, obstacles)
    {
#if NAVIGATION_DEBUG
        Circle2D* cir = static_cast<Circle2D*>(ob->region());

        qDebug() << "Circle2D : "
                 << "Center : (" << cir->center().x << "," << cir->center().y << "),"
                 << "Radius : " << cir->radius();
#endif

        _plannerInitGoal->addObstacle(ob);
        _plannerGoalInit->addObstacle(ob);
    }

    if (_plannerInitGoal->buildRRT(_plannerGoalInit, rrtAttempts))
    {
        Solution.loc.x = _plannerInitGoal->treeNodes().first()->position()->x - plusX;
        Solution.loc.y = _plannerInitGoal->treeNodes().first()->position()->y - plusY;
        Solution.dir = FinalPos.dir;
        RobotSpeed = 1;
#if NAVIGATION_DEBUG
        qDebug() << "I am in (" << _wm->ourRobot[rid].pos.loc.x + plusX << "," << _wm->ourRobot[rid].pos.loc.y + plusY << ").";
        qDebug() << "I want to go to (" << FinalPos.loc.x + plusX << "," << FinalPos.loc.y + plusY << ").";
        qDebug() << "According to RRT, I should go to (" << Solution.loc.x + plusX << "," << Solution.loc.y + plusY<< ").";
#endif
    }
    else
    {
        Solution.dir = FinalPos.dir;
        Solution.loc.x = FinalPos.loc.x;
        Solution.loc.y = FinalPos.loc.y;
        Solution.dir = FinalPos.dir;
        RobotSpeed = 1;
#if false
        qDebug() << "RRT has no result!";
#endif
    }

    return true;
}

