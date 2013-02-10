#include "sslreceiver.h"

SSLReceiver::SSLReceiver(QString ip, int port, QObject *parent) :
    FPSCounter(parent),
    _udpsocket(this),
    _isStarted(false)
{
    // udp socket setup
    bool result;
    result=_udpsocket.bind(QHostAddress::Any,port, QUdpSocket::ReuseAddressHint);
    if(!result) qDebug() << _udpsocket.errorString();
    result=_udpsocket.joinMulticastGroup(QHostAddress(ip));
    if(!result) qDebug() << _udpsocket.errorString();
}

void SSLReceiver::Start()
{
    if(_isStarted) return;
    connect(&_udpsocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    _isStarted=true;
}

void SSLReceiver::Stop()
{
    if(!_isStarted) return;
    disconnect(&_udpsocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    _isStarted=false;
}

void SSLReceiver::readPendingDatagrams()
{
    while (_udpsocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udpsocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        _udpsocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        newReceivedPacket(datagram,sender.toString(),senderPort);
        Pulse();
    }
}

