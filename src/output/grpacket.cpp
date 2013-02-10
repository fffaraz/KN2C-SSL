#include "grpacket.h"

grPacket::grPacket()
{
}

void grPacket::Clear()
{
    _rdata.clear();
}

void grPacket::AddRobot(grRobotData rd)
{
    _rdata[rd.rid]=rd;
}

grSim_Packet grPacket::GetPacket()
{
    grSim_Packet pck;
    foreach(const grRobotData& itr, _rdata)
    {
        grSim_Robot_Command* rcmd = pck.mutable_commands()->add_robot_commands();
        // we are using vx,vy,vw instead of motor speeds
        rcmd->set_wheelsspeed(false);
        rcmd->set_id(itr.rid);
        rcmd->set_veltangent(itr.velx);
        rcmd->set_velnormal(itr.vely);
        rcmd->set_velangular(itr.velw);
        rcmd->set_kickspeedx(itr.kickspeedx);
        rcmd->set_kickspeedz(itr.kickspeedz);
        rcmd->set_spinner(itr.spinner);
        rcmd->set_wheel1(itr.wheel1);
        rcmd->set_wheel2(itr.wheel2);
        rcmd->set_wheel3(itr.wheel3);
        rcmd->set_wheel4(itr.wheel4);
    }
    // !!!
    Clear();
    return pck;
}
