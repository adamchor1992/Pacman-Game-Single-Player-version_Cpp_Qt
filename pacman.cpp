#include "map.h"
#include "pacman.h"
#include <QGraphicsPixmapItem>
#include <QPainter>

Pacman::Pacman()
{
    LoadPacmanImage();
}

QRectF Pacman::boundingRect() const
{
    return QRect(pac_x-15, pac_y-15, 20, 20);
}

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(pac_x-15,pac_y-15,30,30,pacman_pixmap);
}

void Pacman::LoadPacmanImage()
{
    pacman_pixmap.load("://images/pacman_image.png");
}

void Pacman::SetPacX(int x)
{
    pac_x=x;
}

void Pacman::SetPacY(int y)
{
    pac_y=y;
}

void Pacman::SetDirection(int dir)
{
    direction=dir;
}


