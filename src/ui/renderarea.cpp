#include "renderarea.h"

RenderArea::RenderArea(Soccer* sc) :
    QWidget()
{
    _sc = sc;
    brush_field = new QBrush(QPixmap(":/resources/images/Field.jpg"));
    brush_ball = new QBrush(QColor::fromRgb(255,200,0),Qt::SolidPattern);
    brush_yrobot = new QBrush(QColor::fromRgb(255,255,0),Qt::SolidPattern);
    brush_brobot = new QBrush(QColor::fromRgb(50,50,255),Qt::SolidPattern);
    _timer.start(20);
    connect(&_timer,SIGNAL(timeout()), this, SLOT(refresh()));
}

void RenderArea::refresh()
{
    update();
}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Settings
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Draw Field
    painter.setBrush(*brush_field);
    painter.drawRect(0,0,740,540);

    // FPS
    painter.drawText(20,20,"FPS : " + QString::number(_fps.FPS()));

    painter.translate(CENTER_X,CENTER_Y);

    // Draw Robots
    painter.setPen(QColor::fromRgb(0,0,0));

    painter.setBrush(*brush_yrobot);
    for(int i=0;i<12;i++)
        if(_sc->vr->oppRobot[i].isValid)
        {
            painter.drawChord(_sc->vr->oppRobot[i].pos.x/WORLD_SCALE-ROBOT_R,-_sc->vr->oppRobot[i].pos.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,ANGLE_TO_CHORD(_sc->vr->oppRobot[i].angle));
            painter.drawText(_sc->vr->oppRobot[i].pos.x/WORLD_SCALE-ROBOT_R,-_sc->vr->oppRobot[i].pos.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,Qt::AlignCenter,QString::number(_sc->vr->oppRobot[i].id));
        }

    painter.setBrush(*brush_brobot);
    for(int i=0;i<12;i++)
        if(_sc->vr->ourRobot[i].isValid)
        {
            painter.drawChord(_sc->vr->ourRobot[i].pos.x/WORLD_SCALE-ROBOT_R,-_sc->vr->ourRobot[i].pos.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,ANGLE_TO_CHORD(_sc->vr->ourRobot[i].angle));
            painter.drawText(_sc->vr->ourRobot[i].pos.x/WORLD_SCALE-ROBOT_R,-_sc->vr->ourRobot[i].pos.y/WORLD_SCALE-ROBOT_R,ROBOT_D,ROBOT_D,Qt::AlignCenter,QString::number(_sc->vr->ourRobot[i].id));
        }

    // Draw Ball
    if(_sc->vr->ball.isValid)
    {
        painter.setPen(QColor::fromRgb(200,100,0));
        painter.setBrush(*brush_ball);
        painter.drawEllipse(QPoint(_sc->vr->ball.pos.x/WORLD_SCALE,-_sc->vr->ball.pos.y/WORLD_SCALE),BALL_R,BALL_R);
    }
    // TEST

    //painter.drawChord(100-ROBOT_R,100-ROBOT_R,ROBOT_D,ROBOT_D,ANGLE_TO_CHORD(0));
    //painter.drawText(100-ROBOT_R,100-ROBOT_R,ROBOT_D,ROBOT_D,Qt::AlignCenter,"8");

    _fps.Pulse();
}
