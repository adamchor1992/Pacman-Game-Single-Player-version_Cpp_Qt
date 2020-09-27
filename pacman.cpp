#include "game_map.h"
#include "pacman.h"
#include <QGraphicsPixmapItem>
#include <QPainter>

int Pacman::m_X = STARTING_X;
int Pacman::m_Y = STARTING_Y;

Pacman::Pacman()
{
    LoadImages();

    m_AnimationState = 0;
    m_AnimationModifyFactor = 6;

    m_Direction = Direction::LEFT;
    m_NextDirection = Direction::NONE;
    m_X = STARTING_X;
    m_Y = STARTING_Y;
}

void Pacman::Reset()
{
    m_AnimationState = 0;
    m_AnimationModifyFactor = 6;

    m_Direction = Direction::LEFT;
    m_NextDirection = Direction::NONE;
    m_X = STARTING_X;
    m_Y = STARTING_Y;
}

void Pacman::AdvanceAnimation()
{
    if(m_AnimationState > 8 * m_AnimationModifyFactor - 2)
    {
        m_AnimationState = 0;
    }
    else
    {
        m_AnimationState++;
    }
}

void Pacman::LoadImages()
{
    m_Right1Pixmap.load(":/pacman/images/pacman_images/pacclose.png");
    m_Right2Pixmap.load(":/pacman/images/pacman_images/pacopen1.png");
    m_Right3Pixmap.load(":/pacman/images/pacman_images/pacopen2.png");
    m_Right4Pixmap.load(":/pacman/images/pacman_images/pacopen3.png");

    m_Up1Pixmap.load(":/pacman/images/pacman_images/paccloseu.png");
    m_Up2Pixmap.load(":/pacman/images/pacman_images/pacopen1u.png");
    m_Up3Pixmap.load(":/pacman/images/pacman_images/pacopen2u.png");
    m_Up4Pixmap.load(":/pacman/images/pacman_images/pacopen3u.png");

    m_Down1Pixmap.load(":/pacman/images/pacman_images/pacclosed.png");
    m_Down2Pixmap.load(":/pacman/images/pacman_images/pacopen1d.png");
    m_Down3Pixmap.load(":/pacman/images/pacman_images/pacopen2d.png");
    m_Down4Pixmap.load(":/pacman/images/pacman_images/pacopen3d.png");

    m_Left1Pixmap.load(":/pacman/images/pacman_images/pacclosel.png");
    m_Left2Pixmap.load(":/pacman/images/pacman_images/pacopen1l.png");
    m_Left3Pixmap.load(":/pacman/images/pacman_images/pacopen2l.png");
    m_Left4Pixmap.load(":/pacman/images/pacman_images/pacopen3l.png");
}

void Pacman::SetNextDirection(Direction direction)
{
    m_NextDirection=direction;
}

void Pacman::Move()
{
    /*Path point which is tested for validity*/
    QPoint point;

    if(m_NextDirection != m_Direction)
    {
        switch(m_NextDirection)
        {
        case Direction::LEFT:
            point.setX(m_X - 1);
            point.setY(m_Y);

            if(GameMap::IsPointAvailable(point))
            {
                m_Direction = m_NextDirection;
                m_NextDirection = Direction::NONE;
            }
            break;

        case Direction::UP:
            point.setX(m_X);
            point.setY(m_Y - 1);
            if(GameMap::IsPointAvailable(point))
            {
                m_Direction = m_NextDirection;
                m_NextDirection = Direction::NONE;
            }
            break;

        case Direction::DOWN:
            point.setX(m_X);
            point.setY(m_Y + 1);
            if(GameMap::IsPointAvailable(point))
            {
                m_Direction = m_NextDirection;
                m_NextDirection = Direction::NONE;
            }
            break;

        case Direction::RIGHT:
            point.setX(m_X + 1);
            point.setY(m_Y);
            if(GameMap::IsPointAvailable(point))
            {
                m_Direction=m_NextDirection;
                m_NextDirection = Direction::NONE;
            }
            break;

        case Direction::NONE:
            break;
        }
    }

    switch(m_Direction)
    {
    case Direction::LEFT:
        point.setX(m_X - 1);
        point.setY(m_Y);

        if(GameMap::IsPointAvailable(point))
        {
            m_X = m_X - 1;
        }
        break;

    case Direction::UP:
        point.setX(m_X);
        point.setY(m_Y - 1);

        if(GameMap::IsPointAvailable(point))
        {
            m_Y= m_Y - 1;
        }
        break;

    case Direction::DOWN:
        point.setX(m_X);
        point.setY(m_Y + 1);

        if(GameMap::IsPointAvailable(point))
        {
            m_Y= m_Y + 1;
        }
        break;

    case Direction::RIGHT:
        point.setX(m_X + 1);
        point.setY(m_Y);

        if(GameMap::IsPointAvailable(point))
        {
            m_X = m_X + 1;
        }
        break;

    case Direction::NONE:
        break;
    }

    /*Teleportation when reached left boundary of middle horizontal line*/
    if(m_X <= 0)
    {
        m_X = 613;
    }

    /*Teleportation when reached right boundary of middle horizontal line*/
    if(m_X >= 614)
    {
        m_X = 1;
    }
}

QRectF Pacman::boundingRect() const
{
    const int DIAMETER = 30;
    const int OFFSET_X = -15;
    const int OFFSET_Y = -15;

    return QRect(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER);
}

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    const int DIAMETER = 30;
    const int OFFSET_X = -15;
    const int OFFSET_Y = -15;

    switch(m_Direction)
    {
    case Direction::LEFT:
        if(m_AnimationState < 2 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Left1Pixmap);
        }
        else if(m_AnimationState < 4 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Left2Pixmap);
        }
        else if(m_AnimationState < 6 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Left3Pixmap);
        }
        else if(m_AnimationState < 8 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Left4Pixmap);
        }
        break;

    case Direction::RIGHT:
        if(m_AnimationState < 2 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Right1Pixmap);
        }
        else if(m_AnimationState < 4 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Right2Pixmap);
        }
        else if(m_AnimationState < 6 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Right3Pixmap);
        }
        else if(m_AnimationState < 8 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Right4Pixmap);
        }
        break;

    case Direction::DOWN:
        if(m_AnimationState < 2 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Down1Pixmap);
        }
        else if(m_AnimationState < 4 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Down2Pixmap);
        }
        else if(m_AnimationState < 6 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Down3Pixmap);
        }
        else if(m_AnimationState < 8 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Down4Pixmap);
        }
        break;

    case Direction::UP:
        if(m_AnimationState < 2 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Up1Pixmap);
        }
        else if(m_AnimationState < 4 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Up2Pixmap);
        }
        else if(m_AnimationState < 6 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Up3Pixmap);
        }
        else if(m_AnimationState < 8 * m_AnimationModifyFactor)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER , DIAMETER , m_Up4Pixmap);
        }
        break;

    case Direction::NONE:
        break;
    }
}
