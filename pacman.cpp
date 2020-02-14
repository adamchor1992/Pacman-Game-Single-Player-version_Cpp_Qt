#include "map.h"
#include "pacman.h"
#include <QGraphicsPixmapItem>
#include <QPainter>

int Pacman::m_PacX{};
int Pacman::m_PacY{};

Pacman::Pacman()
{
    m_AnimeState = 0;
    m_AnimationModifyFactor = 6;
    LoadPacmanImages();
}

void Pacman::Reset()
{
    m_AnimeState = 0;
    m_AnimationModifyFactor = 6;

    SetDirection(1); //pacman moves left after game start
    SetPacX(320);
    SetPacY(514);
}

void Pacman::AdvanceAnimation()
{
    if(m_AnimeState>8*m_AnimationModifyFactor-2)
    {
        m_AnimeState=0;
    }
    else
    {
        m_AnimeState++;
    }
}

void Pacman::LoadPacmanImages()
{
    m_Right1.load(":/pacman/images/pacman_images/pacclose.png");
    m_Right2.load(":/pacman/images/pacman_images/pacopen1.png");
    m_Right3.load(":/pacman/images/pacman_images/pacopen2.png");
    m_Right4.load(":/pacman/images/pacman_images/pacopen3.png");

    m_Up1.load(":/pacman/images/pacman_images/paccloseu.png");
    m_Up2.load(":/pacman/images/pacman_images/pacopen1u.png");
    m_Up3.load(":/pacman/images/pacman_images/pacopen2u.png");
    m_Up4.load(":/pacman/images/pacman_images/pacopen3u.png");

    m_Down1.load(":/pacman/images/pacman_images/pacclosed.png");
    m_Down2.load(":/pacman/images/pacman_images/pacopen1d.png");
    m_Down3.load(":/pacman/images/pacman_images/pacopen2d.png");
    m_Down4.load(":/pacman/images/pacman_images/pacopen3d.png");

    m_Left1.load(":/pacman/images/pacman_images/pacclosel.png");
    m_Left2.load(":/pacman/images/pacman_images/pacopen1l.png");
    m_Left3.load(":/pacman/images/pacman_images/pacopen2l.png");
    m_Left4.load(":/pacman/images/pacman_images/pacopen3l.png");
}

void Pacman::SetPacX(int x)
{
    m_PacX=x;
}

void Pacman::SetPacY(int y)
{
    m_PacY=y;
}

void Pacman::SetDirection(int dir)
{
    m_Direction=dir;
}

void Pacman::SetNextDirection(int dir)
{
    m_NextDirection=dir;
}

void Pacman::Move()
{
    QPoint p;

    int pac_x = GetPacX();
    int pac_y = GetPacY();
    int direction = GetDirection();
    int nextdirection = GetNextDirection();

    if(nextdirection!=direction)
    {
        switch(nextdirection)
        {
        case 1: //left
            p.setX(pac_x-1);
            p.setY(pac_y);

            if(Map::IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 2: //up
            p.setX(pac_x);
            p.setY(pac_y-1);
            if(Map::IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 3: //down
            p.setX(pac_x);
            p.setY(pac_y+1);
            if(Map::IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 4: //right
            p.setX(pac_x+1);
            p.setY(pac_y);
            if(Map::IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;
        }
    }

    switch(direction)
    {
    case 1: //left
        p.setX(pac_x-1);
        p.setY(pac_y);
        SetDirection(direction);

        if(Map::IsPointAvailable(p))
        {
            pac_x = pac_x - 1;
        }

        break;

    case 2: //up
        p.setX(pac_x);
        p.setY(pac_y-1);
        SetDirection(direction);

        if(Map::IsPointAvailable(p))
        {
            pac_y= pac_y - 1;
        }

        break;

    case 3: //down
        p.setX(pac_x);
        p.setY(pac_y+1);
        SetDirection(direction);

        if(Map::IsPointAvailable(p))
        {
            pac_y= pac_y + 1;
        }

        break;

    case 4: //right
        p.setX(pac_x+1);
        p.setY(pac_y);
        SetDirection(direction);

        if(Map::IsPointAvailable(p))
        {
            pac_x = pac_x + 1;
        }

        break;
    }

    if(pac_x==0 && pac_y==318) //teleportation when reached left boundary of middle horizontal line
    {
        pac_x=613;
    }

    if(pac_x==614 && pac_y==318) //teleportation when reached right boundary of middle horizontal line
    {
        pac_x=1;
    }

    SetPacX(pac_x);
    SetPacY(pac_y);
}

QRectF Pacman::boundingRect() const
{
    return QRect(m_PacX-15, m_PacY-15, 20, 20);
}

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch(m_Direction)
    {
        case 1:
            if(m_AnimeState<2*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Left1);
            }
            else if(m_AnimeState<4*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Left2);
            }
            else if(m_AnimeState<6*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Left3);
            }
            else if(m_AnimeState<8*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Left4);
            }
            break;
        case 4:
            if(m_AnimeState<2*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Right1);
            }
            else if(m_AnimeState<4*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Right2);
            }
            else if(m_AnimeState<6*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Right3);
            }
            else if(m_AnimeState<8*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Right4);
            }
            break;
        case 3:
            if(m_AnimeState<2*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Down1);
            }
            else if(m_AnimeState<4*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Down2);
            }
            else if(m_AnimeState<6*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Down3);
            }
            else if(m_AnimeState<8*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Down4);
            }
            break;
        case 2:
            if(m_AnimeState<2*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Up1);
            }
            else if(m_AnimeState<4*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Up2);
            }
            else if(m_AnimeState<6*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Up3);
            }
            else if(m_AnimeState<8*m_AnimationModifyFactor)
            {
                painter->drawPixmap(m_PacX-15, m_PacY-15, 30, 30, m_Up4);
            }
            break;
    }
}
