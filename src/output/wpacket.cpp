#include "wpacket.h"

WPacket::WPacket()
{
}

void WPacket::Clear()
{
    _rdata.clear();
}

void WPacket::AddRobot(RobotData rd)
{
    //rd.RID = htons(rd.RID); // RID was 2 bytes before
    //_rdata.append(rd);
    _rdata[rd.RID]=rd;
}

QByteArray WPacket::GetPacket()
{
    QByteArray rd;
    //for(int i=0; i<_rdata.count(); ++i)
    //    rd.append((const char*)&(_rdata[i]), 8); //sizeof(_rdata[i]));
    foreach(const RobotData& itr, _rdata)
        rd.append((const char*)&(itr), 8); //sizeof(i));

    unsigned char checksum=0;
    for(int i=0; i<rd.size(); ++i)
        checksum += rd.at(i);

    SendPacketHeader h;
    h.NOR = _rdata.count();
    h.SIB = 2 + 3 + rd.size() + 1; //RobotData size + 3 byte packet header + 2 byte SOP + 1 byte EOP
    h.CHK = checksum;

    QByteArray ans;
    ans.append(WP_SOP);
    ans.append((const char*)&h, 3); //sizeof(h));
    ans.append(rd);
    ans.append(WP_EOP);

    //qDebug() << ans.toHex();

    // !!!
    Clear();
    return ans;
}
