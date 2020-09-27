#include "score_display.h"
#include <QPainter>

ScoreDisplay::ScoreDisplay()
{
    m_Score = 0;
}

void ScoreDisplay::SetScore(int score)
{
    m_Score = score;
}

QRectF ScoreDisplay::boundingRect() const
{
    return QRect(X, Y, WIDTH, HEIGHT);
}

void ScoreDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    QFont font = painter->font();
    font.setPointSize(POINT_SIZE);

    painter->setPen(QPen(Qt::white));
    painter->setFont(font);

    painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter, "Score: " + QString::number(m_Score));
}
