#include "ghost.h"
#include "game_map.h"
#include "pacman.h"

bool Ghost::m_AllGhostScared = false;
bool Ghost::m_AllGhostsStartedFreeMovement = false;
int Ghost::m_GhostsStartTimer = 0;
int Ghost::m_AllGhostsScaredState = 0;

Ghost::Ghost()
{
    m_AnimeState= 0;
    m_AnimationModifyFactor= 6;
    m_GhostDirection=Direction::left;
    m_IsScared=false;
    m_ScaredWhite=false;
    m_GhostMoving = false;
    m_GhostStartedFreeMovement = false;
    m_AllGhostsScaredState=0;
    m_AllGhostScared=false;
    m_GhostsStartTimer = 0;
    m_AllGhostsStartedFreeMovement=false;

    SetGhostX(STARTING_X);
    SetGhostY(STARTING_Y);
    SetGhostX(STARTING_X);
    SetGhostY(STARTING_Y);
    SetGhostX(STARTING_X);
    SetGhostY(STARTING_Y);
    SetGhostX(STARTING_X);
    SetGhostY(STARTING_Y);

    LoadGhostImages();
}

void Ghost::Reset()
{
    m_AnimeState= 0;
    m_AnimationModifyFactor= 6;
    m_GhostDirection=Direction::left;
    m_IsScared=false;
    m_ScaredWhite=false;
    m_GhostMoving = false;
    m_GhostStartedFreeMovement = false;
    m_AllGhostsScaredState=0;
    m_AllGhostScared=false;
    m_GhostsStartTimer = 0;
    m_AllGhostsStartedFreeMovement=false;

    SetGhostX(STARTING_X);
    SetGhostY(STARTING_Y);
    SetGhostX(STARTING_X);
    SetGhostY(STARTING_Y);
    SetGhostX(STARTING_X);
    SetGhostY(STARTING_Y);
    SetGhostX(STARTING_X);
    SetGhostY(STARTING_Y);
}

void Ghost::LoadGhostImages()
{
    m_Right1.load(":/ghosts/images/ghost_images/ghostright1.png");
    m_Right2.load(":/ghosts/images/ghost_images/ghostright2.png");
    m_Up1.load(":/ghosts/images/ghost_images/ghostup1.png");
    m_Up2.load(":/ghosts/images/ghost_images/ghostup2.png");
    m_Down1.load(":/ghosts/images/ghost_images/ghostdown1.png");
    m_Down2.load(":/ghosts/images/ghost_images/ghostdown2.png");
    m_Left1.load(":/ghosts/images/ghost_images/ghostleft1.png");
    m_Left2.load(":/ghosts/images/ghost_images/ghostleft2.png");
    m_ScaredBlue.load(":/ghosts/images/ghost_images/ghostscaredblue1.png");
    m_ScaredBlue1.load(":/ghosts/images/ghost_images/ghostscaredblue2.png");
    m_ScaredWhitePix.load(":/ghosts/images/ghost_images/ghostscaredwhite1.png");
    m_ScaredWhite1.load(":/ghosts/images/ghost_images/ghostscaredwhite2.png");
}

void Ghost::AdvanceAnimation()
{
    if(m_AnimeState>2)
    {
        m_AnimeState=0;
    }
    else
    {
        m_AnimeState++;
    }
}

void Ghost::Respawn()
{
    SetGhostX(Ghost::STARTING_X);
    SetGhostY(252);
    SetIsScared(false);
}

void Ghost::SetGhostColor(QString col)
{
    if(col=="blue")
    {
        m_Right1.load(":/ghosts/images/ghost_images/ghostrightblue1.png");
        m_Right2.load(":/ghosts/images/ghost_images/ghostrightblue2.png");
        m_Up1.load(":/ghosts/images/ghost_images/ghostupblue1.png");
        m_Up2.load(":/ghosts/images/ghost_images/ghostupblue2.png");
        m_Down1.load(":/ghosts/images/ghost_images/ghostdownblue1.png");
        m_Down2.load(":/ghosts/images/ghost_images/ghostdownblue2.png");
        m_Left1.load(":/ghosts/images/ghost_images/ghostleftblue1.png");
        m_Left2.load(":/ghosts/images/ghost_images/ghostleftblue2.png");
    }
    else if(col=="orange")
    {
        m_Right1.load(":/ghosts/images/ghost_images/ghostrightorange1.png");
        m_Right2.load(":/ghosts/images/ghost_images/ghostrightorange2.png");
        m_Up1.load(":/ghosts/images/ghost_images/ghostuporange1.png");
        m_Up2.load(":/ghosts/images/ghost_images/ghostuporange2.png");
        m_Down1.load(":/ghosts/images/ghost_images/ghostdownorange1.png");
        m_Down2.load(":/ghosts/images/ghost_images/ghostdownorange2.png");
        m_Left1.load(":/ghosts/images/ghost_images/ghostleftorange1.png");
        m_Left2.load(":/ghosts/images/ghost_images/ghostleftorange2.png");
    }
    else if(col=="red")
    {
        m_Right1.load(":/ghosts/images/ghost_images/ghostrightred1.png");
        m_Right2.load(":/ghosts/images/ghost_images/ghostrightred2.png");
        m_Up1.load(":/ghosts/images/ghost_images/ghostupred1.png");
        m_Up2.load(":/ghosts/images/ghost_images/ghostupred2.png");
        m_Down1.load(":/ghosts/images/ghost_images/ghostdownred1.png");
        m_Down2.load(":/ghosts/images/ghost_images/ghostdownred2.png");
        m_Left1.load(":/ghosts/images/ghost_images/ghostleftred1.png");
        m_Left2.load(":/ghosts/images/ghost_images/ghostleftred2.png");
    }
}

void Ghost::Move()
{
    QPoint p;

    int pac_x = Pacman::GetPacX();
    int pac_y = Pacman::GetPacY();

    if(!m_GhostMoving)
    {
        m_GhostDirection=static_cast<Direction>((qrand()%4)+1);
    }
    else
    {
        if((m_GhostDirection==Direction::right && m_GhostY<pac_y) || (m_GhostDirection==Direction::left && m_GhostY>pac_y))
        {
            if(m_GhostDirection==Direction::left && m_GhostY>pac_y)
            {
                m_NextGhostDirection=Direction::up;
            }
            else if(m_GhostDirection==Direction::right &&m_GhostY<pac_y)
            {
                m_NextGhostDirection=Direction::down;
            }
        }
        else if((m_GhostDirection==Direction::down && m_GhostX<pac_x) || (m_GhostDirection==Direction::up && m_GhostX>pac_x))
        {
            if(m_GhostDirection==Direction::up && m_GhostX>pac_x)
            {
                m_NextGhostDirection=Direction::left;
            }
            else if(m_GhostDirection==Direction::down && m_GhostX<pac_x)
            {
                m_NextGhostDirection=Direction::right;
            }
        }
    }

    if(m_NextGhostDirection!=m_GhostDirection)
    {
        switch(m_NextGhostDirection)
        {
        case Direction::left:
            p.setX(m_GhostX-1);
            p.setY(m_GhostY);

            if(GameMap::IsPointAvailable(p))
            {
                m_GhostDirection=m_NextGhostDirection;
                m_NextGhostDirection=Direction::none;
            }
            break;

        case Direction::right:
            p.setX(m_GhostX+1);
            p.setY(m_GhostY);

            if(GameMap::IsPointAvailable(p))
            {
                m_GhostDirection=m_NextGhostDirection;
                m_NextGhostDirection=Direction::none;
            }
            break;

        case Direction::down:
            p.setX(m_GhostX);
            p.setY(m_GhostY+1);
            if(GameMap::IsPointAvailable(p))
            {
                m_GhostDirection=m_NextGhostDirection;
                m_NextGhostDirection=Direction::none;
            }
            break;

        case Direction::up:
            p.setX(m_GhostX);
            p.setY(m_GhostY-1);

            if(GameMap::IsPointAvailable(p))
            {
                m_GhostDirection=m_NextGhostDirection;
                m_NextGhostDirection=Direction::none;
            }
            break;

        case Direction::none:
            break;
        }
    }

    switch(m_GhostDirection)
    {
    case Direction::left:
        p.setX(m_GhostX-1);
        p.setY(m_GhostY);
        SetGhostDirection(m_GhostDirection);

        if(GameMap::IsPointAvailable(p))
        {
            m_GhostX-=1;
            m_GhostMoving=true;
        }
        else
        {
            m_GhostMoving=false;
        }
        break;

    case Direction::right:
        SetGhostDirection(m_GhostDirection);
        p.setX(m_GhostX+1);
        p.setY(m_GhostY);
        if(GameMap::IsPointAvailable(p))
        {
            m_GhostX+=1;
            m_GhostMoving=true;
        }
        else
        {
            m_GhostMoving=false;
        }
        break;

    case Direction::down:
        SetGhostDirection(m_GhostDirection);
        p.setX(m_GhostX);
        p.setY(m_GhostY+1);
        if(GameMap::IsPointAvailable(p))
        {
            m_GhostY+=1;
            m_GhostMoving=true;
        }
        else
        {
            m_GhostMoving=false;
        }
        break;

    case Direction::up:
        SetGhostDirection(m_GhostDirection);
        p.setX(m_GhostX);
        p.setY(m_GhostY-1);
        if(GameMap::IsPointAvailable(p))
        {
            m_GhostY-=1;
            m_GhostMoving=true;
        }
        else
        {
            m_GhostMoving=false;
        }
        break;

    case Direction::none:
        break;
    }

    /*Teleportation when reached left boundary of middle horizontal line*/
    if(m_GhostX<=0)
    {
        m_GhostX=613;
        m_GhostY=318;
    }
    /*Teleportation when reached right boundary of middle horizontal line*/
    else if(m_GhostX>=614)
    {
        m_GhostX=1;
        m_GhostY=318;
    }

    SetGhostX(m_GhostX);
    SetGhostY(m_GhostY);
    SetNextGhostDirection(m_NextGhostDirection);
}

void Ghost::MoveInStartingRect()
{
    int const horizontalMovementOffset = 50;

    if(m_GhostX == STARTING_X - horizontalMovementOffset || m_GhostX == STARTING_X + horizontalMovementOffset)
    {
        if(m_GhostDirection==Direction::right)
        {
            /*Go left*/
            m_GhostDirection=Direction::left;
        }
        else
        {
            /*Go right*/
            m_GhostDirection=Direction::right;
        }
    }

    if(m_GhostDirection==Direction::right)
    {
        m_GhostX+=1;
    }
    else
    {
        m_GhostX-=1;
    }
}

QRectF Ghost::boundingRect() const
{
    int const ghostRadius=30;
    int const offsetX=-15;
    int const offsetY=-15;

    return QRect(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius);
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int const ghostRadius=30;
    int const offsetX=-15;
    int const offsetY=-15;

    if(!m_IsScared)
    {
        switch(m_GhostDirection)
        {
        case Direction::left:
            if(m_AnimeState==0)
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY,ghostRadius, ghostRadius, m_Left1);
            }
            else
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius, m_Left2);
            }
            break;

        case Direction::right:
            if(m_AnimeState==0)
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius, m_Right1);
            }
            else
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius, m_Right2);
            }
            break;

        case Direction::down:
            if(m_AnimeState==0)
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius, m_Down1);
            }
            else
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius, m_Down2);
            }
            break;

        case Direction::up:
            if(m_AnimeState==0)
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius, m_Up1);
            }
            else
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius, m_Up2);
            }
            break;

        case Direction::none:
            break;
        }
    }
    else
    {
        if(m_ScaredWhite)
        {
            if(m_AnimeState==0)
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius, m_ScaredWhitePix);
            }
            else
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius, m_ScaredWhite1);
            }
        }
        else
        {
            if(m_AnimeState==0)
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius, m_ScaredBlue);
            }
            else
            {
                painter->drawPixmap(m_GhostX+offsetX, m_GhostY+offsetY, ghostRadius, ghostRadius, m_ScaredBlue1);
            }
        }
    }
}
