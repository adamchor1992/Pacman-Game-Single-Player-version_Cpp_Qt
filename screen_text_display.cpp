#include "screen_text_display.h"

ScreenTextDisplay::ScreenTextDisplay()
{
    m_GameResult = GameResult::NO_RESULT_YET;
    m_Score = 0;
}

QRectF ScreenTextDisplay::boundingRect() const
{
    return QRect(X, Y, WIDTH, HEIGHT);
}

void ScreenTextDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    QPen penRed(Qt::red);
    QPen penYellow(Qt::yellow);
    QPen penBlue(Qt::blue);
    painter->setPen(penRed);
    QFont font = painter->font();
    font.setPointSize (POINT_SIZE);
    painter->setFont(font);

    if(m_GameResult == GameResult::GAME_WIN)
    {
        painter->setPen(penYellow);
        painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"CONGRATULATIONS");
        painter->drawText(boundingRect(),Qt::AlignCenter, "FINAL SCORE : " + QString::number(m_Score));
        painter->setPen(penBlue);
        painter->drawText(boundingRect(),Qt::AlignBottom | Qt::AlignHCenter,"PRESS SPACE TO RESTART");
    }
    else if(m_GameResult == GameResult::GAME_LOST)
    {
        painter->setPen(penRed);
        painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"GAME OVER");
        painter->setPen(penYellow);
        painter->drawText(boundingRect(),Qt::AlignCenter, "FINAL SCORE : " + QString::number(m_Score));
        painter->setPen(penBlue);
        painter->drawText(boundingRect(),Qt::AlignBottom | Qt::AlignHCenter,"PRESS SPACE TO RESTART");
    }
    else if(m_GameResult == GameResult::NO_RESULT_YET)
    {
        painter->drawText(boundingRect(),Qt::AlignCenter, "PRESS SPACE TO START");
    }
    else
    {
        assert(false);
    }
}
