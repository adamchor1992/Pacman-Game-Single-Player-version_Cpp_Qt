#include "powerball.h"
#include <QPoint>
#include <QVector>
#include <QPainter>
#include <QDebug>

Powerball::Powerball(int x, int y, int width, int height)
{
    m_X = x;
    m_Y = y;
    m_Width = width;
    m_Height = height;
}

Powerball::~Powerball()
{
    qDebug() << "Destructor";
}

QRectF Powerball::boundingRect() const
{
    return QRect(m_X, m_Y, m_Width, m_Height);
}

void Powerball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::white));

    painter->drawEllipse(m_X, m_Y, m_Width, m_Height);
}
