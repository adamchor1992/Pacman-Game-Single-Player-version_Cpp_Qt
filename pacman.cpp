#include "map.h"
#include "pacman.h"
#include <QGraphicsPixmapItem>
#include <QPainter>

Pacman::Pacman()
{
    m_AnimeState = 0;
    m_AnimationModifyFactor = 6;
    LoadPacmanImages();
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

void Pacman::Advance()
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
