#include "knowledge.h"
#include "strategy.h"

#include <limits>

Knowledge::Knowledge(WorldModel *wm, QObject *parent) :
    QObject(parent),
    _wm(wm)
{
    validGoalie = false;
}

int Knowledge::countActiveAgents()
{
    int counter = 0;

    for(int i = 0; i < PLAYERS_MAX_NUM; i ++)
        if(_wm->ourRobot[i].isValid)
            counter++;

    return counter;
}

int Knowledge::countActiveRoles()
{
    int roles = countActiveAgents();

    if (!isGoalieValid())
        roles++;

    return roles;
}

QList<int> Knowledge::activeAgents()
{
    QList<int> ans;

    for(int i = 0; i < PLAYERS_MAX_NUM; i ++)
        if(_wm->ourRobot[i].isValid)
            ans.append(i);

    return ans;
}

QList<int> Knowledge::findNearestTo(Vector2D loc)
{
    QMap<double, int> sMap;
    for(int i = 0; i < PLAYERS_MAX_NUM; i ++)
    {
        if(!_wm->ourRobot[i].isValid)
            continue;

        double dist = (_wm->ourRobot[i].pos.loc - loc).length();
        sMap.insert(dist, i);
    }

    QList<int> ans;
    for(auto i=sMap.begin(); i!=sMap.end(); i++)
        ans.append(i.value());

    return ans;
}

int Knowledge::findNearestOpponentToBall()
{
    int ans = 0;
    double minDist = std::numeric_limits< float >::max();
    for(int i = 0; i < PLAYERS_MAX_NUM; i ++)
    {
        if(!_wm->oppRobot[i].isValid)
            continue;

        double dist = (_wm->oppRobot[i].pos.loc - _wm->ball.pos.loc).length();

        if(dist<minDist)
        {
            minDist = dist;
            ans = i;
        }
    }

    return ans;
}

/**
 * @brief Knowledge::findNearestTeammateToPointByStaticPosition
 * @param point target_position
 * @param pm PlayMode
 * @return Index of teammate nearest to point.
 */
int Knowledge::findNearestTeammateToPointByStaticPosition(Vector2D point, PlayMode pm)
{
    double minDist = std::numeric_limits< float >::max();
    int roles = countActiveRoles();
    int ans = -1;

    for (int index = 0; index < roles; index ++)
    {
        Vector2D staticPosition = _wm->position(index, roles, _wm->ball.pos.loc, pm);
        double dist = (staticPosition - point).r();

        if (dist < minDist)
        {
            minDist = dist;
            ans = index;
        }
    }

    return ans;
}

int Knowledge::findNearestTeammateToPoint(Vector2D point)
{
    int ans = -1;
    double minDist = std::numeric_limits< float >::max();
    for (int i = 0 ; i < PLAYERS_MAX_NUM ; i ++)
    {
        if (!_wm->ourRobot[i].isValid)
            continue;

        double dist = (_wm->ourRobot[i].pos.loc - point).length();
        if (dist < minDist)
        {
            minDist = dist;
            ans = i;
        }
    }

    return ans;
}

bool Knowledge::isBallKickable(int Rid)
{
    Position robotPos = _wm->ourRobot[Rid].pos;
    Position ballPos = _wm->ball.pos;
    if(ballPos.loc.dist(robotPos.loc) <= ROBOT_RADIUS + BALL_RADIUS + 5 &&
            ballPos.loc.dist(robotPos.loc) >= ROBOT_RADIUS &&
            abs(ballPos.dir - robotPos.dir) <10)
        return true;
    else
        return false;

}

int Knowledge::ballKicker()
{
    int index = -1;
    float minDist = std::numeric_limits< float >::max();

    for (int id = 0; id < PLAYERS_MAX_NUM; id ++)
    {
        if (!_wm->ourRobot[id].isValid)
            continue;

        float dist = _wm->ourRobot[id].pos.loc.dist(_wm->ball.pos.loc);
        if (dist < minDist)
        {
            minDist = dist;
            index = id;
        }
    }

    return minDist < 100+ROBOT_RADIUS+BALL_RADIUS ? index : -1;
}

Vector2D Knowledge::findNearestPositionToRobot(QList<Vector2D> positions, int rid)
{
    Vector2D robotPos = _wm->ourRobot[rid].pos.loc;
    Vector2D pos = positions[0];
    double minDist = robotPos.dist(pos);
    int ansIndex = 0;

    for (int cnt = 1 ; cnt<positions.count() ; cnt++)
    {
        pos = positions[cnt];
        if (robotPos.dist(pos)<minDist)
        {
            minDist = robotPos.dist(pos) ;
            ansIndex = cnt;
        }
    }

    return positions.at(ansIndex);
}

bool Knowledge::findNearestPointToDummy(Vector2D point,int rid)
{
    int ans=-1;
    float minDist = std::numeric_limits< float >::max();

    for (int i = 0 ; i < PLAYERS_MAX_NUM ; i ++)
    {
        if (!_wm->ourRobot[i].isValid)
            continue;

        double dist = (_wm->ourRobot[i].pos.loc - point).length();

        if (dist < minDist )
        {
            minDist = dist;
            ans = i;
        }
    }

    return true;
}

bool Knowledge::isGoalieValid()
{
    return validGoalie;
}

bool Knowledge::isInPenaltyArea(Vector2D vec)
{
    Rect2D rect(Vector2D(-FIELD_MAX_X,-PARALLEL_LINE_LENGTH/2) , Size2D(PENALTY_AREA_RADIUS,PARALLEL_LINE_LENGTH));
    if (rect.contains(vec))
        return true;
    Sector2D sector1(Vector2D(-FIELD_MAX_X,PARALLEL_LINE_LENGTH/2),0,PENALTY_AREA_RADIUS,90,0),sector2(Vector2D(-FIELD_MAX_X,-PARALLEL_LINE_LENGTH/2),0,PENALTY_AREA_RADIUS,0,-90);
    if (sector1.contains(vec) || sector2.contains(vec))
        return true;
    return false;
}

int Knowledge::findOpponentKicker()
{
    for (int i = 0 ; i < PLAYERS_MAX_NUM ; i++)
    {
        if (!_wm->oppRobot[i].isValid)
            continue;
        if (_wm->oppRobot[i].pos.loc.dist(_wm->ball.pos.loc) < ROBOT_RADIUS+BALL_RADIUS+100)
            return i;
    }
    return -1;
}
