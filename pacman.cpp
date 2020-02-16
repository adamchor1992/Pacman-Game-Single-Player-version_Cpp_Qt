#include "game_map.h"
#include "pacman.h"
#include <QGraphicsPixmapItem>
#include <QPainter>

int Pacman::m_PacX{};
int Pacman::m_PacY{};

Pacman::Pacman()
{
    LoadPacmanImages();

    m_AnimeState = 0;
    m_AnimationModifyFactor = 6;

    SetDirection(Direction::left);
    SetNextDirection(Direction::none);
    SetPacX(startingX);
    SetPacY(startingY);
}

void Pacman::Reset()
{
    m_AnimeState = 0;
    m_AnimationModifyFactor = 6;

    SetDirection(Direction::left);
    SetNextDirection(Direction::none);
    SetPacX(startingX);
    SetPacY(startingY);
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

void Pacman::SetDirection(Direction direction)
{
    m_Direction=direction;
}

void Pacman::SetNextDirection(Direction direction)
{
    m_NextDirection=direction;
}

void Pacman::Move()
{
    /*Path point which is tested for validity*/
    QPoint point;

    if(m_NextDirection!=m_Direction)
    {
        switch(m_NextDirection)
        {
        case Direction::left:
            point.setX(m_PacX-1);
            point.setY(m_PacY);

            if(GameMap::IsPointAvailable(point))
            {
                m_Direction=m_NextDirection;
                m_NextDirection=Direction::none;
            }
            break;

        case Direction::up:
            point.setX(m_PacX);
            point.setY(m_PacY-1);
            if(GameMap::IsPointAvailable(point))
            {
                m_Direction=m_NextDirection;
                m_NextDirection=Direction::none;
            }
            break;

        case Direction::down:
            point.setX(m_PacX);
            point.setY(m_PacY+1);
            if(GameMap::IsPointAvailable(point))
            {
                m_Direction=m_NextDirection;
                m_NextDirection=Direction::none;
            }
            break;

        case Direction::right:
            point.setX(m_PacX+1);
            point.setY(m_PacY);
            if(GameMap::IsPointAvailable(point))
            {
                m_Direction=m_NextDirection;
                m_NextDirection=Direction::none;
            }
            break;

        case Direction::none:
            break;
        }
    }

    switch(m_Direction)
    {
    case Direction::left:
        point.setX(m_PacX-1);
        point.setY(m_PacY);

        if(GameMap::IsPointAvailable(point))
        {
            m_PacX = m_PacX - 1;
        }
        break;

    case Direction::up:
        point.setX(m_PacX);
        point.setY(m_PacY-1);

        if(GameMap::IsPointAvailable(point))
        {
            m_PacY= m_PacY - 1;
        }
        break;

    case Direction::down:
        point.setX(m_PacX);
        point.setY(m_PacY+1);

        if(GameMap::IsPointAvailable(point))
        {
            m_PacY= m_PacY + 1;
        }
        break;

    case Direction::right:
        point.setX(m_PacX+1);
        point.setY(m_PacY);

        if(GameMap::IsPointAvailable(point))
        {
            m_PacX = m_PacX + 1;
        }
        break;

    case Direction::none:
        break;
    }

    /*Teleportation when reached left boundary of middle horizontal line*/
    if(m_PacX<=0)
    {
        m_PacX=613;
    }

    /*Teleportation when reached right boundary of middle horizontal line*/
    if(m_PacX>=614)
    {
        m_PacX=1;
    }
}

QRectF Pacman::boundingRect() const
{
    int const pacmanRadius=30;
    int const offsetX=-15;
    int const offsetY=-15;

    return QRect(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius);
}

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int const pacmanRadius=30;
    int const offsetX=-15;
    int const offsetY=-15;

    switch(m_Direction)
    {
    case Direction::left:
        if(m_AnimeState<2*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Left1);
        }
        else if(m_AnimeState<4*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Left2);
        }
        else if(m_AnimeState<6*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Left3);
        }
        else if(m_AnimeState<8*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Left4);
        }
        break;

    case Direction::right:
        if(m_AnimeState<2*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Right1);
        }
        else if(m_AnimeState<4*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Right2);
        }
        else if(m_AnimeState<6*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Right3);
        }
        else if(m_AnimeState<8*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Right4);
        }
        break;

    case Direction::down:
        if(m_AnimeState<2*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Down1);
        }
        else if(m_AnimeState<4*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Down2);
        }
        else if(m_AnimeState<6*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Down3);
        }
        else if(m_AnimeState<8*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Down4);
        }
        break;

    case Direction::up:
        if(m_AnimeState<2*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Up1);
        }
        else if(m_AnimeState<4*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Up2);
        }
        else if(m_AnimeState<6*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Up3);
        }
        else if(m_AnimeState<8*m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_PacX+offsetX, m_PacY+offsetY, pacmanRadius, pacmanRadius, m_Up4);
        }
        break;

    case Direction::none:
        break;
    }
}
