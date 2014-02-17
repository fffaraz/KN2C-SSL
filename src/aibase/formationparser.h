#ifndef FORMATIONPARSER_H
#define FORMATIONPARSER_H

#include "knowledge.h"
#include "worldmodel.h"
#include <QFile>

class FormationParser
{
public:
    FormationParser()
        {  }

public:
    QList<FormationData>* parse(QString fileName);
};

#endif // FORMATIONPARSER_H
