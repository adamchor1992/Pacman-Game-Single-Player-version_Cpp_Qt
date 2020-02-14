#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QPixmap>

class Map
{
public:
    Map();
    void LoadMapImage();
    void CreatePathPoints(int beginX, int beginY, int endX, int endY);
    QPixmap GetMapBackgroundPicture() const {return m_MapBackgroundPixmap;}

    static bool IsPointAvailable(QPoint);
    static QVector<QPoint>& GetPathPoints() {return m_PathPoints;}

    QRectF boundingRect() const;

private:
    QPixmap m_MapBackgroundPixmap;
    static QVector<QPoint> m_PathPoints;
};

#endif // MAP_H
