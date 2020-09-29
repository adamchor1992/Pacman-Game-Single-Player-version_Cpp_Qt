#pragma once

#include <QVector>
#include <QPoint>
#include <QGraphicsItem>

class Powerball : public QGraphicsItem
{
public:
    Powerball(int x, int y);

private:
    const int DIAMETER = 15;

    int m_X;
    int m_Y;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};
