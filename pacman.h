#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>

class Pacman : public QGraphicsItem
{
private:
    int pac_x;
    int pac_y;
    int direction;
    int nextdirection;
    bool is_moving;

    QPixmap pacman_pixmap;

public:
    Pacman();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void LoadPacmanImage();
    void setPac_X(int);
    void setPac_Y(int);
    void setDirection(int dir);
    void setNextDirection(int dir);

    int getPac_X() {return pac_x;}
    int getPac_Y() {return pac_y;}
    int getDirection() {return direction;}
    int getNextDirection() {return nextdirection;}
};

#endif // PACMAN_H
