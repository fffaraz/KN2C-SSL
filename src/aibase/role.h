#ifndef ROLE_H
#define ROLE_H

#include <QObject>

class Role : public QObject
{
    Q_OBJECT
public:
    explicit Role(QString name, QObject *parent = 0);
    QString Name() { return _name; }

protected:
    QString _name;

signals:

public slots:

};

#endif // ROLE_H
