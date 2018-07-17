#include "enemybullet.h"
#include "fork.h"
#include "ui_mainwindow.h"
#include "player.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>

#include "mainwindow.h"

EnemyBullet::EnemyBullet()
{

}

void EnemyBullet::setPlayerInfo(Player *info)
{
    playerInfo = info;
}

void EnemyBullet::move()
{
    // when ball collide with the fork
     QList<QGraphicsItem *> colliding_forks = collidingItems();
     for (int i = 0, n = colliding_forks.size(); i < n; ++i)
     {
         if (typeid(*(colliding_forks[i])) == typeid(Fork))
         {
             //score increase
             playerInfo->increase();

             //ball and fork disappear( still in the heap)
             scene()->removeItem(colliding_forks[i]);
             scene()->removeItem(this);

             // delete from the heap to save memory
             delete colliding_forks[i];
             delete this;
             return;
             }
         }

     // when ball collide with the poop
      QList<QGraphicsItem *> colliding_poops = collidingItems();
      for (int i = 0, n = colliding_poops.size(); i < n; ++i)
      {
          if (typeid(*(colliding_poops[i])) == typeid(Poop))
          {
              //score increase
              playerInfo->increase();

              scene()->removeItem(this);
              delete this;
              return;
              }
       }

      //when ball hit the dog
      QList<QGraphicsItem *> collide_dog = collidingItems();
      for (int i = 0, n = collide_dog.size(); i < n; ++i)
      {
          if (typeid(*(collide_dog[i])) == typeid(QGraphicsPixmapItem))
          {
              playerInfo->decrease();
              scene()->removeItem(this);
              delete this;
              return;
           }
       }

    //no collision
    setPos(x(), y() +15 );
       if(y() +80 >= 645) {
           scene()->removeItem(this);
           delete this;
                          }
}
