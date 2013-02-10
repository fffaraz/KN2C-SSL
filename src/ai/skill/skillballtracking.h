#ifndef SKILLBALLTRACKING_H
#define SKILLBALLTRACKING_H

#include <QObject>
#include "skill.h"

class SkillBallTracking : public Skill
{
    Q_OBJECT
public:
    explicit SkillBallTracking(WorldModel* wm, QObject *parent = 0);
    bool execute(RobotCommand& rc);
    bool SkillDone();
    void setFace(Vector2D face){_face = face;}
    void setMaxDist(double maxdist) { _maxdist=maxdist; }
private:
    Vector2D _face;
    double _maxdist;
};

#endif // SKILLBALLTRACKING_H
