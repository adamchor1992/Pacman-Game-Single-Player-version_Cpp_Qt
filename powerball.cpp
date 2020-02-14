#include "powerball.h"
#include <QPoint>
#include <QVector>

PowerBall::PowerBall()
{
    QPoint powerball1Position = QPoint(35,75);
    QPoint powerball2Position = QPoint(579,75);
    QPoint powerball3Position = QPoint(35,514);
    QPoint powerball4Position = QPoint(579,514);

    m_PowerballPositions.push_back(powerball1Position);
    m_PowerballPositions.push_back(powerball2Position);
    m_PowerballPositions.push_back(powerball3Position);
    m_PowerballPositions.push_back(powerball4Position);
}

