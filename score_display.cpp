#include "score_display.h"
#include <QPainter>

ScoreDisplay::ScoreDisplay()
{
    m_Width=600;
    m_Height=200;
    m_X=0;
    m_Y=680;

    m_Score=0;
}

void ScoreDisplay::setScore(int score)
{
    m_Score=score;
}

QRectF ScoreDisplay::boundingRect() const
{
    return QRect(m_X, m_Y, m_Width, m_Height);
}

void ScoreDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font = painter->font();
    font.setPointSize (30);

    painter->setPen(QPen(Qt::white));
    painter->setFont(font);

    painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter, "Score: " + QString::number(m_Score));
}
