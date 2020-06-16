#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>
#include <QLabel>
#include <QPushButton>


#include "bullet.h"
#include "floor.h"
#include "player.h"
#include "monster.h"
#include "blackhole.h"
#include "prop.h"

#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //QGraphicsPixmapItem *doodle;
    double v=7.8 ,g=0.095;

public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    //virtual void mousePressEvent(QMouseEvent *e);
    void jump();
    void stopultimate();
    void restart();
    void move_floor(int);

signals:
    void game_over();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QLabel *score_label , *gameover_label ,*finalscore_label , *instruction;
    QPushButton *restart_but;
    QTimer *timer , *startimer;
    player *doodle;
    monster *mon;
    blackhole *bh;
    bullet *bu;
    floor_base *flr[21];
    prop_base *gameprop;
    floor *groundfloor;
    int cnt=0 , score=0 , bhcnt=0 , prcnt=0;
    bool paused=false;
    bool gameover=false;
    bool rocketmode=false;
    bool ultimatemode = false;
    bool onthefloor(int);
    void genfloor(int , int );
    void genmonster();
    void genprop();
    void genblackhole();
    void pause();
    void dead();
    void initialize_scene();

};

#endif // MAINWINDOW_H














