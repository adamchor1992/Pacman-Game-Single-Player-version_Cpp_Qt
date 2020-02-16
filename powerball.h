#ifndef POWERBALL_H
#define POWERBALL_H

#include <QVector>
#include <QPoint>
#include <QGraphicsItem>

class Powerball : public QGraphicsItem
{
public:
    Powerball(int x, int y, int width, int height);
    ~Powerball();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    int m_X;
    int m_Y;
    int m_Width;
    int m_Height;
};

#endif // POWERBALL_H
