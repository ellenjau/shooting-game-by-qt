#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Player;

class Weapon: public QObject, public QGraphicsPixmapItem
{
     Q_OBJECT

public:
    Weapon();
    virtual void setPlayerInfo(Player *info) = 0;

public slots:
    virtual void move() = 0;
};

#endif // WEAPON_H
