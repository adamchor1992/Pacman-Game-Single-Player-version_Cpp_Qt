#include "foodball.h"
#include "game_map.h"
#include <QPainter>

Foodball::Foodball(int x, int y, int width, int height)
{
    m_X = x;
    m_Y = y;
    m_Width = width;
    m_Height = height;
}

QRectF Foodball::boundingRect() const
{
    return QRect(m_X, m_Y, m_Width, m_Height);
}

void Foodball::paint(QPainter *painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::white));

    painter->drawEllipse(m_X, m_Y, m_Width, m_Height);
}
