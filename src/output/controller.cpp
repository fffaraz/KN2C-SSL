#include "controller.h"
#include "constants.h"
#include <cmath>
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

ControllerResult Controller::calc(Position curpos, Position curvel, Position target, int rid, float fdest, float speed,WorldModel* _wm)
{

    wm=_wm;
    // filling controller data
    ControllerData ctrldata;
    ctrldata.curpos=curpos;
    ctrldata.curvel=curvel;
    ctrldata.target=target;
    //ctrldata.target.dir=0;//Vector2D(0,0);target;
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

#define  IntegralCash 100

RobotSpeed Controller::calcRobotSpeed(ControllerData& data)
{
    float MAXROBOTSPEED = MAXMOTORSRPM * M_PI * WHEELDIAMETER * cos(M_PI / 6) / 60;
    float MAXROTATIONSPEED = MAXMOTORSRPM * WHEELDIAMETER / (60 * ROBOTRADIUS * 2);
    float ROBOTSPEED;
    float RotationSpeed;

    static bool flg = false;
    static double saved_data[12][100][2];


    static Vector2D err1[12],err0[12];// = (data.target.loc - data.curpos.loc);
    static Vector2D u1[12];

    static double Kp[12];// = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
    static double Kd[12];// = {50,50,50,50,50,50,50,50,50,50,50,50};
    static double delT[12];// = {10,10,10,10,10,10,10,10,10,10,10,10};
    static double Ki[12];// = {0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01}; //Kp/Ti

    static Vector2D integral[12][IntegralCash];
    static int Integral_CNT[12];
    static Vector2D derived[12];

    static double werr1[12];// = (data.target.loc - data.curpos.loc);
    static double werr0[12];
    static double wu1[12];

    static double wKp[12];// = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
    static double wKd[12];// = {50,50,50,50,50,50,50,50,50,50,50,50};
    //static double wdelT[12];// = {10,10,10,10,10,10,10,10,10,10,10,10};
    static double wKi[12];// = {0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01}; //Kp/Ti
    static double wintegral[12][10];
    static double wderived[12];

    wm->slider[0];

    if(!flg)
    {
        for(int i=0;i<12;i++)
        {
            for(int j=0;j<100;j++)
                for(int k=0;k<2;k++)
                    saved_data[i][j][k] =0;
            if(GRSIM)
            {
                err1[i] = Vector2D(0,0);
                u1[i] = Vector2D(0,0);
                Kp[i] = 4;
                Kd[i] = 5;
                delT[i] = 10;
                Ki[i] = .0000001;//Kp[i]/Ti[i];
                for(int j=0;j<IntegralCash;j++)
                {
                    integral[i][j] = Vector2D(0,0);
                    wintegral[i][j] = 0;
                }
                Integral_CNT[i]=0;
                derived[i]=Vector2D(0,0);
                werr1[i] = 0;
                wu1[i] = 0;
                wKp[i] = 14;
                wKi[i] = .015;//Kp[i]/Ti[i];

                wderived[i] = 0;
            }
            else
            {
                err1[i] = Vector2D(0,0);
                u1[i] = Vector2D(0,0);
                Kp[i] = wm->slider[0]/2000.0;
                Kd[i] = wm->slider[1]/200.0;
                delT[i] = 10;
                Ki[i] = wm->slider[2]/200000.0;//Kp[i]/Ti[i];
                for(int j=0;j<IntegralCash;j++)
                {
                    integral[i][j] = Vector2D(0,0);
                    wintegral[i][j] = 0;
                }
                Integral_CNT[i]=0;
                werr1[i] = 0;
                werr0[i] = 0;
                wu1[i] = 0;
                wKp[i] = .000425;
                wKd[i] = .000425;
                wKi[i] = .000000000006;//Kp[i]/Ti[i];
                wderived[i] = 0;
            }
        }

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

    /******************************Linear Speed Controller************************************/

    err0[data.rid] = err1[data.rid];
    err1[data.rid] = (data.target.loc - data.curpos.loc)*.001;
    if(err1[data.rid].length()<.500)
    {
        Kp[data.rid] = .001900+wm->slider[0]/20000.0-wm->slider[1]/20000.0;2.1;.004000;.0020100;
        Kd[data.rid] = .06;wm->slider[1]/2000.0;400;0;.493000;0;
        Ki[data.rid] = .000001;wm->slider[2]/20000000.0;.0015;;.000001015;0;0;
    }
    else
    {
        Kp[data.rid] = .002;wm->slider[3]/20.0;.0022100;wm->slider[3]/20000.0;
        Kd[data.rid] = 0;.493000;wm->slider[1]/2000.0;
        Ki[data.rid] = 0;.0000015150;wm->slider[2]/20000000.0;
        integral[data.rid][0]=Vector2D(0,0);
    }

    if(err1[data.rid].length()<.150 && err1[data.rid].length()>.010)
    {
        integral[data.rid][0] = integral[data.rid][0] + (err1[data.rid]*delT[data.rid]);
    }
    else
        integral[data.rid][0] = Vector2D(0,0);
    derived[data.rid] = (err1[data.rid]-err0[data.rid])/delT[data.rid];

    u1[data.rid] = (err1[data.rid]*Kp[data.rid]) + (integral[data.rid][0]*Ki[data.rid]) + derived[data.rid]*Kd[data.rid];

    if(u1[data.rid].length()>MAXROBOTSPEED)
        u1[data.rid].setLength(MAXROBOTSPEED);

    //qDebug()<<MAXROBOTSPEED;
    //   if(err1[data.rid].length()>.050)
    //   {
    //   u1[data.rid].setLength(wm->slider[0]/200);
    //   }
    //   else
    //   {
    //       u1[data.rid].setLength(0);
    //   }
    Vector2D temp = u1[data.rid];
        temp.setLength((.00015+wm->slider[3]/20000.0));
    if(err1[data.rid].length()>.010)
        u1[data.rid] = u1[data.rid] + temp;

    Vector2D LinearSpeed = u1[data.rid];
    Vector2D RotLinearSpeed=LinearSpeed;
    RotLinearSpeed.x = LinearSpeed.x * cos(data.curpos.dir) + LinearSpeed.y * sin(data.curpos.dir);
    RotLinearSpeed.y = -LinearSpeed.x * sin(data.curpos.dir) + LinearSpeed.y * cos(data.curpos.dir);

    /******************************Rotation Speed Controller************************************/
    werr0[data.rid] = werr1[data.rid];
    werr1[data.rid] = data.target.dir - data.curpos.dir;
    if (werr1[data.rid] > M_PI) werr1[data.rid] -= 2 * M_PI;
    if (werr1[data.rid] < -M_PI) werr1[data.rid] += 2 * M_PI;
    //    if(data.rid == 0)
    //        qDebug()<<err1[data.rid].length()<<"   "<<integral[data.rid][0].length()<<"   "<<derived[data.rid].length();//<<;werr1[data.rid];
    if(err1[data.rid].length()<.500)
    {
        wKp[data.rid] = .0005;wm->slider[3]/20000.0;4;wm->slider[3]/20000.0;.001600;
        wKd[data.rid] =0; wm->slider[1]/2000.0;.009450;
        wKi[data.rid] = wm->slider[0]/20000000.0;0;wm->slider[2]/20000000.0;.000000150;
    }
    else
    {
        wKp[data.rid] = .00152;wm->slider[3]/20000.0;0;wm->slider[3]/20.0;0;wm->slider[3]/20000.0;;wm->slider[3]/20000.0;.001600;
        wKd[data.rid] =0; wm->slider[1]/2000.0;.009450;
        wKi[data.rid] = 0;wm->slider[2]/20000000.0;.000000150;
        wintegral[data.rid][0]=0;
    }
    if(fabs(werr1[data.rid])< .4)
        wintegral[data.rid][0] = wintegral[data.rid][0] + (werr1[data.rid]*delT[data.rid]);
    else wintegral[data.rid][0] = 0;
    wderived[data.rid] = (fabs(werr1[data.rid])-fabs(werr0[data.rid]))/delT[data.rid];

    wu1[data.rid] = (werr1[data.rid]*wKp[data.rid]) + (wintegral[data.rid][0]*wKi[data.rid]) + wderived[data.rid]*wKd[data.rid];



    //    wintegral[data.rid] = wintegral[data.rid] + (werr1[data.rid]*delT[data.rid]);
    //    wu1[data.rid] = (werr1[data.rid]*wKp[data.rid]) + (wintegral[data.rid]*wKi[data.rid]);
    //    if(fabs(wu1[data.rid]) > MAXROTATIONSPEED*2)
    //        wu1[data.rid] = sign(wu1[data.rid])*MAXROTATIONSPEED*2;
    if(fabs(werr1[data.rid])> 5*AngleDeg::DEG2RAD)
        wu1[data.rid] += .001*(float)(sign(wu1[data.rid]));
    RotationSpeed = wu1[data.rid];



    RobotSpeed ans;

    ans.VX = RotLinearSpeed.x*data.speed;
    ans.VY = RotLinearSpeed.y*data.speed;
    ans.VW = RotationSpeed;



    ans.RID=data.rid;
    return ans;
}

MotorSpeed Controller::calcMotorSpeed3(RobotSpeed rs)
{
    double motor[3][1],rotate[3][3],speed[3][1];

    speed[0][0] = rs.VX;
    speed[1][0] = rs.VY;
    speed[2][0] = rs.VW;

    rotate[0][0] = sin(M_PI / 3.0);//-sin(rangle - M_PI / 3);
    rotate[1][0] = sin(M_PI);//-sin(rangle + M_PI / 3);
    rotate[2][0] = sin(4.0 * M_PI / 3.0);//-sin(rangle + M_PI);
    rotate[0][1] = -cos(M_PI / 3.0);//cos(rangle - M_PI / 3);
    rotate[1][1] = -cos(M_PI);//cos(rangle + M_PI / 3);
    rotate[2][1] = cos(4.0 * M_PI / 3.0);//cos(rangle + M_PI);
    rotate[0][2] = -ROBOTRADIUS;
    rotate[1][2] = -ROBOTRADIUS;
    rotate[2][2] = -ROBOTRADIUS;

    //motor = Matrix.Multiply(rotate, speed);
    motor[0][0] = rotate[0][0] * speed[0][0] + rotate[0][1] * speed[1][0] + rotate[0][2] * speed[2][0];
    motor[1][0] = rotate[1][0] * speed[0][0] + rotate[1][1] * speed[1][0] + rotate[1][2] * speed[2][0];
    motor[2][0] = rotate[2][0] * speed[0][0] + rotate[2][1] * speed[1][0] + rotate[2][2] * speed[2][0];


    double MaxMotorSpeed = MAXMOTORSRPM * M_PI * WHEELDIAMETER / 60000;

    MotorSpeed ms;

    //    if(rs.RID == 6)
    //        qDebug()<<motor[0][0]<<"    " <<motor[1][0]<<"    " <<motor[2][0];


    ms.M1 = -(motor[0][0] * 127.0 / MaxMotorSpeed);
    ms.M2 = -(motor[1][0] * 127.0 / MaxMotorSpeed);
    ms.M3 = -(motor[2][0] * 127.0 / MaxMotorSpeed);

    double max = max3(fabs(ms.M1),fabs(ms.M2),fabs(ms.M3));
    //    if(rs.RID == 6)
    //        qDebug() << "m1:"<< ms.M1<<"m2:"<< ms.M2<<"m3:"<< ms.M3;
    if(rs.RID==8)
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

    //    if(rs.RID == 6)
    //   qDebug() << "m1:"<<motor[0][0] <<","<< ms.M1<<"m2:"<<motor[1][0]<<","<< ms.M2<<"m3:"<<motor[2][0]<<","<< ms.M3;
    //        qDebug() << "m1:"<< ms.M1<<"m2:"<< ms.M2<<"m3:"<< ms.M3;
    return ms;
}

MotorSpeed Controller::calcMotorSpeed4(RobotSpeed rs)
{
    double motor[4][1],rotate[4][3],speed[3][1];

    speed[0][0] = rs.VX * 1000.0;
    speed[1][0] = rs.VY * 1000.0;
    speed[2][0] = rs.VW * 1000.0;
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
