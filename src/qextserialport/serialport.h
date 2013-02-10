#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include <QObject>
#include <QtCore>
#include <QtDebug>
#include "qextserialport.h"
#include "qextserialenumerator.h"

class SerialPort : public QObject
{
Q_OBJECT
public:
    SerialPort(const QString & portName, QObject *parent = 0);
    static QString ListPorts();

//private:
    QextSerialPort *port;

private slots:
    void onReadyRead();
    void onDsrChanged(bool status);

};

#endif /*SERIALPORT_H_*/
