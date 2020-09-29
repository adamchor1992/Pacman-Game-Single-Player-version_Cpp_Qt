#include "powerball.h"
#include <QPoint>
#include <QVector>
#include <QPainter>
#include <QDebug>

Powerball::Powerball(int x, int y)
{
    m_X = x;
    m_Y = y;
}

QRectF Powerball::boundingRect() const
{
    return QRect(m_X, m_Y, DIAMETER, DIAMETER);
}

void Powerball::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::white));

    painter->drawEllipse(m_X, m_Y, DIAMETER, DIAMETER);
}
