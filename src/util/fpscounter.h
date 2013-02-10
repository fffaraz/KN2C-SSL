#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <QObject>
#include <QTimer>
#include <assert.h>

class FPSCounter : public QObject
{
    Q_OBJECT
public:
    explicit FPSCounter(QObject *parent = 0, uint fpsinterval = 1000);
    quint64 TotalCounter();
    quint32 FPS();

private:
    quint64 _totalcounter;
    quint32 _fpscounter;
    quint32 _lastfps;
    quint32 _lastfps_val;
    QTimer _resettimer;
    uint _fpsinterval;

signals:

public slots:
    void Pulse();

private slots:
    void resetFPSCounter();

};

#endif // FPSCOUNTER_H
