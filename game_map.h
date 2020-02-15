#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QPixmap>

class Map
{
public:
    static bool IsPointAvailable(QPoint);
    static QVector<QPoint>& GetPathPoints() {return m_PathPoints;}

    Map();
    void LoadMapImage();
    void CreatePathPoints(int beginX, int beginY, int endX, int endY);
    QPixmap GetMapBackgroundPicture() const {return m_MapBackgroundPixmap;}

    QRectF boundingRect() const;

private:
    static QVector<QPoint> m_PathPoints;
    QPixmap m_MapBackgroundPixmap;
};

#endif // MAP_H
