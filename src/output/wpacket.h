#ifndef WPACKET_H
#define WPACKET_H

#include <QList>
#include <QByteArray>
#include <QDebug>

#include <netinet/in.h>

#define WP_SOP QByteArray::fromHex("a55a") // Start of Packet
#define WP_EOP QByteArray::fromHex("80")   // End   of Packet


// disable padding
#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

struct SendPacketHeader
{
    //unsigned short SOP;	// start of packet (2 bytes)
    unsigned char SIB;	// size in bytes
    unsigned char NOR;	// number of robots
    unsigned char CHK;	// ckeck sum
    //RobotData R[6];
    //unsigned char EOP;	// end of packet
};

struct RobotData
{
    unsigned char RID;	// robot id
    signed char M1;	// motor 1
    signed char M2;	// motor 2
    signed char M3;	// motor 3
    signed char M4;	// motor 4
    unsigned char KCK;	// kick options
    unsigned char FLG;	// flags
    unsigned char ASK;	// ask

    RobotData() :
        RID(0xFF),
        M1(0),
        M2(0),
        M3(0),
        M4(0),
        KCK(0),
        FLG(0),
        ASK(0)
    { }
};
#pragma pack(pop)   /* restore original alignment from stack */

class WPacket
{
public:
    WPacket();
    void AddRobot(RobotData rd);
    QByteArray GetPacket();
    void Clear();

private:
    QMap<int,RobotData> _rdata;
};

#endif // WPACKET_H
