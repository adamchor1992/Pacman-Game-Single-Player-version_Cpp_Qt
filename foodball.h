#ifndef FOODBALL_H
#define FOODBALL_H

#include <QGraphicsItem>
#include <QPoint>

class FoodBall
{
private:
    int foodballcount;
    QVector<QPoint> foodballpositions;
    QVector<QPoint> pacmanmapforreference;
public:
    FoodBall();

    QVector<QPoint> getFoodBallPositions();
    void CreateFoodballPositionsVector();
};

#endif // FOODBALL_H
