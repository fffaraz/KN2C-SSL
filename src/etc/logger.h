#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QtCore>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = 0);

signals:

public slots:
    void log(QString message);

};

#endif // LOGGER_H
