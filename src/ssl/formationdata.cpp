#include "formationdata.h"
#include <QDebug>

FormationData::FormationData(QString data)
{
    QStringList temp;
    temp = data.split("=");
    index = temp[0].toInt();
    data = temp[1];
    QRegExp regExp("[(][-]?[0-9]*\\.?[0-9]*,[-]?[0-9]*\\.?[0-9]*[)]");
    if(regExp.indexIn(data)!=-1)
    {
        QString t = regExp.cap(0);
        data = data.mid(t.length());
        ball.x = t.mid(1,t.indexOf(",")-1).toDouble();
        t = t.mid(t.indexOf(",")+1);
        t = t.mid(0,t.length()-1);
        ball.y = t.toDouble();
    }
    while(regExp.indexIn(data)!=-1)
    {
        QString t = regExp.cap(0);
        data = data.mid(t.length());
        Vector2D vec;
        vec.x = t.mid(1,t.indexOf(",")-1).toDouble();
        t = t.mid(t.indexOf(",")+1);
        t = t.mid(0,t.indexOf(")"));
        vec.y = t.toDouble();
        robots.append(vec);
    }
}
