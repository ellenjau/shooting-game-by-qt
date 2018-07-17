#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "weapon.h"
#include "player.h"

class MainWindow;

class EnemyBullet: public Weapon
{
    Q_OBJECT

public:
    EnemyBullet();
    virtual void setPlayerInfo(Player *info);

public slots:
    virtual void move();

private:
    Player *playerInfo;
};


#endif// ENEMYBULLET_H
