#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QObject>


// Finite-state machine
class StateMachine : public QObject
{
    Q_OBJECT
public:
    explicit StateMachine(QObject *parent = 0);

signals:

public slots:

};

#endif // STATEMACHINE_H
