#ifndef FORK_H
#define FORK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "player.h"
#include "enemy.h"
#include "weapon.h"

class MainWindow;

class Fork: public Weapon
{
    Q_OBJECT

public:
    Fork();
    virtual void setPlayerInfo(Player *info);
    void setEnemyInfo(Enemy *einfo);

public slots:
    virtual void move();

private:
    Player *playerInfo;
    Enemy *enemyInfo;

};

#endif // FORK_H
