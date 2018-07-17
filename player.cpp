#include "player.h"
#include "mainwindow.h"


Player::Player(QGraphicsItem *parent): Character(parent){
    // initialize
    score = 0;
    health = 10;

    // draw the text
    setPlainText(QString("Dog's Score: ") + QString::number(score)
                 +QString("\n\n")
           + QString("Dog's Hp: ") + QString::number(health)
                 +QString("\n\n")
           + QString("Dog's Special Skill:"));

    setDefaultTextColor(Qt::blue);
    setFont(QFont("Arial",18));
}

void Player::increase(){
    score+=2;
    setPlainText(QString("Dog's Score: ") + QString::number(score)
                 +QString("\n\n")
           + QString("Dog's Hp: ") + QString::number(health)
                 +QString("\n\n")
           + QString("Dog's Special Skill:"));
}


int Player::decrease(){
    health--;
    score--;

    if (health <= 0)
    {
        setPlainText(QString("GG")
                     + QString("\n")
                     + QString("Dog has died ><")
                     + QString("\n")
                     + QString("Score this round is: ")
                     + QString("\n")
                     +QString("%1").arg(score));
        //end game
        emit dogDieEndGame();
    }

    else
    {
        setPlainText(QString("Dog's Score: ") + QString::number(score)
                 +QString("\n\n")
           + QString("Dog's Hp: ") + QString::number(health)
                 +QString("\n\n")
           + QString("Dog's Special Skill:"));
    }

    return 0;
}

int Player::gethp()
{
    return health;
}




