#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QTimer>

class Counter : public QObject
{
    Q_OBJECT
public:
    explicit Counter(QObject *parent = 0, uint interval = 1000);
    quint64 totalCount();
    quint32 perSecond();

private:
    QTimer timer;
    quint64 totalcount;
    quint32 pscounter;
    quint32 pscounter_last;
    quint32 interval;

public slots:
    void pulse();

private slots:
    void timer_timeout();

};

#endif // COUNTER_H
