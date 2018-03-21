#ifndef MAP_H
#define MAP_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QVector>
#include <QPixmap>

class Map
{
public:
    Map();
    void CreatePathPoints(int x_begin, int y_begin, int x_end, int y_end);
    void LoadMapImage();
    ~Map();
    QPixmap map_background_picture;

private:
    QVector<QPoint> pacman_paths;
};

#endif // MAP_H
