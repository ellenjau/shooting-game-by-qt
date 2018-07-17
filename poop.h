#ifndef POOP_H
#define POOP_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


#include "player.h"
#include "enemy.h"
#include "weapon.h"

class MainWindow;

class Poop: public Weapon
{
    Q_OBJECT

public:
    Poop();
    virtual void setPlayerInfo(Player *info);
    void setEnemyInfo(Enemy *einfo);

public slots:
    virtual void move();

private:
    Player *playerInfo;
    Enemy *enemyInfo;
};

#endif // POOP_H
