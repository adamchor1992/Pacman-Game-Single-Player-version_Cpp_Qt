#ifndef FOODBALL_H
#define FOODBALL_H

#include <QVector>
#include <QPoint>
#include <QGraphicsItem>

class Foodball : public QGraphicsItem
{
public:
    Foodball(int x, int y, int width, int height);

private:
    int m_X;
    int m_Y;
    int m_Width;
    int m_Height;

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // FOODBALL_H
