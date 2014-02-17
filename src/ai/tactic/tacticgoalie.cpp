#include "tacticgoalie.h"

TacticGoalie::TacticGoalie(WorldModel *wm, Knowledge *kn, QObject *parent) :
    Tactic(wm, kn, "TacticGoalie", parent)
{
    _index = 0;
    _passDestination = -1;
    _tracePass = false;
    _sgp = new SkillGotoPosition(_wm, this);
    _skb = new SkillKickBall(_wm, this);
    _bp = new BehaviorPenalty(wm,kn,this);
}

bool TacticGoalie::doPlayOn(RobotCommand &rc)
{
    if (_kn->isInPenaltyArea(_wm->ball.pos.loc))
        return doKick(rc);
    else
        return doMove(rc);
}
bool TacticGoalie::doStop(RobotCommand &rc)
{
    return doMove(rc);
}

bool TacticGoalie::doOurDirectFreeKick(RobotCommand &rc)
{
    return doMove(rc);
}

bool TacticGoalie::doOurIndirectFreeKick(RobotCommand &rc)
{
    return doMove(rc);
}

bool TacticGoalie::doOurKickoff(RobotCommand &rc)
{
    return doMove(rc);
}

bool TacticGoalie::doOurPenalty(RobotCommand &rc)
{
    return doMove(rc);
}

bool TacticGoalie::doTheirDirectFreeKick(RobotCommand &rc)
{
    return doMove(rc);

    //    Line2D lineGoal(Vector2D(-FIELD_MAX_X,-FIELD_MAX_Y),Vector2D(-FIELD_MAX_X,FIELD_MAX_Y));
    //    Vector2D gdir, gloc;
    //    gdir=Vector2D();
    //    gloc=Vector2D();

    //    int kickerID=_kn->findOpponentKicker();



    //    if(kickerID==-1)
    //    {
    //        gdir=Vector2D(1,0);
    //        gloc=Vector2D(-3025,0);
    //    }
    //    else
    //    {
    //        Vector2D ins;
    //        Line2D l1(_wm->oppRobot[kickerID].pos.loc,AngleDeg(_wm->oppRobot[kickerID].pos.dir*AngleDeg::RAD2DEG));

    //        ins = l1.intersection(lineGoal);

    //        if(ins.y>265)
    //        {
    //            ins.y=265;
    //        }
    //        else if(ins.y<-265)
    //        {
    //            ins.y=-265;
    //        }
    //        ins.x=-3025;

    //        gdir=Vector2D(1,0);

    //        gloc=ins;
    //    }

    //    if(gloc.x<-3010)
    //        gloc.x=-3010;

    //    Position p;
    //    p.loc=gloc;
    //    p.dir=gdir.dir().radian();
    //    _sgp->setRID(_rid);
    //    _sgp->setPosition(p);

    //    return _sgp->execute(rc);
}

bool TacticGoalie::doTheirIndirectFreeKick(RobotCommand &rc)
{
    return doMove(rc);
}

bool TacticGoalie::doTheirKickoff(RobotCommand &rc)
{
    return doMove(rc);
}

bool TacticGoalie::doTheirPenalty(RobotCommand &rc)
{return doMove(rc);/*
    Line2D lineGoal(Vector2D(-3025,-2025),Vector2D(-3025,2025));
        Vector2D gdir, gloc;
        gdir=Vector2D();
        gloc=Vector2D();

        int kickerID=_kn->findOpponentKicker();


        if(kickerID==-1)
        {
            gdir=_wm->ball.pos.dir;
            gloc=Vector2D(-3025,0);
        }
        else
        {
            Vector2D ins;
            Line2D l1(_wm->oppRobot[kickerID].pos.loc,AngleDeg(_wm->oppRobot[kickerID].pos.dir*AngleDeg::RAD2DEG));

            ins = l1.intersection(lineGoal);

            if(ins.y>265)
            {
                ins.y=265;
            }
            else if(ins.y<-265)
            {
                ins.y=-265;
            }
            ins.x=-3025;

            gdir=Vector2D(1,0);

            gloc=ins;
        }

        if(gloc.x<-3010)
            gloc.x=-3010;

        Position p;
        p.loc=gloc;
        p.dir=gdir.dir.radian();
        _sgp->setRID(_rid);
        _sgp->setPosition(p);

        return _sgp->execute(rc);*/

}

bool TacticGoalie::doKick(RobotCommand &rc)
{
    Position p;
    _skb->setRID(_rid);
    _skb->setSpeedX(SHOOT_KICK_SPEED);
    if (_wm->ourRobot[_rid].pos.dir<0)
        p.dir = 0;
    p.dir = _wm->ourRobot[_rid].pos.dir;
    _skb->setKickPosition(p);
    return _skb->execute(rc);
}

bool TacticGoalie::doMove(RobotCommand &rc)
{
    Position p;
    Vector2D sol;
    Vector2D ourGoal1(-FIELD_MAX_X , GOAL_HALF_LENGTH);
    Vector2D ourGoal2(-FIELD_MAX_X , -GOAL_HALF_LENGTH);
    Vector2D thirdPoint(-FIELD_MAX_X + PENALTY_AREA_RADIUS/4 , 0);
    Line2D line1(thirdPoint,ourGoal1);
    Line2D line2(thirdPoint,ourGoal2);
    Line2D prependicularLine1 = line1.perpendicular(Vector2D((thirdPoint.x+ourGoal1.x)/2,(thirdPoint.y+ourGoal1.y)/2));
    Line2D prependicularLine2 = line2.perpendicular(Vector2D((thirdPoint.x+ourGoal2.x)/2,(thirdPoint.y+ourGoal2.y)/2));
    Vector2D center = prependicularLine1.intersection(prependicularLine2);
    double radius = center.dist(thirdPoint);
    Circle2D goalieCircle(center,radius);
    int opponentKicker = _kn->findOpponentKicker();
    Segment2D *ballLine;
    if (_wm->ball.pos.loc.absY() > GOAL_HALF_LENGTH+ROBOT_RADIUS*6.5)
    {
        ballLine = new Segment2D(_wm->ball.pos.loc,Vector2D(-FIELD_MAX_X,(GOAL_HALF_LENGTH-ROBOT_RADIUS)*_wm->ball.pos.loc.signY()));
    }
    else
        ballLine = new Segment2D(_wm->ball.pos.loc , Vector2D(-FIELD_MAX_X,0));
//    if (_tracePass)
//    {
//        qDebug()<<"trace!";
//        if (_wm->oppRobot[_passDestination].pos.loc.dist(_wm->ball.pos.loc) > _lastDist + 100)
//        {
//            qDebug()<<"normal!";
//            _tracePass = false ;
//            return true;
//        }
//        else
//        {
//            Vector2D sol1,sol2;
//            Line2D targetRobotLine(_wm->oppRobot[_passDestination].pos.loc , _wm->oppRobot[_passDestination].pos.dir*AngleDeg::RAD2DEG);
//            qDebug()<<"continue! "<<goalieCircle.intersection(targetRobotLine,&sol1,&sol2);

//            if (sol1.x < -FIELD_MAX_X)
//                sol =(sol2.isValid())? sol2:Vector2D(-FIELD_MAX_X+50,0);
//            else
//                sol = (sol1.isValid())?sol1:Vector2D(-FIELD_MAX_X+50,0);

//        }
//    }
//    else
//    {
        if (opponentKicker==-1)//================ball
        {
            Vector2D sol1=Vector2D::INVALIDATED;
            Vector2D sol2=Vector2D::INVALIDATED;
            goalieCircle.intersection(*ballLine,&sol1,&sol2);
            if (sol1.x < -FIELD_MAX_X)
                sol =(sol2.isValid())? sol2:Vector2D(-FIELD_MAX_X+50,0);
            else
                sol = (sol1.isValid())?sol1:Vector2D(-FIELD_MAX_X+50,0);
        }//=========================================
        else
        {
            Vector2D sol1=Vector2D::INVALIDATED;
            Vector2D sol2=Vector2D::INVALIDATED;
            Line2D robotLine(_wm->oppRobot[opponentKicker].pos.loc , _wm->oppRobot[opponentKicker].pos.dir*AngleDeg::RAD2DEG);
            if (goalieCircle.intersection(robotLine,&sol1,&sol2)!=0)
            {//=====================opponent kicker
                if (sol1.x < -FIELD_MAX_X)
                    sol = sol2;
                else
                    sol = sol1;
            }//====================================
            else
            {//================================pass
                _tracePass = true;
                int index = -1;
                double minDist = std::numeric_limits <double>::max();
                for (int i = 0 ; i < PLAYERS_MAX_NUM ; i++)
                {
                    if (!_wm->oppRobot[i].isValid || i==opponentKicker)
                        continue;
                    Vector2D targetRobot = _wm->oppRobot[i].pos.loc;
                    if ((robotLine.getA()*-FIELD_MAX_X + robotLine.getC())*(robotLine.getA()*targetRobot.x+robotLine.getB()*targetRobot.y+robotLine.getC())>0)
                        continue;
                    if(robotLine.dist(targetRobot) < minDist)
                    {
                        minDist = robotLine.dist(targetRobot);
                        index = i;
                    }
                }
                if (index!=-1)
                {
                    _passDestination = index;
                    _lastDist = _wm->oppRobot[index].pos.loc.dist(_wm->ball.pos.loc);
                    Line2D targetRobotLine(_wm->oppRobot[index].pos.loc , _wm->oppRobot[index].pos.dir*AngleDeg::RAD2DEG);
                    if (goalieCircle.intersection(targetRobotLine,&sol1,&sol2)!=0)
                    {
                        if (sol1.x < -FIELD_MAX_X)
                            sol =(sol2.isValid())? sol2:Vector2D(-FIELD_MAX_X+50,0);
                        else
                            sol = (sol1.isValid())?sol1:Vector2D(-FIELD_MAX_X+50,0);
                    }
                    else
                    {
                        goalieCircle.intersection(*ballLine,&sol1,&sol2);
                        if (sol1.x < -FIELD_MAX_X)
                            sol =(sol2.isValid())? sol2:Vector2D(-FIELD_MAX_X+50,0);
                        else
                            sol = (sol1.isValid())?sol1:Vector2D(-FIELD_MAX_X+50,0);
                    }
                }
                else
                {
                    goalieCircle.intersection(*ballLine,&sol1,&sol2);
                    if (sol1.x < -FIELD_MAX_X)
                        sol =(sol2.isValid())? sol2:Vector2D(-FIELD_MAX_X+50,0);
                    else
                        sol = (sol1.isValid())?sol1:Vector2D(-FIELD_MAX_X+50,0);
                }
            }
        }
//    }
    Circle2D robotGoalie(sol,ROBOT_RADIUS+10);
    if (robotGoalie.contains(ourGoal1) || sol.dist(ourGoal1) < 2*ROBOT_RADIUS+BALL_RADIUS)
        sol = Vector2D(-FIELD_MAX_X+50 , GOAL_HALF_LENGTH-(ROBOT_RADIUS+BALL_RADIUS+10));
    else if(robotGoalie.contains(ourGoal2) ||sol.dist(ourGoal2) < 2*ROBOT_RADIUS)
        sol = Vector2D(-FIELD_MAX_X+50 , -GOAL_HALF_LENGTH+(ROBOT_RADIUS+BALL_RADIUS+10));
    p.loc = sol;
    p.dir = (sol-_wm->ball.pos.loc).dir().radian()+M_PI;
    _sgp->setPosition(p, 1.5);
    _sgp->setRID(RID());
    return _sgp->execute(rc);
}
