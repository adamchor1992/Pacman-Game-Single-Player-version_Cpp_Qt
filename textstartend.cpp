#include "textstartend.h"

TextStartEnd::TextStartEnd()
{
    m_GameWon=false;
    m_GameLost=false;

    m_W=600;
    m_H=200;
    m_X=614/2-m_W/2;
    m_Y=714/2-m_H/2;

    m_Score=0;
    m_Playing=false;
}

QRectF TextStartEnd::boundingRect() const
{
    return QRect(m_X, m_Y, m_W, m_H);
}

void TextStartEnd::SetScore(int score)
{
    m_Score = score;
}

void TextStartEnd::SetGameWon(bool gameWon)
{
    m_GameWon = gameWon;
}

void TextStartEnd::SetGameLost(bool gameLost)
{
    m_GameLost = gameLost;
}

void TextStartEnd::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen_red(Qt::red);
    QPen pen_yellow(Qt::yellow);
    QPen pen_blue(Qt::blue);
    painter->setPen(pen_red);
    QFont font = painter->font();
    font.setPointSize (30);
    painter->setFont(font);

    if(!m_Playing)
    {
        if(m_GameWon)
        {
            painter->setPen(pen_yellow);
            painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"CONGRATULATIONS");
            painter->drawText(boundingRect(),Qt::AlignCenter, "FINAL SCORE : "+QString::number(m_Score));
            painter->setPen(pen_blue);
            painter->drawText(boundingRect(),Qt::AlignBottom | Qt::AlignHCenter,"PRESS SPACE TO RESTART");
        }
        else if(m_GameLost)
        {
            painter->setPen(pen_red);
            painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"YOU LOST, GAME OVER");
            painter->setPen(pen_yellow);
            painter->drawText(boundingRect(),Qt::AlignCenter, "FINAL SCORE : "+QString::number(m_Score));
            painter->setPen(pen_blue);
            painter->drawText(boundingRect(),Qt::AlignBottom | Qt::AlignHCenter,"PRESS SPACE TO RESTART");
        }
        else
        {
            painter->drawText(boundingRect(),Qt::AlignCenter, "PRESS SPACE TO START");
        }
    }
}
