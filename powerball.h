#pragma once

#include <QVector>
#include <QPoint>
#include <QGraphicsItem>

class Powerball : public QGraphicsItem
{
public:
    Powerball(int x, int y, int width, int height);

private:
    int m_X;
    int m_Y;
    int m_Width;
    int m_Height;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};
