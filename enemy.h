#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Player;

class Enemy: public Character
{
    Q_OBJECT

public:
    Enemy(QGraphicsItem * parent=0);
    virtual int gethp();

public slots:
    virtual int decrease();//-1
    int decreasebig();//-5

signals:
    void ghostDieEndGame();

private:
    int ghosthp;

};

#endif // ENEMY_H

