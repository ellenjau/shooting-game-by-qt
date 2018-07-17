#include "fork.h"

#include "mainwindow.h"
#include <QDebug>
#include "player.h"
#include"enemy.h"
#include <QList>

Fork::Fork()
{

}

void Fork::setPlayerInfo(Player *info)
{
    playerInfo = info;
}

void Fork::setEnemyInfo(Enemy *einfo)
{
    enemyInfo = einfo;
}

void Fork::move(){

    //when the fork hit the enemy, score++, enemy hp--
    QList<QGraphicsItem *> collide_ghost = collidingItems();
    for (int i = 0, n = collide_ghost.size(); i < n; ++i)
    {
        if (typeid(*(collide_ghost[i])) == typeid(QGraphicsPixmapItem))
        {
              playerInfo->increase();
              enemyInfo->decrease();

              scene()->removeItem(this);
              delete this;
              return;
         }
     }

    setPos(x(), y() - 3);
       if(y()  < 80) {
           this->scene()->removeItem(this);
           delete this;
       }
}
