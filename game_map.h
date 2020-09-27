#pragma once

#include <QVector>
#include <QPixmap>

class GameMap
{
public:
    GameMap();

    static bool IsPointAvailable(QPoint const& point);
    static QVector<QPoint> const& GetPathPoints() {return m_PathPoints;}

    QPixmap GetMapBackgroundPicture() const {return m_MapBackgroundPixmap;}
    QVector<QPoint> const& GetFoodballPositions() const {return m_FoodballPositions;}
    QVector<QPoint> const& GetPowerballPositions() const {return m_PowerballPositions;}

private:
    static QVector<QPoint> m_PathPoints;
    QPixmap m_MapBackgroundPixmap;
    QVector<QPoint> m_FoodballPositions;
    QVector<QPoint> m_PowerballPositions;

    void LoadMapImage();
    void CreatePathPoints(int startX, int startY, int endX, int endY);
    void CreateFoodballPositionsVector();
    void CreatePowerballPositionsVector();

    QRectF boundingRect() const;
};
