#pragma once

#include <QVector>
#include <QPixmap>

class GameMap
{
public:
    GameMap();
    static bool IsPointAvailable(QPoint const& point);
    static QVector<QPoint> const& GetPathPoints() {return m_PathPoints;}
    QVector<QPoint> GenerateFoodballPositions() const;
    QVector<QPoint> GeneratePowerballPositions() const;

private:
    const int TARGET_FOODBALL_COUNT = 88;
    const int TARGET_POWERBALL_COUNT = 4;

    static QVector<QPoint> m_PathPoints;

    void GeneratePathPoints(int startX, int startY, int endX, int endY);
};
