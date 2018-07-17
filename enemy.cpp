#include "enemy.h"
#include "character.h"
#include "player.h"

Enemy::Enemy(QGraphicsItem *parent):
    Character(parent)
{
    // initialize
    ghosthp = 30;
    //draw the text
    setPlainText(QString("Ghost's Hp: ")
                 + QString::number(ghosthp));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("Arial",18));

}


int Enemy::decreasebig()
{
    ghosthp-=5;

    if (ghosthp <= 0)
    {
        setPlainText(QString("YA!!!ghost has died")
                     + QString("\n")
                     +QString("Your score this round is displayed at the right board"));
        //end game
        emit ghostDieEndGame();

     }
    else
      {
        setPlainText(QString("Ghost's Hp: ") + QString::number(ghosthp));
      }
    return 0;
 }

int Enemy::decrease()
{
    ghosthp--;

    if (ghosthp <= 0)
     {
        setPlainText(QString("YA!!!ghost has died")
                     + QString("\n")
                     +QString("Your score this round is displayed at the right board"));
        //end game
        emit ghostDieEndGame();
     }
    else
      {
        setPlainText(QString("Ghost's Hp: ") + QString::number(ghosthp));
      }
    return 0;
 }

int Enemy::gethp()
{
    return ghosthp;
}
