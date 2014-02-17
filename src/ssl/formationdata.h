#ifndef FORMATIONDATA_H
#define FORMATIONDATA_H

#include <vector_2d.h>
#include <QList>
#include <QString>
#include <QRegExp>
#include <QStringList>

class FormationData
{
public:
    FormationData(QString data);

public:
    Vector2D ball;
    QList <Vector2D> robots;
    int index;
};

#endif // FORMATIONDATA_H
