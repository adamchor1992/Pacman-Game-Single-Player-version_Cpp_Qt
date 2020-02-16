#ifndef FOODBALL_H
#define FOODBALL_H

#include <QVector>
#include <QPoint>
#include <QGraphicsItem>

class Foodball : public QGraphicsItem
{
public:
    Foodball(int x, int y, int width, int height);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    int m_X;
    int m_Y;
    int m_Width;
    int m_Height;
};

#endif // FOODBALL_H
