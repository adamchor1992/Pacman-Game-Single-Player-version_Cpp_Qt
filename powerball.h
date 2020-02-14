#ifndef POWERBALL_H
#define POWERBALL_H

#include <QVector>
#include <QPoint>

class PowerBall
{
public:
    PowerBall();
    QVector<QPoint> GetPowerBallPositions() {return m_PowerballPositions;}

private:
    QVector<QPoint> m_PowerballPositions;
};

#endif // POWERBALL_H
