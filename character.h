#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QFont>
//#include "ui_mainwindow.h"
//#include "mainwindow.h"

class Character: public QGraphicsTextItem
{
       Q_OBJECT

public:
    Character(QGraphicsItem * parent=0);
    virtual int gethp() = 0;

public slots:
    virtual int decrease() = 0;

};

#endif // CHARACTER_H
