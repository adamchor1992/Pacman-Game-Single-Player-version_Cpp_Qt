#ifndef MAP_H
#define MAP_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QVector>
#include <QPixmap>

class Map
{
private:
    QVector<QPoint> pacman_paths;

public:
    Map();
    void CreatePathPoints(int x_begin, int y_begin, int x_end, int y_end);
    void LoadMapImage();
    bool IsPointAvailable(QPoint);
    QRectF boundingRect() const;

    QPixmap map_background_picture;

    ~Map();
};

#endif // MAP_H
