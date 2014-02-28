#include "logger.h"

Logger::Logger(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Logger Initialization...";
}

void Logger::log(QString message)
{
    qDebug() << message;
}
