#include "poop.h"
#include <QDebug>
#include "mainwindow.h"

Poop::Poop()
{

}

void Poop::setPlayerInfo(Player *info)
{
    playerInfo = info;
}

void Poop::setEnemyInfo(Enemy *einfo)
{
    enemyInfo = einfo;
}


void Poop::move(){
    //when the poop hit the enemy, score++, enemy hp--
    QList<QGraphicsItem *> collide_ghost = collidingItems();
    for (int i = 0, n = collide_ghost.size(); i < n; ++i)
    {
        if (typeid(*(collide_ghost[i])) == typeid(QGraphicsPixmapItem))
        {
              playerInfo->increase();
              enemyInfo->decreasebig();

            //fork disappears
              scene()->removeItem(this);
              delete this;
              return;
         }
     }

    setPos(x(), y() - 2);
       if(y()  < 80) {
           this->scene()->removeItem(this);
           delete this;
       }
}
