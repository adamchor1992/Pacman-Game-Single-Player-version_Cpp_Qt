#include "textstartend.h"

TextStartEnd::TextStartEnd()
{
    game_won=false;
    game_lost=false;

    w=600;
    h=200;
    x=614/2-w/2;
    y=714/2-h/2;

    score=0;
    playing=false;
}

QRectF TextStartEnd::boundingRect() const
{
    return QRect(x, y, w, h);
}

void TextStartEnd::setScore(int _score)
{
    this -> score = _score;
}

void TextStartEnd::setGameWon(bool _game_won)
{
    this -> game_won=game_won;
}

void TextStartEnd::setGameLost(bool _game_lost)
{
    this -> game_lost=_game_lost;
}

void TextStartEnd::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::red);
    painter->setPen(pen);
    QFont font=painter->font();
    font.setPointSize (33);
    painter->setFont(font);

    if(!playing)
    {
        if(game_won)
        {
            painter->drawText(boundingRect().x(),boundingRect().y(), "CONGRATULATIONS, YOU WON");
            painter->drawText(boundingRect(),Qt::AlignCenter, "FINAL SCORE : "+QString::number(score));
        }
        else if(game_lost)
        {
            painter->drawText(boundingRect().x(),boundingRect().y(), "YOU LOST, GAME OVER");
            painter->drawText(boundingRect(),Qt::AlignCenter, "FINAL SCORE : "+QString::number(score));
        }
        else
        {
            painter->drawText(boundingRect(),Qt::AlignCenter, "PRESS SPACE TO START");
        }
    }
}
