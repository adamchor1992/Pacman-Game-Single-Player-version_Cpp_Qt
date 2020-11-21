#pragma once

#include <QVector>
#include <QPixmap>

class GameMap
{
public:
    GameMap();
    static bool IsPointAvailable(QPoint const& point);
    static QVector<QPoint> const& GetPathPoints() {return m_PathPoints;}
    QPixmap const& GetMapBackgroundPicture() const {return m_MapBackgroundPixmap;}
    QVector<QPoint> const& GetFoodballPositions() const {return m_FoodballPositions;}
    QVector<QPoint> const& GetPowerballPositions() const {return m_PowerballPositions;}

private:
    const int TARGET_FOODBALL_COUNT = 88;
    const int TARGET_POWERBALL_COUNT = 4;

    static QVector<QPoint> m_PathPoints;
    const QPixmap m_MapBackgroundPixmap;
    QVector<QPoint> m_FoodballPositions;
    QVector<QPoint> m_PowerballPositions;

    void GeneratePathPoints(int startX, int startY, int endX, int endY);
    void GenerateFoodballPositions();
    void GeneratePowerballPositions();
};
