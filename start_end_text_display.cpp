#include "start_end_text_display.h"

StartEndTextDisplay::StartEndTextDisplay()
{
    m_Width=600;
    m_Height=200;
    m_X=614/2-m_Width/2;
    m_Y=714/2-m_Height/2;

    m_GameWon=false;
    m_GameLost=false;

    m_Score=0;
    m_Playing=false;
}

void StartEndTextDisplay::SetScore(int score)
{
    m_Score = score;
}

void StartEndTextDisplay::SetGameWon(bool gameWon)
{
    m_GameWon = gameWon;
}

void StartEndTextDisplay::SetGameLost(bool gameLost)
{
    m_GameLost = gameLost;
}

QRectF StartEndTextDisplay::boundingRect() const
{
    return QRect(m_X, m_Y, m_Width, m_Height);
}

void StartEndTextDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
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
