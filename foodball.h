#pragma once

#include <QVector>
#include <QPoint>
#include <QGraphicsItem>

class Foodball : public QGraphicsItem
{
public:
    Foodball(int x, int y);

private:
    const int DIAMETER = 7;

    int m_X;
    int m_Y;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
