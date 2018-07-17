#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QtGui>

#include "fork.h"
#include "enemybullet.h"
#include "player.h"
#include "enemy.h"
#include "poop.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     bool eventFilter(QObject *watched, QEvent *event);
     void delay();

public slots:
    void keyPressEvent(QKeyEvent *e);
    void enemyMove();

    void showGhostDie();
    void showDogDie();
    void changebar();

private slots:
    void on_actionrules_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView * view;

    QTimer *playertimer;
    QTimer *enemytimer;
    QTimer *balldroptimer;
    QTimer *checkbar;

    QGraphicsItem *player;
    QGraphicsItem *enemy;
    QGraphicsItem *specialskill1;
    QGraphicsItem *specialskill2;
    QGraphicsItem *specialskill3;
    QGraphicsItem *frozen1;
    QGraphicsItem *frozen2;
    QGraphicsItem *frozen3;

    Player* playerInfo;
    Enemy* enemyInfo;

    bool judge = 0;




};

#endif // MAINWINDOW_H
