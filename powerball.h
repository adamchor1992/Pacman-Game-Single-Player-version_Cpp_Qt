#ifndef POWERBALL_H
#define POWERBALL_H

#include <QGraphicsItem>
#include <QPainter>

#include <QVector>
#include <QPoint>

class PowerBall
{
private:
    QVector<QPoint> powerballpositions;
public:
    PowerBall();
    QVector<QPoint> getPowerBallPositions();
};

#endif // POWERBALL_H
