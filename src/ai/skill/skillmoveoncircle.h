#ifndef SKILLMOVEONCIRCLE_H
#define SKILLMOVEONCIRCLE_H

#include <QObject>
#include "skill.h"

class SkillMoveOnCircle : public Skill
{
    Q_OBJECT
public:
    explicit SkillMoveOnCircle(WorldModel* wm, QObject *parent = 0);
    virtual bool execute(RobotCommand& rc);
    virtual bool done();

    void setCenter(Vector2D center) { _center = center; }
    void setEnd (Vector2D end) { _end = end; }
    void setTarget(Vector2D target) { _target = target; }
    void setRadius(float radius) { _radius = radius; }

private:
    Vector2D _center;
    Vector2D _end;
    Vector2D _target;

    float _radius;
};

#endif // SKILLMOVEONCIRCLE_H
