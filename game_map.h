#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QPixmap>

class GameMap
{
public:
    static bool IsPointAvailable(QPoint const& point);
    static QVector<QPoint> const& GetPathPoints() {return m_PathPoints;}

    void CreateFoodballPositionsVector();
    void CreatePowerballPositionsVector();
    QVector<QPoint> const& GetFoodballPositions() const {return m_FoodballPositions;}
    QVector<QPoint> const& GetPowerballPositions() const {return m_PowerballPositions;}

    GameMap();
    void LoadMapImage();
    void CreatePathPoints(int beginX, int beginY, int endX, int endY);
    QPixmap GetMapBackgroundPicture() const {return m_MapBackgroundPixmap;}

    QRectF boundingRect() const;

private:
    static QVector<QPoint> m_PathPoints;
    QPixmap m_MapBackgroundPixmap;

    QVector<QPoint> m_FoodballPositions;
    QVector<QPoint> m_PowerballPositions;
};

#endif // MAP_H
