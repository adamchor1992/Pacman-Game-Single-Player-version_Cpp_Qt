#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QPainter>

class Ghost : public QGraphicsItem
{
private:
    QPixmap ghost_pixmap;
    QPixmap ghost_scared_blue;
    QPixmap ghost_scared_white;

    bool is_scared;
    bool scared_white;

    int ghost_x,ghost_y;
    int ghostdirection;
    int nextghostdirection;

public:
    Ghost();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance();

    void setGhost_X(int);
    void setGhost_Y(int);
    void setIsScared(bool option) {is_scared=option;}
    //void setScarestate(int number) {scarestat}
    void setScaredWhite(bool option) {scared_white=option;}
    void setGhostDirection(int dir) {ghostdirection=dir;}
    void setNextGhostDirection(int dir) {nextghostdirection=dir;}
    void setGhostColor(QString col);

    int getGhost_X() {return ghost_x;}
    int getGhost_Y() {return ghost_y;}
    int getGhostDirection() {return ghostdirection;}
    int getNextGhostDirection() {return nextghostdirection;}
    bool getIsScared() {return is_scared;}
    bool getScaredWhite() {return scared_white;}
};

#endif // GHOST_H
