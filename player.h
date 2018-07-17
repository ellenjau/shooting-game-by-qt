#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

class Player: public Character
{
    Q_OBJECT

public:
    Player(QGraphicsItem * parent=0);
    virtual int gethp();

public slots:
    virtual int decrease();//-1
    void increase();

signals:
    void dogDieEndGame();

private:
    int health;
    int score;

};
#endif
