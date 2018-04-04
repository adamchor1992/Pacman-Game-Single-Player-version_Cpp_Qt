#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>

class Pacman : public QGraphicsItem
{
private:
    int pac_x;
    int pac_y;
    int direction;

public:
    Pacman();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void LoadPacmanImage();
    void SetPacX(int);
    void SetPacY(int);
    void SetDirection(int dir);

    QPixmap pacman_pixmap;
};

#endif // PACMAN_H
