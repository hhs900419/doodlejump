#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QList>
#include <QMediaPlayer>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(20, 20, 800, 800)),
    timer(new QTimer),
    startimer(new QTimer)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    //srand(time(NULL));
    flr[0] = new floor(20 , 790);
    doodle = new player;
    mon = new monster;
    bh = new blackhole;
    gameprop = new rocket;

    QMediaPlayer *bgm = new QMediaPlayer(this);
    bgm->setMedia(QUrl("qrc:/images/bgm"));
    bgm->play();
    flr[0]->setPixmap(QPixmap(":/images/normal_floor").scaled(800,30));
    flr[0]->setPos(flr[0]->x(),flr[0]->y());
    doodle->setPos(420-doodle->pixmap().width(), 820-doodle->pixmap().height());
    scene->addItem(doodle);

    score_label = new QLabel(this);
    score_label -> setText("SCORE: "+QString::number(score));
    score_label->setGeometry(830, 50 , 300 , 80);
    score_label->setFont(QFont("Ubuntu", 14));
    instruction = new QLabel(this);
    instruction->setText("press P to pause");
    instruction->setFont(QFont("Ubuntu", 14));
    instruction->setGeometry(830, 150 , 200 , 80);
    gameover_label = new QLabel(this);
    gameover_label -> setText("       GAME OVER");
    gameover_label -> setGeometry(220 , 220 , 300 , 100);
    gameover_label -> setFont(QFont("Ubuntu", 20));
    gameover_label -> hide();
    restart_but = new QPushButton(this);
    restart_but -> setText("PLAY AGAIN!");
    restart_but -> setFont(QFont("Ubuntu", 20));
    restart_but->hide();

    timer->start(10);


    for(int i=1;i<21;i++){
        flr[i] = new floor(rand()%650+20 , -800+(rand()%160)+160*(i%10));
        flr[i]->setPixmap(QPixmap(":/images/normal_floor").scaled(150,30));
        flr[i]->setPos(flr[i]->x(),flr[i]->y());
    }
    for(int i=0;i<21;++i){
        scene->addItem(static_cast<QGraphicsPixmapItem*>(flr[i]));
    }



    connect(timer, SIGNAL(timeout()), this, SLOT(jump()));
    connect(startimer, SIGNAL(timeout()), this, SLOT(stopultimate()));
    connect(restart_but, SIGNAL(clicked()), this, SLOT(restart()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize_scene()
{
    flr[0] = new floor(20 , 790);
    flr[0]->setPixmap(QPixmap(":/images/normal_floor").scaled(800,30));
    flr[0]->setPos(flr[0]->x(),flr[0]->y());
    for(int i=1;i<21;i++){
        flr[i] = new floor(rand()%650+20 , -800+(rand()%160)+160*(i%10));
        flr[i]->setPixmap(QPixmap(":/images/normal_floor").scaled(150,30));
        flr[i]->setPos(flr[i]->x(),flr[i]->y());
    }
    for(int i=0;i<21;++i){
        scene->addItem(static_cast<QGraphicsPixmapItem*>(flr[i]));
    }
    doodle->setPos(420-doodle->pixmap().width(), 820-doodle->pixmap().height());
    doodle->show();
    v=7.8;
}

bool MainWindow::onthefloor(int i)
{
    double plrbot , plrlftedge , plrrgtedge , floorledge , floorredge , floortop , floorbot;
    plrbot = doodle->y()+doodle->pixmap().height();
    plrlftedge = doodle->x();
    plrrgtedge = doodle->x()+doodle->pixmap().width()-35;



    floorbot = flr[i]->y()+flr[i]->pixmap().height();
    floortop = flr[i]->y();
    floorledge = flr[i]->x();
    floorredge = flr[i]->x() + flr[i]->pixmap().width();

    if(plrbot>floortop && plrbot<floorbot && plrlftedge>=floorledge && plrlftedge<=floorredge){

       return true;
    }
    else if(plrbot>floortop && plrbot<floorbot && plrrgtedge>=floorledge && plrrgtedge<=floorredge){

       return true;
    }
    else {
       return false;
    }


}
void MainWindow::jump()
{
    int hieght ;
    score = flr[0]->y()-800+10;

    if(rocketmode && !ultimatemode){
        doodle->setPixmap(QPixmap(":/images/flying_doodle").scaled(120,120));
    }
    if(ultimatemode){
        doodle->setPixmap(QPixmap(":/images/ultimate_doodle").scaled(120,120));
    }
    if(!rocketmode && !ultimatemode) {
        doodle->setPixmap(QPixmap(":/images/doodle").scaled(120,120));
    }

    score_label -> setText("SCORE: "+QString::number(score));
    doodle->setPos(doodle->x() , doodle->y()-v);
    v = v-g;
    if(doodle->y()+doodle->pixmap().height()>=850){
        gameover = true;
        dead();
    }

    for(int i=0;i<21;i++){

        hieght = flr[i]->y();
        if(v<0 && onthefloor(i) && !gameover){
            v=7.8;
            if(flr[i]->stepped()==1)
                genfloor(i , hieght);
            else if(flr[i]->stepped()==2)
                v=15;
        }
    }

    if(doodle->collide_with_monster() && v<20 && !rocketmode && !ultimatemode){
        gameover=true;
        v=-10;
    }
    if(doodle->collide_with_blackhole() && v<20 && !rocketmode && !ultimatemode){
        gameover=true;
        v=-10;
    }
    if(doodle->collide_with_prop())
    {
        if(gameprop->collided()==1){
            rocketmode=true;
            v=30;
        }
        else if(gameprop->collided()==2){
            ultimatemode=true;
            gameprop->setPos(-500 , gameprop->y());
            scene->removeItem(gameprop);
            startimer->start(10000);
        }
    }
    if(v<=7)
    {
        rocketmode=false;
    }
    if(v>0 && doodle->y() <= 400){

        doodle->setPos(doodle->x() , 400);
        for(int i=0;i<21;i++){
            flr[i]->setPos(flr[i]->x(),flr[i]->y() + v);
        }
        mon->setPos(mon->x() , mon->y() + v);
        bh->setPos(bh->x(), bh->y() + v);
        gameprop->setPos(gameprop->x(), gameprop->y() + v);

    }
    for(int i=1;i<20;i++){

        if(flr[i]->y()>=1100){

            hieght=flr[i]->y();
            if(!rocketmode){
                cnt++;
                bhcnt++;
                if(!ultimatemode){
                    prcnt++;
                }
            }
            delete flr[i];
            genfloor(i , hieght);
        }
    }
    if(cnt>=50){
        cnt=0;
        genmonster();
    }
    if(bhcnt>=70){
        bhcnt=0;
        genblackhole();
    }
    if(prcnt>=30){
        prcnt=0;
        genprop();
    }





}

void MainWindow::move_floor(int i)
{
    flr[i]->setPos(flr[i]->x()-3,flr[i]->y());
    if(flr[i]->x() <= 20){
        flr[i]->setPos(flr[i]->x()+3, flr[i]->y());
    }
    if(flr[i]->x()+flr[i]->pixmap().width()>=820){
        flr[i]->setPos(flr[i]->x()-3, flr[i]->y());
    }
}
void MainWindow:: genfloor(int i , int y)
{
    if(v<15){
        if(rand()%20<3){
            flr[i] = new disappearing_floor(rand()%650+20 , y-1600+rand()%160);
        }
        else if (rand()%14<1) {
            flr[i] = new bouncy_floor(rand()%650+20 ,  y-1600+rand()%160);
        }
        else if (rand()%10<3) {
            flr[i] = new moving_floor(rand()%650+20 ,  y-1600+rand()%160);
            flr[i]->connect(timer, SIGNAL(timeout()),flr[i], SLOT(moving()));
        }
        else {
            flr[i] = new floor(rand()%650+20 ,  y-1600+rand()%160);
        }
    }
    else {
        if(rand()%20<3){
            flr[i] = new disappearing_floor(rand()%650+20 , y-1600+rand()%100);
        }
        else if (rand()%13<1) {
            flr[i] = new bouncy_floor(rand()%650+20 ,  y-1600+rand()%10);
        }
        else if (rand()%10<3) {
            flr[i] = new moving_floor(rand()%650+20 ,  y-1600+rand()%140);
            flr[i]->connect(timer, SIGNAL(timeout()),flr[i], SLOT(moving()));
        }
        else {
            flr[i] = new floor(rand()%650+20 ,  y-1600+rand()%140);
        }
    }
    flr[i]->setPos(flr[i]->x(),flr[i]->y());
    scene->addItem(static_cast<QGraphicsPixmapItem*>(flr[i]));
}

void MainWindow:: genmonster()
{
    mon = new monster(rand()%650+20 , -500-rand()%300);
    mon->setPos(mon->x(),mon->y());
    scene->addItem(static_cast<QGraphicsPixmapItem*>(mon));
}
void MainWindow:: genblackhole()
{
    bh = new blackhole(rand()%650+20 , -500-rand()%300);
    bh->setPos(bh->x(),bh->y());
    scene->addItem(static_cast<QGraphicsPixmapItem*>(bh));
}
void MainWindow:: genprop()
{
    if (rand()%2 < 1){
        gameprop = new rocket(rand()%650+20 , -500-rand()%300);
    }
    else {
       gameprop = new ultimatestar(rand()%650+20 , -500-rand()%300);
    }
    gameprop->setPos(gameprop->x(),gameprop->y());
    scene->addItem(static_cast<QGraphicsPixmapItem*>(gameprop));
}

void MainWindow::stopultimate()
{
    ultimatemode=false;
}
void MainWindow:: pause()
{
    if(paused==false){
        paused=true;
        instruction->setText("press P to start");
        timer->stop();
    }
    else {
        paused=false;
        instruction->setText("press P to pause");
        timer->start(10);
    }

}

void MainWindow::dead()
{
    emit game_over();

    score_label -> setText("SCORE: "+QString::number(score));
    score_label-> setFont(QFont("Ubuntu", 20));
    restart_but -> setGeometry(220, 500 , 250 , 60);
    restart_but->show();
    timer->stop();
    for(int i=0;i<21;++i){
        flr[i]->hide();
    }
    mon->hide();
    bh->hide();
    doodle->hide();
    gameprop->hide();
    instruction->hide();
    score_label->setGeometry(260 , 250 , 300 , 300);
    gameover_label -> show();
}
void MainWindow:: restart()
{
    gameover=false;
    score = 0;
    restart_but->hide();
    gameover_label->hide();
    score_label -> setText("SCORE: "+QString::number(score));
    score_label->setGeometry(830, 50 , 200 , 80);
    score_label->setFont(QFont("Ubuntu", 14));
    for(int i=0;i<21;++i){
        delete flr[i];
    }
    initialize_scene();
    timer->start(10);

}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(gameover){
        return;
    }
    if(e->key()==Qt::Key_P){
        pause();
        return;
    }
    if(paused==true){

        return;
    }
    double x;
    x = doodle->x() + doodle->pixmap().width() / 2;
    switch(e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        doodle->setPos(doodle->x(), doodle->y() - 10);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        doodle->setPos(doodle->x(), doodle->y() + 10);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        doodle->setPos(doodle->x() - 30, doodle->y());
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        doodle->setPos(doodle->x() + 30, doodle->y());
        break;
    case Qt::Key_Space:
        bullet *b = new bullet;
        b->setPixmap(QPixmap(":/images/bullet").scaled(84, 84));
        b->setPos(doodle->x() + doodle->pixmap().width() / 2 - b->pixmap().width() / 2, doodle->y() - b->pixmap().height());
        b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
        b->connect(this, SIGNAL(game_over()), b, SLOT(bullet_bye_bye()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
        break;
    }

    if(x>820){
        doodle->setPos(20 - doodle->pixmap().width() / 2 , doodle->y());
    }
    if(x<20){
        doodle->setPos(820 - doodle->pixmap().width() / 2 , doodle->y());
    }

}




































