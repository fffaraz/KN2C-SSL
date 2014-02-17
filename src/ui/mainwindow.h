#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "soccer.h"
#include "renderarea.h"
#include "base.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Soccer* soccer, QWidget *parent = 0);
    ~MainWindow();

private:
    QTimer _updatetimer;
    RenderArea *_render;
    Soccer* sc;
    Vector2D last_ball_pos;
    bool ball_moved;
private slots:
    void on_updatetimer_timeout();

    void on_Halt_KP_Point_clicked();
    void on_Stop_Game_KP_0_clicked();
    void on_ForceStart_KP_5_clicked();
    void on_NormalStart_KP_Enter_clicked();
    void on_Kickoff_Yellow_clicked();
    void on_Penalty_Yellow_clicked();
    void on_Freekick_Yellow_clicked();
    void on_Indirect_Yellow_clicked();
    void on_Kickoff_Blue_clicked();
    void on_Penalty_Blue_clicked();
    void on_FreeKick_Blue_clicked();
    void on_Indirect_Blue_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
