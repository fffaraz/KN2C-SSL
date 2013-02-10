#ifndef GRPACKET_H
#define GRPACKET_H

#include <QList>
#include <QByteArray>
#include <QDebug>
#include "grSim_Packet.pb.h"

struct grRobotData
{
    int rid;
    float kickspeedx;
    float kickspeedz;
    float velx;
    float vely;
    float velw;
    bool spinner;
    float wheel1;
    float wheel2;
    float wheel3;
    float wheel4;

    grRobotData()
    {
        rid=0;
        kickspeedx=0;
        kickspeedz=0;
        velx=0;
        vely=0;
        velw=0;
        spinner=0;
        wheel1=0;
        wheel2=0;
        wheel3=0;
        wheel4=0;
    }
};

class grPacket
{
public:
    grPacket();
    void AddRobot(grRobotData rd);
    grSim_Packet GetPacket();
    void Clear();

private:
    QMap<int,grRobotData> _rdata;

};

#endif // GRPACKET_H
