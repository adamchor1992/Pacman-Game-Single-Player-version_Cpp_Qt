#ifndef FOODBALL_H
#define FOODBALL_H

#include <QVector>
#include <QPoint>

class FoodBall
{
public:
    FoodBall();
    QVector<QPoint> GetFoodBallPositions() {return m_FoodballPositions;}
    void CreateFoodballPositionsVector();

private:
    int m_FoodballCount;
    QVector<QPoint> m_FoodballPositions;
    QVector<QPoint> m_PacmanMapForReference;
};

#endif // FOODBALL_H
