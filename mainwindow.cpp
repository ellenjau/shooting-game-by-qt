#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <stdlib.h>
#include <QImage>
#include <QMessageBox>
#include <QColor>

int countspecialskill = 3;
int freezetime = 3;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    playertimer(new QTimer),
    enemytimer(new QTimer),
    balldroptimer(new QTimer),
    playerInfo(new Player),
    enemyInfo(new Enemy),
    checkbar(new QTimer)
{
    //window
    ui->setupUi(this);
    this->setWindowTitle(tr("shoot game"));
    this->setFixedSize(1052,618);

    //scene
    scene = new QGraphicsScene(0, 0, 1050, 610);

    //view
    view = new QGraphicsView;
    view ->setScene(scene);
    view->installEventFilter(this);
    setCentralWidget(view);
    view->setFixedSize(1055,605);
    view->setBackgroundBrush(QImage(":/img/final.jpg").scaled(800,600));

    //player
    player = new QGraphicsPixmapItem(QPixmap(":/img/whitedog.png").scaled(120,120));
    player->setPos(350, 480);
    scene->addItem(player);
    playertimer->start(10);

    //enemy
    enemy = new QGraphicsPixmapItem(QPixmap(":/img/ghost.png").scaled(100,100));
    enemy->setPos(0, 80);
    scene->addItem(enemy);
    enemytimer->start(100);
    connect(enemytimer, SIGNAL(timeout()), this, SLOT(enemyMove()));

    //board
    QGraphicsRectItem* board = new QGraphicsRectItem(800,80,250,620);
    board->setBrush(QBrush(QColor(250,255,255,127)));
    scene->addItem(board);

    //enemy bar background
    QGraphicsRectItem* barback = new QGraphicsRectItem(0,0,800,80);
    barback->setBrush(QBrush(QColor(255,250,255,127)));
    scene->addItem(barback);

    //beautify the view
    QGraphicsRectItem* rightup = new QGraphicsRectItem(800,0,250,80);
    rightup->setBrush(QBrush(QColor(100,255,255,127)));
    scene->addItem(rightup);

    //player's score and hp
    playerInfo->setPos(820,120);
    scene->addItem(playerInfo);

    //enemy's score and hp
    enemyInfo->setPos(10,20);
    scene->addItem(enemyInfo);

    //player's special skill
    specialskill1 = new QGraphicsPixmapItem(QPixmap(":/img/poop.png").scaled(40,30));
    specialskill1->setPos(840, 280);
    scene->addItem(specialskill1);

    specialskill2 = new QGraphicsPixmapItem(QPixmap(":/img/poop.png").scaled(40,30));
    specialskill2->setPos(890, 280);
    scene->addItem(specialskill2);

    specialskill3 = new QGraphicsPixmapItem(QPixmap(":/img/poop.png").scaled(40,30));
    specialskill3->setPos(940, 280);
    scene->addItem(specialskill3);

    frozen1 = new QGraphicsPixmapItem(QPixmap(":/img/cutetimer.png").scaled(40,30));
    frozen1->setPos(840,320);
    scene->addItem(frozen1);

    frozen2 = new QGraphicsPixmapItem(QPixmap(":/img/cutetimer.png").scaled(40,30));
    frozen2->setPos(890,320);
    scene->addItem(frozen2);

    frozen3 = new QGraphicsPixmapItem(QPixmap(":/img/cutetimer.png").scaled(40,30));
    frozen3->setPos(940,320);
    scene->addItem(frozen3);

    connect(enemyInfo,SIGNAL(ghostDieEndGame()), this, SLOT(showGhostDie()));
    connect(playerInfo,SIGNAL(dogDieEndGame()), this, SLOT(showDogDie()));

    checkbar->start(50);
    connect(checkbar, SIGNAL(timeout()), this, SLOT(changebar()));


}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == view && event->type() == QEvent::KeyPress){
        QKeyEvent *kevent = static_cast<QKeyEvent *>(event);

        if(kevent->key() == Qt::Key_Left){
            if (player->x() > 10)
            player->setPos(player->pos() - QPointF(10, 0));
            return true;
        }

        if(kevent->key() == Qt::Key_Right){
            if (player->x() + 130 < 790)
            player->setPos(player->pos() + QPointF(10, 0));
            return true;
        }

        if(kevent->key() == Qt::Key_Up){
            if (player->y() + 120 > 410)
            player->setPos(player->pos() - QPointF(0, 10));
            return true;
        }

        if(kevent->key() == Qt::Key_Down){
            if (player->y() + 120 < 600)
            player->setPos(player->pos() + QPointF(0, 10));
            return true;
        }

    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_S)
    {
        if (freezetime == 3)
        {
            enemytimer->stop();
            playertimer->stop();
            balldroptimer->stop();

            delay();

            enemytimer->start(100);
            playertimer->start(10);
            balldroptimer->start(100);

            scene->removeItem(frozen3);
            delete frozen3;
            freezetime--;
        }

        else if (freezetime == 2)
        {
            enemytimer->stop();
            playertimer->stop();
            balldroptimer->stop();

            delay();

            enemytimer->start(100);
            playertimer->start(10);
            balldroptimer->start(100);

            scene->removeItem(frozen2);
            delete frozen2;
            freezetime--;
        }

        else if (freezetime == 1)
        {
            enemytimer->stop();
            playertimer->stop();
            balldroptimer->stop();

            delay();

            enemytimer->start(100);
            playertimer->start(10);
            balldroptimer->start(100);

            scene->removeItem(frozen1);
            delete frozen1;
            freezetime--;
        }

        else
        {
            QMessageBox::warning(this,tr("OOPS"),
                                 tr("Sorry, no chance to freeze ghost."),
                                 QMessageBox::Ok);
        }

    }

    if (e->key() == Qt::Key_Space){
        Fork * fork = new Fork();
        fork->setPlayerInfo(playerInfo);
        fork->setEnemyInfo(enemyInfo);
        fork->setPixmap(QPixmap(":/img/fork.png").scaled(80, 80));

        fork->setPos(player->x() + 100 - fork->pixmap().width()/2
                     ,player->y()+30 - fork->pixmap().height());

        fork->connect(playertimer, SIGNAL(timeout()), fork, SLOT(move()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(fork));//need to cast

    }

    if (e->key() == Qt::Key_Shift){

        if (countspecialskill == 3)
        {
            Poop * middle = new Poop();
            middle->setPlayerInfo(playerInfo);
            middle->setEnemyInfo(enemyInfo);
            middle->setPixmap(QPixmap(":/img/poop.png").scaled(40, 30));

            middle->setPos(player->x() + 68 - middle->pixmap().width()/2
                           ,player->y() - middle->pixmap().height());

            middle->connect(playertimer, SIGNAL(timeout()), middle, SLOT(move()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(middle));

            Poop * right = new Poop();
            right->setPlayerInfo(playerInfo);
            right->setEnemyInfo(enemyInfo);
            right->setPixmap(QPixmap(":/img/poop.png").scaled(40, 30));

            right->setPos(player->x() + 118 - right->pixmap().width()/2
                          ,player->y() - right->pixmap().height());

            right->connect(playertimer, SIGNAL(timeout()), right, SLOT(move()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(right));

            Poop * left = new Poop();
            left->setPlayerInfo(playerInfo);
            left->setEnemyInfo(enemyInfo);
            left->setPixmap(QPixmap(":/img/poop.png").scaled(40, 30));

            left->setPos(player->x()+18 - left->pixmap().width()/2
                        ,player->y() - left->pixmap().height());

            left->connect(playertimer, SIGNAL(timeout()), left, SLOT(move()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(left));

            scene->removeItem(specialskill3);
            delete specialskill3;
            countspecialskill--;
        }

        else if (countspecialskill == 2)
        {
            Poop * middle = new Poop();
            middle->setPlayerInfo(playerInfo);
            middle->setEnemyInfo(enemyInfo);
            middle->setPixmap(QPixmap(":/img/poop.png").scaled(40, 30));

            middle->setPos(player->x() + 68 - middle->pixmap().width()/2
                           ,player->y() - middle->pixmap().height());

            middle->connect(playertimer, SIGNAL(timeout()), middle, SLOT(move()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(middle));

            Poop * right = new Poop();
            right->setPlayerInfo(playerInfo);
            right->setEnemyInfo(enemyInfo);
            right->setPixmap(QPixmap(":/img/poop.png").scaled(40, 30));

            right->setPos(player->x() + 118 - right->pixmap().width()/2
                          ,player->y() - right->pixmap().height());

            right->connect(playertimer, SIGNAL(timeout()), right, SLOT(move()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(right));

            Poop * left = new Poop();
            left->setPlayerInfo(playerInfo);
            left->setEnemyInfo(enemyInfo);
            left->setPixmap(QPixmap(":/img/poop.png").scaled(40, 30));

            left->setPos(player->x()+18 - left->pixmap().width()/2
                        ,player->y() - left->pixmap().height());

            left->connect(playertimer, SIGNAL(timeout()), left, SLOT(move()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(left));

            scene->removeItem(specialskill2);
            delete specialskill2;
            countspecialskill--;
        }

        else if (countspecialskill == 1)
        {
            Poop * middle = new Poop();
            middle->setPlayerInfo(playerInfo);
            middle->setEnemyInfo(enemyInfo);
            middle->setPixmap(QPixmap(":/img/poop.png").scaled(40, 30));

            middle->setPos(player->x() + 68 - middle->pixmap().width()/2
                           ,player->y() - middle->pixmap().height());

            middle->connect(playertimer, SIGNAL(timeout()), middle, SLOT(move()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(middle));

            Poop * right = new Poop();
            right->setPlayerInfo(playerInfo);
            right->setEnemyInfo(enemyInfo);
            right->setPixmap(QPixmap(":/img/poop.png").scaled(40, 30));

            right->setPos(player->x() + 118 - right->pixmap().width()/2
                          ,player->y() - right->pixmap().height());

            right->connect(playertimer, SIGNAL(timeout()), right, SLOT(move()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(right));

            Poop * left = new Poop();
            left->setPlayerInfo(playerInfo);
            left->setEnemyInfo(enemyInfo);
            left->setPixmap(QPixmap(":/img/poop.png").scaled(40, 30));

            left->setPos(player->x()+18 - left->pixmap().width()/2
                        ,player->y() - left->pixmap().height());

            left->connect(playertimer, SIGNAL(timeout()), left, SLOT(move()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(left));

            scene->removeItem(specialskill1);
            delete specialskill1;
            countspecialskill--;
        }

        else
        {
            QMessageBox::warning(this,tr("OOPS"),
                                 tr("Sorry, the dog has used up its special skill."),
                                 QMessageBox::Ok);
        }

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enemyMove()
{

  if(judge==0)
    {
       if (enemy->x()+100==800)
       {
           int possibility = rand() % 2;
           if (possibility==1)
           {
               EnemyBullet * ball = new EnemyBullet();
               ball->setPlayerInfo(playerInfo);
               ball->setPixmap(QPixmap(":/img/ball.png").scaled(30, 30));
               ball->setPos(enemy->x()+52, 180);
               balldroptimer->start(100);
               ball->connect(balldroptimer, SIGNAL(timeout()), ball, SLOT(move()));
               scene->addItem(static_cast<QGraphicsPixmapItem*>(ball));
           }

         judge=1;
       }
       else
        {
           enemy->setPos(enemy->x() + 25,enemy->y());

           int possibility = rand() % 7;
           if (possibility==1)
           {
               EnemyBullet * ball = new EnemyBullet();
               ball->setPlayerInfo(playerInfo);
               ball->setPixmap(QPixmap(":/img/ball.png").scaled(30, 30));
               ball->setPos(enemy->x()+52, 180);
               balldroptimer->start(100);
               ball->connect(balldroptimer, SIGNAL(timeout()), ball, SLOT(move()));
               scene->addItem(static_cast<QGraphicsPixmapItem*>(ball));
           }
       }
     }

   else if(judge==1)
     {
        if (enemy->x()==0)
          {
            judge=0;
            int possibility = rand() % 2;
            if (possibility==1)
            {
                EnemyBullet * ball = new EnemyBullet();
                ball->setPlayerInfo(playerInfo);
                ball->setPixmap(QPixmap(":/img/ball.png").scaled(30, 30));
                ball->setPos(enemy->x()+52, 180);
                balldroptimer->start(100);
                ball->connect(balldroptimer, SIGNAL(timeout()), ball, SLOT(move()));
                scene->addItem(static_cast<QGraphicsPixmapItem*>(ball));
            }
          }
        else
          {
            enemy->setPos(enemy->x() -25,enemy->y());
            int possibility = rand() % 7;
            if (possibility==1)
            {
                EnemyBullet * ball = new EnemyBullet();
                ball->setPlayerInfo(playerInfo);
                ball->setPixmap(QPixmap(":/img/ball.png").scaled(30, 30));
                ball->setPos(enemy->x()+52, 180);
                balldroptimer->start(100);
                ball->connect(balldroptimer, SIGNAL(timeout()), ball, SLOT(move()));
                scene->addItem(static_cast<QGraphicsPixmapItem*>(ball));
            }
          }
      }
}

void MainWindow::showGhostDie()
{
//    qDebug() << "ok" << endl;
    int now = enemyInfo->gethp();

    if(now<=0)
    {
       scene->removeItem(enemy);
       balldroptimer->stop();
       playertimer->stop();
       enemytimer->stop();
       QMessageBox::about(this,tr("Congrats"),tr("you win!"));
    }

}

void MainWindow::showDogDie()
{
    int update = playerInfo->gethp();
    if(update<=0)
    {
       scene->removeItem(player);
       balldroptimer->stop();
       playertimer->stop();
       enemytimer->stop();

       QMessageBox::about(this,tr("Sorry"),
                          tr("You lose, but it's ok.\n"
                             " The dog goes to heaven."));
    }
}

void MainWindow::changebar()
{
    int l = enemyInfo->gethp();
    QGraphicsRectItem* barlong = new QGraphicsRectItem(230,35,l*15,5);
    barlong->setBrush(QBrush(Qt::yellow));
    scene->addItem(barlong);
    delay();
    scene->removeItem(barlong);

}

void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(3);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_actionrules_triggered()
{
    QMessageBox::about(this,tr("How to play?"),
                       tr("1. press 'RIGHT','LEFT', 'UP' and 'DOWN' to move accordingly.\n"
                          "2. press 'SPACE' to spawn fork to shoot ghost.\n"
                          "3. press 'SHIFT' to evoke special skill poop for at most 3 times.\n"
                          "4. press 'S' to evoke special skill freeze ghost for at most 3 times.\n"
                          "5. either ghost or dog lose when its hp=0"));
}
