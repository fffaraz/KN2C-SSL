#include "controller.h"
#include "constants.h"
#include <QTime>
Controller::Controller(ScriptEngine *engine, QObject *parent) :
    QObject(parent),
    _engine(engine)
{
    //qDebug() << "Controller Initialization...";
    // _engine->AddObject(_outbuffer, "outbuffer");
    MAXMOTORSRPM = 450;
    WHEELDIAMETER = 0.060;
    ROBOTRADIUS = 0.090;

    for(int i=0; i<PLAYERS_MAX_NUM; i++)
    {
        err[i]=1;
        PastDist[i] = Vector2D(0,0);
    }
}

ControllerResult Controller::calc(Position curpos, Position curvel, Position target, int rid, float fdest, float speed)
{
    // filling controller data
    ControllerData ctrldata;
    ctrldata.curpos=curpos;
    ctrldata.curvel=curvel;
    ctrldata.target=target;
    ctrldata.rid=rid;
    ctrldata.fdest=fdest;
    ctrldata.speed=speed;

    // scripts
    //_engine->AddObject(&ctrldata, "ctrl");
    //_engine->evalFile("controller.js");
    //qDebug() << _engine->evalFile("controller.js").toString();

    // calc robot speed & motor speeds
    RobotSpeed rs = calcRobotSpeed(ctrldata);
    MotorSpeed ms3 = calcMotorSpeed3(rs);
    MotorSpeed ms4 = calcMotorSpeed4(rs);

    // make result
    ControllerResult ctrlresult;
    ctrlresult.rs = rs;
    ctrlresult.ms3 = ms3;
    ctrlresult.ms4 = ms4;

    return ctrlresult;
}

RobotSpeed Controller::calcRobotSpeed(ControllerData& data)
{
    float MAXROBOTSPEED = MAXMOTORSRPM * M_PI * WHEELDIAMETER * cos(M_PI / 6) / 60;
    float MAXROTATIONSPEED = MAXMOTORSRPM * WHEELDIAMETER / (60 * ROBOTRADIUS * 2);
    float ROBOTSPEED;
    float RotationSpeed;
    static bool flg = false;
    static double saved_data[12][100][2];

//        data.target.loc = Vector2D(0,0);
//        data.target.dir = M_PI/2;
    if(!flg)
    {
        for(int i=0;i<12;i++)
            for(int j=0;j<100;j++)
                for(int k=0;k<2;k++)
                    saved_data[i][j][k] =0;
        flg = true;
    }
    double tmp1=0,tmp2=0;

    for(int i =99;i>0;i--)
    {
        saved_data[data.rid][i][0] = saved_data[data.rid][i-1][0];
        tmp1 += saved_data[data.rid][i][0];
    }
    saved_data[data.rid][0][0] = data.curvel.loc.x;
    tmp1 +=saved_data[data.rid][0][0];

    for(int i =99;i>0;i--)
    {
        saved_data[data.rid][i][1] = saved_data[data.rid][i-1][1];
        tmp2 += saved_data[data.rid][i][1];
    }
    saved_data[data.rid][0][1] = data.curvel.loc.y;
    tmp2 += saved_data[data.rid][0][1];


    Vector2D norm_vel = Vector2D(tmp1,tmp2);



    //    if (data.rid == 0)
    //        qDebug()<<"vel:"<< data.curvel.loc.length()<<"Norm: "<<Vector2D(tmp1,tmp2).length()/100;



    /******************************Linear Speed Controller************************************/
    Vector2D DistanceVector = (data.target.loc - data.curpos.loc);
    DistanceVector.scale(.001);




    /*





    double tmp;
    static Vector2D m = Vector2D(0,0);
    // tmp = (PastDist.length())/DistanceVector.length();
    tmp = PastDist[data.rid].length() - DistanceVector.length();
    if(fabs(tmp) > .0001 && DistanceVector.length()>.01 )
    {
//        tmp= .15*  .001*err[data.rid]*(AGENT_TIMER/tmp) + 1*DistanceVector.length();//*a+DistanceVector.length();
//        if (fabs(tmp)<100000 || fabs(tmp) < fabs(err[data.rid]))
//            err[data.rid]=tmp;

            err[data.rid]+=tmp;


    }
    m+= DistanceVector;
    //  if(!std::isnan(tmp))
    //  {
    //     a = 4*a*(tmp-.9) + 1*DistanceVector.length();
    //
    if (data.rid ==0)
    qDebug()<<"A:"<<err[data.rid]<<m.length()<<norm_vel.length()<<DistanceVector.length();

    //else
    //   a= .019*  .001*a*40000 + DistanceVector.length();

    //qDebug()<<"diss: "<<(AGENT_TIMER/tmp);
    /*   if( !std::isnan(DistanceVector.length()/data.curvel.loc.length())\
           && !std::isinf(DistanceVector.length()/data.curvel.loc.length()))
    {
        ROBOTSPEED = .5*DistanceVector.length()/data.curvel.loc.length();
     //   qDebug()<<"robs: "<<ROBOTSPEED<<data.curvel.loc.length()<<DistanceVector.length();
    }* /
    //qDebug()<<"Speed:"<<data.curvel.loc.length();
    PastDist[data.rid] = DistanceVector;
    //PastTime = t.elapsed();
    //qDebug()<<"cirvel:"<<data.curvel.dir;
    if( !std::isnan(DistanceVector.length()/norm_vel.length())\
            && !std::isinf(DistanceVector.length()/norm_vel.length())
            && DistanceVector.length()<2)
    {
        if(fabs(err[data.rid])<1000 || norm_vel.length()<.05)
            ROBOTSPEED = 0.9*DistanceVector.length()/norm_vel.length()
                    +.000*err[data.rid];
        else
            ROBOTSPEED = .4;
        //   qDebug()<<"robs: "<<ROBOTSPEED<<data.curvel.loc.length()<<DistanceVector.length();
    }
    else ROBOTSPEED=1;
    //qDebug()<<"RobotSpeed:"<<ROBOTSPEED;

    Vector2D LinearSpeed = DistanceVector;

    LinearSpeed.setLength(ROBOTSPEED * MAXROBOTSPEED);

    if (LinearSpeed.length() > MAXROBOTSPEED)
        LinearSpeed.setLength(MAXROBOTSPEED);









    */

    ///* V4
    //double speed;
    //Vector2D LinearSpeed = Vector2D(DistanceVector);
    //if (DistanceVector.length()< .5)
    //                          LinearSpeed.setLength(sqrt(DistanceVector.length())*1.9);// speed = (MAXROBOTSPEED * (DistanceVector.length() / .1));
    //                       else
    //                           speed = MAXROBOTSPEED;
    ////                       if(data.rid == 5) speed *= 3;
    //                       qDebug()<<"maxrobot"<<MAXROBOTSPEED;
    //                   //Vector2D LinearSpeed = Vector2D(DistanceVector);
    //                   LinearSpeed.setLength((double)speed);
    //                   if(!std::isnan(norm_vel.length()))
    //                   LinearSpeed+=(LinearSpeed - data.curvel.loc);

    //                   if (LinearSpeed.length() > MAXROBOTSPEED)
    //                   {
    //                       LinearSpeed.setLength((double)MAXROBOTSPEED);
    //                   }
    //LinearSpeed.setLength(.8);
    //*/

    Vector2D LinearSpeed = Vector2D(DistanceVector);
    if(DistanceVector.length() < .40)
        if(data.curvel.loc.length()<.020)
            LinearSpeed.setLength(sqrt(DistanceVector.length())*.004);//23
        else
            LinearSpeed.setLength(sqrt(DistanceVector.length())*.0023);
    else if(DistanceVector.length() < 1)
        LinearSpeed.setLength(sqrt(DistanceVector.length())*.0018);
    else //if(DistanceVector.length() > 1)
        LinearSpeed.setLength(MAXROBOTSPEED);

    if(data.rid==10)
        //LinearSpeed.scale(6);
        LinearSpeed.setLength(MAXROBOTSPEED);

    if(GRSIM)
    {
        if(DistanceVector.length()<1)
        LinearSpeed.setLength(MAXROBOTSPEED*DistanceVector.length()*2);
        else
            LinearSpeed.setLength(MAXROBOTSPEED);

    }

    if (LinearSpeed.length() > MAXROBOTSPEED)
    {
        LinearSpeed.setLength((double)MAXROBOTSPEED*2);
    }

    //    Vector2D velocity = (LinearSpeed - data.curvel.loc);
    //    velocity.setLength(sqrt((LinearSpeed - data.curvel.loc).length())*.01);
    //    if((LinearSpeed - data.curvel.loc).length()<.09 && DistanceVector.length()>.06)
    //        LinearSpeed+=velocity;
    //    else
    //        LinearSpeed.setLength(0);

    //    if(data.rid== 1)
    //        qDebug()<<"CurVel:" <<LinearSpeed.x<<":"<<LinearSpeed.y;
    //LinearSpeed.setLength(MAXROBOTSPEED);
    Vector2D RotLinearSpeed;
    RotLinearSpeed.x = LinearSpeed.x * cos(data.curpos.dir) + LinearSpeed.y * sin(data.curpos.dir);
    RotLinearSpeed.y = -LinearSpeed.x * sin(data.curpos.dir) + LinearSpeed.y * cos(data.curpos.dir);
    // Rotation Speed Controller
    float difangle = data.target.dir - data.curpos.dir;
    if (difangle > M_PI) difangle -= 2 * M_PI;
    if (difangle < -M_PI) difangle += 2 * M_PI;

    //if (fabs(difangle) < M_PI/2)

    //RotationSpeed = MAXROTATIONSPEED * difangle/(2*M_PI) ;
    if(fabs(difangle) < (5/180)*M_PI)
        RotationSpeed =0;
    else if(fabs(difangle) < 1)
        RotationSpeed =(0.025* sign(difangle)*sqrt(fabs(difangle)))/(2*M_PI) ;
    else if(fabs(difangle) < (3*M_PI)/2)
        RotationSpeed =(.030* sign(difangle))/(2*M_PI) ;
    else
        RotationSpeed =(.03* sign(difangle))/(2*M_PI) ;
//    else
//        RotationSpeed=difangle*0.002;

    if(GRSIM)
    {
       RotationSpeed =(2* sign(difangle))/(2*M_PI) ;

    }


    //qDebug()<<difangle;
    //else
    //RotationSpeed = MAXROTATIONSPEED * sign(difangle);
    // if(DistanceVector.length()>.20)
    //    RotationSpeed =0 ;
    //RotationSpeed = MAXROTATIONSPEED * sign(difangle) ;
    //qDebug()<<"maxrs:"<<MAXROBOTSPEED;
    RobotSpeed ans;
    ans.VX = RotLinearSpeed.x;
    ans.VY = RotLinearSpeed.y;
    ans.VW = RotationSpeed;

    //    if(data.rid== 1)
    //        qDebug()<<"Vel:" <<ans.VX<<":"<<ans.VY;
    ans.RID=data.rid;
    return ans;
}

MotorSpeed Controller::calcMotorSpeed3(RobotSpeed rs)
{
    double motor[3][1],rotate[3][3],speed[3][1];

    speed[0][0] = rs.VX;
    speed[1][0] = rs.VY;
    speed[2][0] = rs.VW;

    rotate[0][0] = sin(M_PI / 3);//-sin(rangle - M_PI / 3);
    rotate[1][0] = sin(M_PI);//-sin(rangle + M_PI / 3);
    rotate[2][0] = sin(4 * M_PI / 3);//-sin(rangle + M_PI);
    rotate[0][1] = -cos(M_PI / 3);//cos(rangle - M_PI / 3);
    rotate[1][1] = -cos(M_PI);//cos(rangle + M_PI / 3);
    rotate[2][1] = -cos(4 * M_PI / 3);//cos(rangle + M_PI);
    rotate[0][2] = -ROBOTRADIUS;
    rotate[1][2] = -ROBOTRADIUS;
    rotate[2][2] = -ROBOTRADIUS;

    //motor = Matrix.Multiply(rotate, speed);
    motor[0][0] = rotate[0][0] * speed[0][0] + rotate[0][1] * speed[1][0] + rotate[0][2] * speed[2][0];
    motor[1][0] = rotate[1][0] * speed[0][0] + rotate[1][1] * speed[1][0] + rotate[1][2] * speed[2][0];
    motor[2][0] = rotate[2][0] * speed[0][0] + rotate[2][1] * speed[1][0] + rotate[2][2] * speed[2][0];


    double MaxMotorSpeed = MAXMOTORSRPM * M_PI * WHEELDIAMETER / 60000;

    MotorSpeed ms;




    ms.M1 = -(motor[0][0] * 127.0 / MaxMotorSpeed);
    ms.M2 = -(motor[1][0] * 127.0 / MaxMotorSpeed);
    ms.M3 = -(motor[2][0] * 127.0 / MaxMotorSpeed);

    double max = max3(fabs(ms.M1),fabs(ms.M2),fabs(ms.M3));

    if(rs.RID==5)
    {
        ms.M1 = (int)((ms.M1 * 127.0)/max);
        ms.M2 = (int)((ms.M2 * 127.0)/max);
        ms.M3 = (int)((ms.M3 * 127.0)/max);
    }
    else if(max > 127)
    {
        ms.M1 = (int)((ms.M1 * 127.0)/max);
        ms.M2 = (int)((ms.M2 * 127.0)/max);
        ms.M3 = (int)((ms.M3 * 127.0)/max);
    }


    //qDebug() << "m1:"<<motor[0][0] << ms.M1<<"m2:"<<motor[1][0]<< ms.M2<<"m3:"<<motor[2][0]<< ms.M3;
    return ms;
}

MotorSpeed Controller::calcMotorSpeed4(RobotSpeed rs)
{
    double motor[4][1],rotate[4][3],speed[3][1];

    speed[0][0] = rs.VX;
    speed[1][0] = rs.VY;
    speed[2][0] = rs.VW;
    //qDebug()<<"vw:"<<rs.VW*ROBOTRADIUS;

    rotate[0][0] = sin(M_PI / 3);//-sin(rangle - M_PI / 3);
    rotate[1][0] = sin(3 * M_PI / 4);//-sin(rangle + M_PI / 3);
    rotate[2][0] = sin(5 * M_PI / 4);//-sin(rangle + M_PI);
    rotate[3][0] = sin(5 * M_PI / 3);//-sin(rangle + M_PI);
    rotate[0][1] = -cos(M_PI / 3);//cos(rangle - M_PI / 3);
    rotate[1][1] = -cos(3 * M_PI / 4);//cos(rangle + M_PI / 3);
    rotate[2][1] = -cos(5 * M_PI / 4);//cos(rangle + M_PI);
    rotate[3][1] = -cos(5 * M_PI / 3);//cos(rangle + M_PI);
    rotate[0][2] = -ROBOTRADIUS;
    rotate[1][2] = -ROBOTRADIUS;
    rotate[2][2] = -ROBOTRADIUS;
    rotate[3][2] = -ROBOTRADIUS;

    //motor = Matrix.Multiply(rotate, speed);
    motor[0][0] = rotate[0][0] * speed[0][0] + rotate[0][1] * speed[1][0] + rotate[0][2] * speed[2][0];
    motor[1][0] = rotate[1][0] * speed[0][0] + rotate[1][1] * speed[1][0] + rotate[1][2] * speed[2][0];
    motor[2][0] = rotate[2][0] * speed[0][0] + rotate[2][1] * speed[1][0] + rotate[2][2] * speed[2][0];
    motor[3][0] = rotate[3][0] * speed[0][0] + rotate[3][1] * speed[1][0] + rotate[3][2] * speed[2][0];
    //qDebug()<<"m1:"<<motor[0][0]<<"mx1: "<<rotate[0][0] * speed[0][0] + rotate[0][1] * speed[1][0];
    //qDebug()<<"m2:"<<motor[1][0]<<"mx2: "<<rotate[1][0] * speed[0][0] + rotate[1][1] * speed[1][0];
    //qDebug()<<"m3:"<<motor[2][0]<<"mx3: "<<rotate[2][0] * speed[0][0] + rotate[2][1] * speed[1][0];
    //qDebug()<<"m4:"<<motor[3][0]<<"mx4: "<<rotate[3][0] * speed[0][0] + rotate[3][1] * speed[1][0];


    MotorSpeed ms;

    ms.M1 = -motor[0][0]*100;
    ms.M2 = -motor[1][0]*100;
    ms.M3 = -motor[2][0]*100;
    ms.M4 = -motor[3][0]*100;


    return ms;
}
