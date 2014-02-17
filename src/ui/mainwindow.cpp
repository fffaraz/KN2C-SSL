#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Soccer *soccer, QWidget *parent) :
    QMainWindow(parent),
    _updatetimer(this),
    sc(soccer),
    ui(new Ui::MainWindow)
{
    _updatetimer.setObjectName("updatetimer");
    _updatetimer.start(100);
    ui->setupUi(this);
    ui->txtLog->append(SerialPort::ListPorts());
    _render = new RenderArea(soccer);
    ui->gridRender->addWidget(_render);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_updatetimer_timeout()
{
    ui->txtRefreeSpeed->setText(QString::number(sc->sslvision->FPS()));
    ui->txtVisionSpeed->setText(QString::number(sc->sslrefbox->FPS()));
    ui->txtRecordSpeed->setText(QString::number(sc->visionrecorder->FPS()));
    ui->txtTime->setText(QString::number((sc->wm->time)));
    ui->txtTimeBall->setText(QString::number(sc->vr->ball.time));

    QString refgs = QString("") + sc->wm->refgs.cmd +
            ":" +QString::number(sc->wm->refgs.cmd_counter) +
            ":" + QString::number(sc->wm->refgs.goals_blue) +
            ":" + QString::number(sc->wm->refgs.goals_yellow) +
            ":" + QString::number(sc->wm->refgs.time_remaining);
    ui->txtrefgs->setText(refgs);


    sc->wm->referee_our_ui=ui->Enable->isChecked();
    sc->wm->updatePlayMode();

    ball_moved=(last_ball_pos - sc->wm->ball.pos.loc).length() > 20.0;

    if(!sc->wm->referee_our_ui)
        {
        ui->txtcmgs_1->setText(QString("gameOn : ") + (sc->wm->cmgs.gameOn()?"1":"0"));
        ui->txtcmgs_2->setText(QString("allowedNearBall : ") + (sc->wm->cmgs.allowedNearBall()?"1":"0"));
        ui->txtcmgs_3->setText(QString("canKickBall : ") + (sc->wm->cmgs.canKickBall()?"1":"0"));

        ui->txtcmgs_4->setText(QString("restart : ") + (sc->wm->cmgs.restart()?"1":"0"));
        ui->txtcmgs_5->setText(QString("ourRestart : ") + (sc->wm->cmgs.ourRestart()?"1":"0"));
        ui->txtcmgs_6->setText(QString("theirRestart : ") + (sc->wm->cmgs.theirRestart()?"1":"0"));

        ui->txtcmgs_7->setText(QString("kickoff : ") + (sc->wm->cmgs.kickoff()?"1":"0"));
        ui->txtcmgs_8->setText(QString("ourKickoff : ") + (sc->wm->cmgs.ourKickoff()?"1":"0"));
        ui->txtcmgs_9->setText(QString("theirKickoff : ") + (sc->wm->cmgs.theirKickoff()?"1":"0"));

        ui->txtcmgs_10->setText(QString("penaltyKick : ") + (sc->wm->cmgs.penaltyKick()?"1":"0"));
        ui->txtcmgs_11->setText(QString("ourPenaltyKick : ") + (sc->wm->cmgs.ourPenaltyKick()?"1":"0"));
        ui->txtcmgs_12->setText(QString("theirPenaltyKick : ") + (sc->wm->cmgs.theirPenaltyKick()?"1":"0"));

        ui->txtcmgs_13->setText(QString("directKick : ") + (sc->wm->cmgs.directKick()?"1":"0"));
        ui->txtcmgs_14->setText(QString("ourDirectKick : ") + (sc->wm->cmgs.ourDirectKick()?"1":"0"));
        ui->txtcmgs_15->setText(QString("theirDirectKick : ") + (sc->wm->cmgs.theirDirectKick()?"1":"0"));

        ui->txtcmgs_16->setText(QString("indirectKick : ") + (sc->wm->cmgs.indirectKick()?"1":"0"));
        ui->txtcmgs_17->setText(QString("ourIndirectKick : ") + (sc->wm->cmgs.ourIndirectKick()?"1":"0"));
        ui->txtcmgs_18->setText(QString("theirIndirectKick : ") + (sc->wm->cmgs.theirIndirectKick()?"1":"0"));

        ui->txtcmgs_19->setText(QString("freeKick : ") + (sc->wm->cmgs.freeKick()?"1":"0"));
        ui->txtcmgs_20->setText(QString("ourFreeKick : ") + (sc->wm->cmgs.ourFreeKick()?"1":"0"));
        ui->txtcmgs_21->setText(QString("theiFreeKick : ") + (sc->wm->cmgs.theirFreeKick()?"1":"0"));

        ui->txtcmgs_22->setText(QString("canMove : ") + (sc->wm->cmgs.canMove()?"1":"0"));

        last_ball_pos=sc->wm->ball.pos.loc;
        }
        else
        {

       // sc->wm->cmgs.transition(sc->wm->gs,ball_moved);
        ui->txtcmgs_1->setText(QString("gameOn : ") + (sc->wm->cmgs.gameOn()?"1":"0"));
        ui->txtcmgs_2->setText(QString("allowedNearBall : ") + (sc->wm->cmgs.allowedNearBall()?"1":"0"));
        ui->txtcmgs_3->setText(QString("canKickBall : ") + (sc->wm->cmgs.canKickBall()?"1":"0"));

        ui->txtcmgs_4->setText(QString("restart : ") + (sc->wm->cmgs.restart()?"1":"0"));
        ui->txtcmgs_5->setText(QString("ourRestart : ") + (sc->wm->cmgs.ourRestart()?"1":"0"));
        ui->txtcmgs_6->setText(QString("theirRestart : ") + (sc->wm->cmgs.theirRestart()?"1":"0"));

        ui->txtcmgs_7->setText(QString("kickoff : ") + (sc->wm->cmgs.kickoff()?"1":"0"));
        ui->txtcmgs_8->setText(QString("ourKickoff : ") + (sc->wm->cmgs.ourKickoff()?"1":"0"));
        ui->txtcmgs_9->setText(QString("theirKickoff : ") + (sc->wm->cmgs.theirKickoff()?"1":"0"));

        ui->txtcmgs_10->setText(QString("penaltyKick : ") + (sc->wm->cmgs.penaltyKick()?"1":"0"));
        ui->txtcmgs_11->setText(QString("ourPenaltyKick : ") + (sc->wm->cmgs.ourPenaltyKick()?"1":"0"));
        ui->txtcmgs_12->setText(QString("theirPenaltyKick : ") + (sc->wm->cmgs.theirPenaltyKick()?"1":"0"));

        ui->txtcmgs_13->setText(QString("directKick : ") + (sc->wm->cmgs.directKick()?"1":"0"));
        ui->txtcmgs_14->setText(QString("ourDirectKick : ") + (sc->wm->cmgs.ourDirectKick()?"1":"0"));
        ui->txtcmgs_15->setText(QString("theirDirectKick : ") + (sc->wm->cmgs.theirDirectKick()?"1":"0"));

        ui->txtcmgs_16->setText(QString("indirectKick : ") + (sc->wm->cmgs.indirectKick()?"1":"0"));
        ui->txtcmgs_17->setText(QString("ourIndirectKick : ") + (sc->wm->cmgs.ourIndirectKick()?"1":"0"));
        ui->txtcmgs_18->setText(QString("theirIndirectKick : ") + (sc->wm->cmgs.theirIndirectKick()?"1":"0"));

        ui->txtcmgs_19->setText(QString("freeKick : ") + (sc->wm->cmgs.freeKick()?"1":"0"));
        ui->txtcmgs_20->setText(QString("ourFreeKick : ") + (sc->wm->cmgs.ourFreeKick()?"1":"0"));
        ui->txtcmgs_21->setText(QString("theiFreeKick : ") + (sc->wm->cmgs.theirFreeKick()?"1":"0"));

        ui->txtcmgs_22->setText(QString("canMove : ") + (sc->wm->cmgs.canMove()?"1":"0"));

        last_ball_pos=sc->wm->ball.pos.loc;
        }




    QString ball = QString::number(sc->wm->ball.pos.loc.x,'f',2) + " : " + QString::number(sc->wm->ball.pos.loc.y,'f',2);
    QString s = QString::number(sc->wm->ball.vel.loc.x,'f',2) + " : " + QString::number(sc->wm->ball.vel.loc.y,'f',2);
    ball+= " ( " + s + " ) ";
    ui->txtBall->setText(ball);
    ui->txtWM->setText("Ball: " + ball + " : " + QString::number(sc->wm->ball.isValid?1:0));
    // WM
    for(int i=0; i<PLAYERS_MAX_NUM; ++i)
    {
        QString r = QString::number(sc->wm->ourRobot[i].pos.loc.x,'f',2) + " : " + QString::number(sc->wm->ourRobot[i].pos.loc.y,'f',2);
        QString s = QString::number(sc->wm->ourRobot[i].vel.loc.x,'f',2) + " : " + QString::number(sc->wm->ourRobot[i].vel.loc.y,'f',2)+ " : " + QString::number(sc->wm->ourRobot[i].vel.dir,'f',2);
        ui->txtWM->append("our[" + QString::number(i) + "] (" + r + ")(" + s + ") : " +QString::number(sc->wm->ourRobot[i].isValid));
    }
    for(int i=0; i<PLAYERS_MAX_NUM; ++i)
    {
        QString r = QString::number(sc->wm->oppRobot[i].pos.loc.x,'f',2) + " : " + QString::number(sc->wm->oppRobot[i].pos.loc.y,'f',2);
        QString s = QString::number(sc->wm->oppRobot[i].vel.loc.x,'f',2) + " : " + QString::number(sc->wm->oppRobot[i].vel.loc.y,'f',2)+ " : " + QString::number(sc->wm->oppRobot[i].vel.dir,'f',2);
        ui->txtWM->append("opp[" + QString::number(i) + "] (" + r + ")(" + s + ") : " +QString::number(sc->wm->oppRobot[i].isValid));
    }

    sc->wm->slider[0]=ui->horizontalSlider->value();
    sc->wm->slider[1]=ui->horizontalSlider_2->value();
    sc->wm->slider[2]=ui->horizontalSlider_3->value();
    sc->wm->slider[3]=ui->horizontalSlider_4->value();
    ui->label_1->setText(QString::number(sc->wm->slider[0]/20000.0,'f',6));
    ui->label_2->setText(QString::number(sc->wm->slider[1]/20000.0,'f',6));
    ui->label_3->setText(QString::number(sc->wm->slider[2]/20000000.0,'f',9));
    ui->label_4->setText(QString::number(sc->wm->slider[3]/20000.0,'f',6));

    sc->wm->referee_our_ui =ui->Enable->isChecked();
    if(sc->wm->referee_our_ui)
        sc->wm->updatePlayMode();

}




void MainWindow::on_Halt_KP_Point_clicked()
{
    if(sc->wm->referee_our_ui)
        sc->wm->set_ui_state(COMM_HALT,ball_moved);
    sc->wm->updatePlayMode();
}

void MainWindow::on_Stop_Game_KP_0_clicked()
{
    if(sc->wm->referee_our_ui)
       sc->wm->set_ui_state(COMM_STOP,ball_moved);
    sc->wm->updatePlayMode();
}

void MainWindow::on_ForceStart_KP_5_clicked()
{
    if(sc->wm->referee_our_ui)
        sc->wm->set_ui_state(COMM_START,ball_moved);
    sc->wm->updatePlayMode();
}

void MainWindow::on_NormalStart_KP_Enter_clicked()
{
    if(sc->wm->referee_our_ui)
        sc->wm->set_ui_state(COMM_READY,ball_moved);
    sc->wm->updatePlayMode();
}

void MainWindow::on_Kickoff_Yellow_clicked()
{

    if(sc->wm->referee_our_ui)
        sc->wm->set_ui_state(COMM_KICKOFF_YELLOW,ball_moved);
    sc->wm->updatePlayMode();
}

void MainWindow::on_Penalty_Yellow_clicked()
{

    if(sc->wm->referee_our_ui)
        sc->wm->set_ui_state(COMM_PENALTY_YELLOW,ball_moved);
    sc->wm->updatePlayMode();
}

void MainWindow::on_Freekick_Yellow_clicked()
{

    if(sc->wm->referee_our_ui)
        sc->wm->set_ui_state(COMM_DIRECT_YELLOW,ball_moved);
    sc->wm->updatePlayMode();
}

void MainWindow::on_Indirect_Yellow_clicked()
{

    if(sc->wm->referee_our_ui)
        sc->wm->set_ui_state(COMM_INDIRECT_YELLOW,ball_moved);
    sc->wm->updatePlayMode();
}

void MainWindow::on_Kickoff_Blue_clicked()
{
    if(sc->wm->referee_our_ui)
        sc->wm->set_ui_state(COMM_KICKOFF_BLUE,ball_moved);
    sc->wm->updatePlayMode();
}

void MainWindow::on_Penalty_Blue_clicked()
{
    if(sc->wm->referee_our_ui)
        sc->wm->set_ui_state(COMM_PENALTY_BLUE,ball_moved);
    sc->wm->updatePlayMode();
}

void MainWindow::on_FreeKick_Blue_clicked()
{
    if(sc->wm->referee_our_ui)
        sc->wm->set_ui_state(COMM_DIRECT_BLUE,ball_moved);
    sc->wm->updatePlayMode();
}

void MainWindow::on_Indirect_Blue_clicked()
{
    if(sc->wm->referee_our_ui)
        sc->wm->set_ui_state(COMM_INDIRECT_BLUE,ball_moved);
    sc->wm->updatePlayMode();
}
