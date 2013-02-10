#ifndef OUTPUTBUFFER_H
#define OUTPUTBUFFER_H

#include <QObject>
#include "wpacket.h"
#include "grpacket.h"
#include "controller.h"

class Controller;

class OutputBuffer //: public QObject
{
    // Q_OBJECT
public:
    WPacket wpck;
    grPacket grpck;
    Controller* ctrl;
    void Clear()
    {
        wpck.Clear();
        grpck.Clear();
    }
};

#endif // OUTPUTBUFFER_H
