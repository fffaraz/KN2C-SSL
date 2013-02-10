#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <QObject>
#include <QTimer>
#include "base.h"
#include "constants.h"
#include "serialport.h"
#include "outputbuffer.h"

class OutputBuffer;

class Transmitter : public QObject
{
    Q_OBJECT
public:
    explicit Transmitter(QString port, OutputBuffer* buffer, QObject *parent = 0);

private:
    SerialPort _serialport;
    QTimer _timer;
    bool _state;
    OutputBuffer* _buffer;

public slots:
    void Start();
    void Stop();

private slots:
    void sendPacket();

};

#endif // TRANSMITTER_H
