#include "ghost.h"

Ghost::Ghost()
{
    m_AnimeState= 0;
    m_AnimationModifyFactor= 6;

    m_GhostDirection=1;
    m_IsScared=false;
    m_ScaredWhite=false;

    LoadGhostImages();
}

QRectF Ghost::boundingRect() const
{
    return QRect(m_GhostX-15, m_GhostY-15, 20, 20);
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!m_IsScared)
    {
        switch(m_GhostDirection)
        {
            case 1:
                if(m_AnimeState==0)
                {
                    painter->drawPixmap(m_GhostX-15, m_GhostY-15,30,30, m_Left1);
                }
                else
                {
                    painter->drawPixmap(m_GhostX-15, m_GhostY-15, 30, 30, m_Left2);
                }
                break;
            case 4:
                if(m_AnimeState==0)
                {
                    painter->drawPixmap(m_GhostX-15, m_GhostY-15, 30, 30, m_Right1);
                }
                else
                {
                    painter->drawPixmap(m_GhostX-15, m_GhostY-15, 30, 30, m_Right2);
                }
                break;
            case 3:
                if(m_AnimeState==0)
                {
                    painter->drawPixmap(m_GhostX-15, m_GhostY-15, 30, 30, m_Down1);
                }
                else
                {
                    painter->drawPixmap(m_GhostX-15, m_GhostY-15, 30, 30, m_Down2);
                }
                break;
            case 2:
                if(m_AnimeState==0)
                {
                    painter->drawPixmap(m_GhostX-15, m_GhostY-15, 30, 30, m_Up1);
                }
                else
                {
                    painter->drawPixmap(m_GhostX-15, m_GhostY-15, 30, 30, m_Up2);
                }
                break;
        }
    }
    else
    {
        if(m_ScaredWhite)
        {
            if(m_AnimeState==0)
            {
                painter->drawPixmap(m_GhostX-15, m_GhostY-15, 30, 30, m_ScaredWhitePix);
            }
            else
            {
                painter->drawPixmap(m_GhostX-15, m_GhostY-15, 30, 30, m_ScaredWhite1);
            }
        }
        else
        {
            if(m_AnimeState==0)
            {
                painter->drawPixmap(m_GhostX-15, m_GhostY-15, 30, 30, m_ScaredBlue);
            }
            else
            {
                painter->drawPixmap(m_GhostX-15, m_GhostY-15, 30, 30, m_ScaredBlue1);
            }
        }
    }
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

void Ghost::Advance()
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

void Ghost::SetGhostX(int x)
{
    m_GhostX=x;
}

void Ghost::SetGhostY(int y)
{
    m_GhostY=y;
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
