#include "foodball.h"
#include "game_map.h"
#include <QPainter>

Foodball::Foodball(int x, int y)
{
    m_X = x;
    m_Y = y;
}

QRectF Foodball::boundingRect() const
{
    return QRect(m_X, m_Y, DIAMETER, DIAMETER);
}

void Foodball::paint(QPainter *painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::white));

    painter->drawEllipse(m_X, m_Y, DIAMETER, DIAMETER);
}
