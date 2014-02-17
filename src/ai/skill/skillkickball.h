#ifndef SKILLKICKBALL_H
#define SKILLKICKBALL_H

#include <QObject>
#include "skill.h"

class SkillKickBall: public Skill
{
    Q_OBJECT
public:
    SkillKickBall(WorldModel *wm, QObject *parent = 0);

    bool execute(RobotCommand& rc);
    bool done();

    void setKickPosition(Position kickPos) { _kickPos = kickPos; }
    void setSpeedX(float speedX) { _speedX = speedX; }
    void setSpeedZ(float speedZ) { _speedZ = speedZ; }

private:
    Position _kickPos;
    float _speedX;
    float _speedZ;
    bool _done;
};

#endif // SKILLKICKBALL_H
