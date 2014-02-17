#include "formationparser.h"

QList<FormationData>* FormationParser::parse(QString fileName)
{
    QList<FormationData> * formationList = new QList<FormationData>();

    QFile formationFile(fileName);
    if(formationFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&formationFile);
        qDebug() << "Formation for " << in.readLine() << " Robots!";

        while(!in.atEnd())
        {
            QString str = in.readLine();
            FormationData newData(str);
            formationList->append(newData);
        }
    }

    return formationList;
}
