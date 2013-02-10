#include "grsim.h"

grSim::grSim(QString ip, int port, TeamColorType color, OutputBuffer* buffer, QObject *parent) :
    QObject(parent),
    _socket(this),
    _timer(this),
    _buffer(buffer)
{
    qDebug() << "grSim Initialization...";
    _isYellow = (color==COLOR_YELLOW)?true:false;
    _socket.connectToHost(QHostAddress(ip), port);
    _timer.setInterval(20);
    connect(&_timer,SIGNAL(timeout()), this, SLOT(sendPacket()));

    // Log
    qDebug() << "IP: " << ip;
    qDebug() << "Port: " << port;
}

void grSim::Start()
{
    qDebug() << "grSim::Start";
    _timer.start();
}

void grSim::Stop()
{
    qDebug() << "grSim::Stop";
    _timer.stop();
}

void grSim::sendPacket()
{
    grSim_Packet pck = _buffer->grpck.GetPacket();
    pck.mutable_commands()->set_timestamp(0.0);
    pck.mutable_commands()->set_isteamyellow(_isYellow);
    std::string s;
    pck.SerializeToString(&s);
    _socket.write(s.c_str(), s.length());
}
