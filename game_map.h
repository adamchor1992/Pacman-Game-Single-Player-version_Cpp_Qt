#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QPixmap>

class GameMap
{
public:
    static bool IsPointAvailable(QPoint);
    static QVector<QPoint>& GetPathPoints() {return m_PathPoints;}

    void CreateFoodballPositionsVector();
    void CreatePowerballPositionsVector();
    QVector<QPoint> GetFoodBallPositions() const {return m_FoodballPositions;}
    QVector<QPoint> GetPowerBallPositions() const {return m_PowerballPositions;}

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
