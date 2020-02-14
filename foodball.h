#ifndef FOODBALL_H
#define FOODBALL_H

#include <QVector>
#include <QPoint>

class FoodBall
{
public:
    FoodBall();
    void CreateFoodballPositionsVector();
    QVector<QPoint> GetFoodBallPositions() const {return m_FoodballPositions;}

private:
    QVector<QPoint> m_FoodballPositions;
};

#endif // FOODBALL_H
