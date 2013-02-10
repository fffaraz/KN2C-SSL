#ifndef GRSIM_H
#define GRSIM_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include "base.h"
#include "grSim_Packet.pb.h"
#include "outputbuffer.h"

class OutputBuffer;

class grSim : public QObject
{
    Q_OBJECT
public:
    explicit grSim(QString ip, int port, TeamColorType color, OutputBuffer* buffer, QObject *parent = 0);

private:
    QUdpSocket _socket;
    QTimer _timer;
    bool _isYellow;
    bool _state;
    OutputBuffer* _buffer;

signals:

public slots:
    void Start();
    void Stop();

private slots:
    void sendPacket();


};

#endif // GRSIM_H
