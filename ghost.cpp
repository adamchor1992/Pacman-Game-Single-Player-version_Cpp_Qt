#include "ghost.h"

Ghost::Ghost()
{
    ghostdirection=1;
    is_scared=false;
    scared_white=false;

    ghost_pixmap.load(":/images/ghostpurple.png");
    ghost_scared_blue.load(":/images/ghostscared.png");
    ghost_scared_white.load(":/images/ghostscaredwhite.png");
}

QRectF Ghost::boundingRect() const
{
    return QRect(ghost_x-15,ghost_y-15,20,20);
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!is_scared)
    {
        painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,ghost_pixmap);
    }
    else
    {
        if(scared_white)
        {
            painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,ghost_scared_white);
        }
        else
        {
            painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,ghost_scared_blue);
        }
    }
}

void Ghost::setGhost_X(int x)
{
    ghost_x=x;
}

void Ghost::setGhost_Y(int y)
{
    ghost_y=y;
}

void Ghost::setGhostColor(QString col)
{
    if(col=="blue")
    {
        ghost_pixmap.load(":/images/ghostblue.png");
    }
    else if(col=="orange")
    {
        ghost_pixmap.load(":/images/ghostorange.png");
    }
    else if(col=="red")
    {
        ghost_pixmap.load(":/images/ghostred.png");
    }
}
