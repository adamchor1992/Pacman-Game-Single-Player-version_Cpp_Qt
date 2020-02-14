#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QPixmap>

class Map
{
public:
    Map();
    void CreatePathPoints(int beginX, int beginY, int endX, int endY);
    void LoadMapImage();
    bool IsPointAvailable(QPoint);
    QPixmap GetMapBackgroundPicture() {return m_MapBackgroundPixmap;}
    QVector<QPoint> GetPacmanPaths() {return m_PacmanPaths;}

    QRectF boundingRect() const;

private:
    QPixmap m_MapBackgroundPixmap;
    QVector<QPoint> m_PacmanPaths;
};

#endif // MAP_H
