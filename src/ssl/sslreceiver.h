#ifndef SSLRECEIVER_H
#define SSLRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include "fpscounter.h"

class SSLReceiver : public FPSCounter
{
    Q_OBJECT
public:
    explicit SSLReceiver(QString ip, int port, QObject *parent = 0);

private:
    QUdpSocket _udpsocket;
    bool _isStarted;

signals:
    void newReceivedPacket(QByteArray data, QString ip, int port);

public slots:
    void Start();
    void Stop();

private slots:
    void readPendingDatagrams();

};

#endif // SSLRECEIVER_H
