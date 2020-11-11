#include "ghost.h"
#include "game_map.h"
#include "pacman.h"

bool Ghost::m_AllGhostsStartedFreeMovement = false;
int Ghost::m_GhostsStartTimer = 0;
int Ghost::m_AllGhostsScaredState = 0;
int Ghost::m_GhostNumber = 0;

Ghost::Ghost()
{
    m_AllGhostsScaredState = 0;
    m_GhostsStartTimer = 0;
    m_AllGhostsStartedFreeMovement = false;

    m_AnimationState = 0;
    m_AnimationModifyFactor = 6;
    m_Direction = Direction::LEFT;
    m_NextDirection = Direction::NONE;
    m_ScaredState = ScaredState::NO_SCARED;
    m_GhostMoving = false;
    m_GhostStartedFreeMovement = false;
    m_X = STARTING_X;
    m_Y = STARTING_Y;

    LoadImages();

    /*Each ghost has an unique color*/
    switch(m_GhostNumber)
    {
    case 0:
        SetColor("orange");
        break;
    case 1:
        SetColor("red");
        break;
    case 2:
        SetColor("blue");
        break;
    }

    ++m_GhostNumber;
}

void Ghost::Reset()
{
    m_AllGhostsScaredState = 0;
    m_GhostsStartTimer = 0;
    m_AllGhostsStartedFreeMovement = false;

    m_AnimationState = 0;
    m_AnimationModifyFactor = 6;
    m_Direction = Direction::LEFT;
    m_ScaredState = ScaredState::NO_SCARED;
    m_GhostMoving = false;
    m_GhostStartedFreeMovement = false;
    m_NextDirection = Direction::NONE;
    m_X = STARTING_X;
    m_Y = STARTING_Y;
}

void Ghost::LoadImages()
{
    m_Right1Pixmap.load(":/ghosts/images/ghost_images/ghostright1.png");
    m_Right2Pixmap.load(":/ghosts/images/ghost_images/ghostright2.png");
    m_Up1Pixmap.load(":/ghosts/images/ghost_images/ghostup1.png");
    m_Up2Pixmap.load(":/ghosts/images/ghost_images/ghostup2.png");
    m_Down1Pixmap.load(":/ghosts/images/ghost_images/ghostdown1.png");
    m_Down2Pixmap.load(":/ghosts/images/ghost_images/ghostdown2.png");
    m_Left1Pixmap.load(":/ghosts/images/ghost_images/ghostleft1.png");
    m_Left2Pixmap.load(":/ghosts/images/ghost_images/ghostleft2.png");
    m_ScaredBlue1Pixmap.load(":/ghosts/images/ghost_images/ghostscaredblue1.png");
    m_ScaredBlue2Pixmap.load(":/ghosts/images/ghost_images/ghostscaredblue2.png");
    m_ScaredWhite1Pixmap.load(":/ghosts/images/ghost_images/ghostscaredwhite1.png");
    m_ScaredWhite2Pixmap.load(":/ghosts/images/ghost_images/ghostscaredwhite2.png");
}

void Ghost::AdvanceAnimation()
{
    if(m_AnimationState > 2)
    {
        m_AnimationState = 0;
    }
    else
    {
        m_AnimationState++;
    }
}

void Ghost::Respawn()
{
    m_X = STARTING_X;
    m_Y = 252;
    m_ScaredState = ScaredState::NO_SCARED;
}

void Ghost::SetColor(const QString& col)
{
    if(col == "blue")
    {
        m_Right1Pixmap.load(":/ghosts/images/ghost_images/ghostrightblue1.png");
        m_Right2Pixmap.load(":/ghosts/images/ghost_images/ghostrightblue2.png");
        m_Up1Pixmap.load(":/ghosts/images/ghost_images/ghostupblue1.png");
        m_Up2Pixmap.load(":/ghosts/images/ghost_images/ghostupblue2.png");
        m_Down1Pixmap.load(":/ghosts/images/ghost_images/ghostdownblue1.png");
        m_Down2Pixmap.load(":/ghosts/images/ghost_images/ghostdownblue2.png");
        m_Left1Pixmap.load(":/ghosts/images/ghost_images/ghostleftblue1.png");
        m_Left2Pixmap.load(":/ghosts/images/ghost_images/ghostleftblue2.png");
    }
    else if(col == "orange")
    {
        m_Right1Pixmap.load(":/ghosts/images/ghost_images/ghostrightorange1.png");
        m_Right2Pixmap.load(":/ghosts/images/ghost_images/ghostrightorange2.png");
        m_Up1Pixmap.load(":/ghosts/images/ghost_images/ghostuporange1.png");
        m_Up2Pixmap.load(":/ghosts/images/ghost_images/ghostuporange2.png");
        m_Down1Pixmap.load(":/ghosts/images/ghost_images/ghostdownorange1.png");
        m_Down2Pixmap.load(":/ghosts/images/ghost_images/ghostdownorange2.png");
        m_Left1Pixmap.load(":/ghosts/images/ghost_images/ghostleftorange1.png");
        m_Left2Pixmap.load(":/ghosts/images/ghost_images/ghostleftorange2.png");
    }
    else if(col == "red")
    {
        m_Right1Pixmap.load(":/ghosts/images/ghost_images/ghostrightred1.png");
        m_Right2Pixmap.load(":/ghosts/images/ghost_images/ghostrightred2.png");
        m_Up1Pixmap.load(":/ghosts/images/ghost_images/ghostupred1.png");
        m_Up2Pixmap.load(":/ghosts/images/ghost_images/ghostupred2.png");
        m_Down1Pixmap.load(":/ghosts/images/ghost_images/ghostdownred1.png");
        m_Down2Pixmap.load(":/ghosts/images/ghost_images/ghostdownred2.png");
        m_Left1Pixmap.load(":/ghosts/images/ghost_images/ghostleftred1.png");
        m_Left2Pixmap.load(":/ghosts/images/ghost_images/ghostleftred2.png");
    }
}

void Ghost::Move()
{
    QPoint point;

    int pacmanX = Pacman::GetX();
    int pacmanY = Pacman::GetY();

    if(!m_GhostMoving)
    {
        m_Direction = static_cast<Direction>((qrand() % 4) + 1);
    }
    else
    {
        if((m_Direction == Direction::RIGHT && m_Y < pacmanY) || (m_Direction == Direction::LEFT && m_Y > pacmanY))
        {
            if(m_Direction == Direction::LEFT && m_Y > pacmanY)
            {
                m_NextDirection = Direction::UP;
            }
            else if(m_Direction == Direction::RIGHT && m_Y < pacmanY)
            {
                m_NextDirection = Direction::DOWN;
            }
        }
        else if((m_Direction == Direction::DOWN && m_X < pacmanX) || (m_Direction == Direction::UP && m_X > pacmanX))
        {
            if(m_Direction == Direction::UP && m_X > pacmanX)
            {
                m_NextDirection = Direction::LEFT;
            }
            else if(m_Direction == Direction::DOWN && m_X < pacmanX)
            {
                m_NextDirection=Direction::RIGHT;
            }
        }
    }

    if(m_NextDirection != m_Direction)
    {
        switch(m_NextDirection)
        {
        case Direction::LEFT:
            point.setX(m_X - 1);
            point.setY(m_Y);

            if(GameMap::IsPointAvailable(point))
            {
                m_Direction=m_NextDirection;
                m_NextDirection = Direction::NONE;
            }
            break;

        case Direction::RIGHT:
            point.setX(m_X + 1);
            point.setY(m_Y);

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

        case Direction::UP:
            point.setX(m_X);
            point.setY(m_Y - 1);

            if(GameMap::IsPointAvailable(point))
            {
                m_Direction = m_NextDirection;
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
            m_X -= 1;
            m_GhostMoving = true;
        }
        else
        {
            m_GhostMoving = false;
        }
        break;

    case Direction::RIGHT:
        point.setX(m_X + 1);
        point.setY(m_Y);

        if(GameMap::IsPointAvailable(point))
        {
            m_X += 1;
            m_GhostMoving = true;
        }
        else
        {
            m_GhostMoving = false;
        }
        break;

    case Direction::DOWN:
        point.setX(m_X);
        point.setY(m_Y + 1);

        if(GameMap::IsPointAvailable(point))
        {
            m_Y += 1;
            m_GhostMoving = true;
        }
        else
        {
            m_GhostMoving = false;
        }
        break;

    case Direction::UP:
        point.setX(m_X);
        point.setY(m_Y - 1);

        if(GameMap::IsPointAvailable(point))
        {
            m_Y -= 1;
            m_GhostMoving = true;
        }
        else
        {
            m_GhostMoving = false;
        }
        break;

    case Direction::NONE:
        break;
    }

    /*Teleportation when reached left boundary of middle horizontal line*/
    if(m_X <= 0)
    {
        m_X = 613;
        m_Y = 318;
    }
    /*Teleportation when reached right boundary of middle horizontal line*/
    else if(m_X >= 614)
    {
        m_X = 1;
        m_Y = 318;
    }
}

void Ghost::MoveInStartingRect()
{
    int const horizontalMovementOffset = 50;

    if(m_X == STARTING_X - horizontalMovementOffset || m_X == STARTING_X + horizontalMovementOffset)
    {
        if(m_Direction == Direction::RIGHT)
        {
            /*Go left*/
            m_Direction = Direction::LEFT;
        }
        else
        {
            /*Go right*/
            m_Direction = Direction::RIGHT;
        }
    }

    if(m_Direction == Direction::RIGHT)
    {
        m_X += 1;
    }
    else
    {
        m_X -= 1;
    }
}

void Ghost::MoveOutOfTheStartingBox(int ghostX, int ghostY)
{
    if(ghostX > Ghost::STARTING_X)
    {
        ghostX -= 1;
    }
    else if(ghostX < Ghost::STARTING_X)
    {
        ghostX += 1;
    }

    if(!GetGhostStartedFreeMovement())
    {
        ghostY -= 1;

        m_X = ghostX;
        m_Y = ghostY;

        QPoint point(ghostX, ghostY);

        if(GameMap::GetPathPoints().contains(point))
        {
            m_GhostStartedFreeMovement = true;
        }
    }
}

QRectF Ghost::boundingRect() const
{
    const int DIAMETER = 30;
    const int OFFSET_X = -15;
    const int OFFSET_Y = -15;

    return QRect(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER);
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    const int  DIAMETER = 30;
    const int OFFSET_X = -15;
    const int OFFSET_Y= -15;

    if(m_ScaredState == ScaredState::NO_SCARED)
    {
        switch(m_Direction)
        {
        case Direction::LEFT:
            if(m_AnimationState == 0)
            {
                painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_Left1Pixmap);
            }
            else
            {
                painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_Left2Pixmap);
            }
            break;

        case Direction::RIGHT:
            if(m_AnimationState == 0)
            {
                painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_Right1Pixmap);
            }
            else
            {
                painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_Right2Pixmap);
            }
            break;

        case Direction::DOWN:
            if(m_AnimationState == 0)
            {
                painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_Down1Pixmap);
            }
            else
            {
                painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_Down2Pixmap);
            }
            break;

        case Direction::UP:
            if(m_AnimationState == 0)
            {
                painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_Up1Pixmap);
            }
            else
            {
                painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_Up2Pixmap);
            }
            break;

        case Direction::NONE:
            break;
        }
    }
    else if(m_ScaredState == ScaredState::SCARED_BLUE)
    {
        if(m_AnimationState == 0)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_ScaredBlue1Pixmap);
        }
        else
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_ScaredBlue2Pixmap);
        }
    }
    else if(m_ScaredState == ScaredState::SCARED_WHITE)
    {
        if(m_AnimationState == 0)
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_ScaredWhite1Pixmap);
        }
        else
        {
            painter->drawPixmap(m_X + OFFSET_X, m_Y + OFFSET_Y, DIAMETER, DIAMETER, m_ScaredWhite2Pixmap);
        }
    }
    else
    {
        assert(false);
    }
}
