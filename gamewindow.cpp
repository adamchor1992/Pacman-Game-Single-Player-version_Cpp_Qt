#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "map.h"
#include "powerball.h"
#include <QGraphicsScene>

GameWindow::GameWindow(QWidget *parent) : QDialog(parent), m_pUi(new Ui::GameWindow)
{
    m_pUi->setupUi(this);

    InitializeGameplayAreaScene();

    GenerateAndPopulateMap();
    GenerateAndPlacePacman();
    GenerateAndPlaceGhosts();

    ShowScore();

    m_CollisionDetectionDelay = 0; //delay collision detection after game restart

    m_Scene.addItem(&m_TextStartEnd);

    m_Start=false;
    m_Playing = false;
    m_ReadyToRestart = false;

    this->setFocus(Qt::ActiveWindowFocusReason);
}

void GameWindow::InitializeGameplayAreaScene()
{
    m_Scene.setParent(this);
    m_pUi->m_pGameplayArea->setScene(&m_Scene);
    m_pUi->m_pGameplayArea->setRenderHint(QPainter::Antialiasing);
    m_Scene.setSceneRect(0,0,614,740);
    m_pUi->m_pGameplayArea->setSceneRect(m_Scene.sceneRect());
}

void GameWindow::GenerateAndPopulateMap()
{
    m_PowerballPositions = m_Powerball.GetPowerBallPositions();
    m_FoodballPositions = m_Foodball.GetFoodBallPositions();

    m_pMapItem = m_Scene.addPixmap(m_PacMap.GetMapBackgroundPicture());

    for(int i=0; i<m_PowerballPositions.size();i++)
    {
        m_PowerballGraphicalItemsTable.push_back(m_Scene.addEllipse(m_PowerballPositions.at(i).x()-5, m_PowerballPositions.at(i).y()-8, 15, 15, QPen(Qt::NoPen), QBrush(Qt::white)));
    }

    m_FoodballItemsCount=m_FoodballPositions.size();

    for(int i=0;i<m_FoodballPositions.size();i++)
    {
        m_FoodballGraphicalItemsTable.push_back(m_Scene.addEllipse(m_FoodballPositions.at(i).x(),m_FoodballPositions.at(i).y(),7,7,QPen(Qt::NoPen),QBrush(Qt::white)));
    }
}

void GameWindow::GenerateAndPlacePacman()
{
    m_Pacman.SetDirection(1); //pacman moves left after game m_Start
    m_Pacman.SetPacX(320);
    m_Pacman.SetPacY(514);

    m_Scene.addItem(&m_Pacman);
}

void GameWindow::GenerateAndPlaceGhosts()
{
    m_StartTimer = 0;

    m_Scared = false;

    m_ScareState = 0;

    m_Ghost1.SetIsScared(false);
    m_Ghost2.SetIsScared(false);
    m_Ghost3.SetIsScared(false);
    m_Ghost4.SetIsScared(false);

    m_Ghost1.SetGhostX(307);
    m_Ghost1.SetGhostY(318);
    m_Ghost2.SetGhostX(307);
    m_Ghost2.SetGhostY(318);
    m_Ghost3.SetGhostX(307);
    m_Ghost3.SetGhostY(318);
    m_Ghost4.SetGhostX(307);
    m_Ghost4.SetGhostY(318);

    m_Ghost1.SetGhostColor("orange");
    m_Ghost2.SetGhostColor("red");
    m_Ghost3.SetGhostColor("blue");

    m_GhostMoving1=false;
    m_GhostMoving2=false;
    m_GhostMoving3=false;
    m_GhostMoving4=false;

    m_GhostStart1=false;
    m_GhostStart2=false;
    m_GhostStart3=false;
    m_GhostStart4=false;

    m_AllGhostsStarted = false;

    m_Scene.addItem(&m_Ghost1);
    m_Scene.addItem(&m_Ghost2);
    m_Scene.addItem(&m_Ghost3);
    m_Scene.addItem(&m_Ghost4);
}

void GameWindow::ShowScore()
{
    m_Score=0;
    m_pScoreDisplay = m_Scene.addText("Score:");
    m_pScoreDisplay->setDefaultTextColor(Qt::white);
    m_pScoreDisplay->setFont(QFont("Arial", 40));
    m_pScoreDisplay->setPos(0,671);
}

void GameWindow::StartGame()
{
    m_Sounds.m_BeginningSound.play();

    m_TextStartEnd.hide();

    connect(&m_Timer, SIGNAL(timeout()), this,SLOT(Updater()));
    connect(&m_GhostsTimer, SIGNAL(timeout()), this,SLOT(GhostUpdater()));

    m_Timer.start(4);
    m_GhostsTimer.start(4);
    this->setFocus(); //gives the keyboard input focus to this widget
}

void GameWindow::RestartGame()
{
    ClearVariablesAndContainers();

    m_Pacman.show();
    m_Ghost1.show();
    m_Ghost2.show();
    m_Ghost3.show();
    m_Ghost4.show();

    GenerateAndPopulateMap();
    GenerateAndPlacePacman();
    GenerateAndPlaceGhosts();

    ShowScore();

    m_Sounds.m_BeginningSound.play();

    m_TextStartEnd.hide();

    m_Timer.start(4);
    m_GhostsTimer.start(4);
    this->setFocus(); //gives the keyboard input focus to this widget
}

void GameWindow::ClearVariablesAndContainers()
{
    m_PowerballGraphicalItemsTable.clear();
    m_FoodballGraphicalItemsTable.clear();
    m_PowerballGraphicalItemsTable.squeeze();
    m_FoodballGraphicalItemsTable.squeeze();
}

void GameWindow::HideSceneItems()
{
    m_pMapItem->hide();
    m_pScoreDisplay->hide();

    m_Pacman.hide();
    m_Scene.removeItem(&m_Pacman);

    m_Ghost1.hide();
    m_Ghost2.hide();
    m_Ghost3.hide();
    m_Ghost4.hide();
    m_Scene.removeItem(&m_Ghost1);
    m_Scene.removeItem(&m_Ghost2);
    m_Scene.removeItem(&m_Ghost3);
    m_Scene.removeItem(&m_Ghost4);

    for(int i=0; i<m_FoodballGraphicalItemsTable.size();i++)
    {
        m_FoodballGraphicalItemsTable.at(i)->hide();
    }

    for(int i=0; i<m_PowerballGraphicalItemsTable.size();i++)
    {
        m_PowerballGraphicalItemsTable.at(i)->hide();
    }
}

void GameWindow::EndGame(int win)
{
    if(win==1)
    {
        HideSceneItems();

        m_TextStartEnd.show();

        m_TextStartEnd.SetScore(m_Score);
        m_TextStartEnd.SetGameWon(true);
        m_TextStartEnd.show();

        m_Score=0;

        m_Scene.update();
        m_Playing = false;
        m_ReadyToRestart = true;
    }

    else
    {
        m_Sounds.m_PacmanDeathSound.play();

        HideSceneItems();

        m_TextStartEnd.show();
        m_TextStartEnd.SetScore(m_Score);
        m_TextStartEnd.SetGameLost(true);
        m_TextStartEnd.show();

        m_Score=0;

        m_Scene.update();
        m_Playing = false;
        m_ReadyToRestart = true;
    }
}

void GameWindow::PacmanMove()
{
    QPoint p;

    int pac_x = m_Pacman.GetPacX();
    int pac_y = m_Pacman.GetPacY();
    int direction = m_Pacman.GetDirection();
    int nextdirection = m_Pacman.GetNextDirection();

    if(nextdirection!=direction)
    {
        switch(nextdirection)
        {
        case 1: //left
            p.setX(pac_x-1);
            p.setY(pac_y);

            if(m_PacMap.IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 2: //up
            p.setX(pac_x);
            p.setY(pac_y-1);
            if(m_PacMap.IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 3: //down
            p.setX(pac_x);
            p.setY(pac_y+1);
            if(m_PacMap.IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 4: //right
            p.setX(pac_x+1);
            p.setY(pac_y);
            if(m_PacMap.IsPointAvailable(p))
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
        m_Pacman.SetDirection(direction);

        if(m_PacMap.IsPointAvailable(p))
        {
            pac_x = pac_x - 1;
        }

        break;

    case 2: //up
        p.setX(pac_x);
        p.setY(pac_y-1);
        m_Pacman.SetDirection(direction);

        if(m_PacMap.IsPointAvailable(p))
        {
            pac_y= pac_y - 1;
        }

        break;

    case 3: //down
        p.setX(pac_x);
        p.setY(pac_y+1);
        m_Pacman.SetDirection(direction);

        if(m_PacMap.IsPointAvailable(p))
        {
            pac_y= pac_y + 1;
        }

        break;

    case 4: //right
        p.setX(pac_x+1);
        p.setY(pac_y);
        m_Pacman.SetDirection(direction);

        if(m_PacMap.IsPointAvailable(p))
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

    m_Pacman.SetPacX(pac_x);
    m_Pacman.SetPacY(pac_y);
}

void GameWindow::GhostMove1()
{
    QPoint p;

    int pac_x = m_Pacman.GetPacX();
    int pac_y = m_Pacman.GetPacY();
    int m_Ghost1X = m_Ghost1.GetGhostX();
    int m_Ghost1Y = m_Ghost1.GetGhostY();
    int m_Ghost1Dir = m_Ghost1.GetGhostDirection();
    int m_NextGhost1Dir = m_Ghost1.GetNextGhostDirection();

    if(!m_GhostMoving1)
    {
        m_Ghost1Dir=(qrand()%4)+1;
    }
    else
    {
        if(m_Ghost1Dir==4 &&m_Ghost1Y<pac_y || m_Ghost1Dir==1 && m_Ghost1Y>pac_y)
        {
            if(m_Ghost1Dir==1 && m_Ghost1Y>pac_y)
            {
                m_NextGhost1Dir=2;
            }
            else if(m_Ghost1Dir==4 &&m_Ghost1Y<pac_y)
            {
                m_NextGhost1Dir=3;
            }
        }
        else if(m_Ghost1Dir==3 && m_Ghost1X<pac_x || m_Ghost1Dir==2 && m_Ghost1X>pac_x)
        {
            if(m_Ghost1Dir==2 && m_Ghost1X>pac_x)
            {
                m_NextGhost1Dir=1;
            }
            else if(m_Ghost1Dir==3 && m_Ghost1X<pac_x)
            {
                m_NextGhost1Dir=4;
            }
        }
    }

    if(m_NextGhost1Dir!=m_Ghost1Dir)
    {
        switch(m_NextGhost1Dir)
        {
        case 1:
            p.setX(m_Ghost1X-1);
            p.setY(m_Ghost1Y);

            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost1Dir=m_NextGhost1Dir;
                m_NextGhost1Dir=0;
            }

            break;

        case 4:
            p.setX(m_Ghost1X+1);
            p.setY(m_Ghost1Y);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost1Dir=m_NextGhost1Dir;
                m_NextGhost1Dir=0;
            }

            break;
        case 3:
            p.setX(m_Ghost1X);
            p.setY(m_Ghost1Y+1);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost1Dir=m_NextGhost1Dir;
                m_NextGhost1Dir=0;
            }

            break;
        case 2:
            p.setX(m_Ghost1X);
            p.setY(m_Ghost1Y-1);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost1Dir=m_NextGhost1Dir;
                m_NextGhost1Dir=0;
            }

            break;
        }
    }

    switch(m_Ghost1Dir)
    {
    case 1:
        p.setX(m_Ghost1X-1);
        p.setY(m_Ghost1Y);
        m_Ghost1.SetGhostDirection(m_Ghost1Dir);

        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost1X-=1;
            m_GhostMoving1=true;
        }
        else
        {
            m_GhostMoving1=false;
        }

        break;

    case 4:
        m_Ghost1.SetGhostDirection(m_Ghost1Dir);
        p.setX(m_Ghost1X+1);
        p.setY(m_Ghost1Y);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost1X+=1;
            m_GhostMoving1=true;
        }
        else
        {
            m_GhostMoving1=false;
        }

        break;

    case 3:
        m_Ghost1.SetGhostDirection(m_Ghost1Dir);
        p.setX(m_Ghost1X);
        p.setY(m_Ghost1Y+1);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost1Y+=1;
            m_GhostMoving1=true;
        }
        else
        {
            m_GhostMoving1=false;
        }

        break;
    case 2:
        m_Ghost1.SetGhostDirection(m_Ghost1Dir);
        p.setX(m_Ghost1X);
        p.setY(m_Ghost1Y-1);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost1Y-=1;
            m_GhostMoving1=true;
        }
        else
        {
            m_GhostMoving1=false;
        }

        break;
    }

    if(m_Ghost1X<=0)
    {
        m_Ghost1X=613;
        m_Ghost1Y=318;
    }
    else if(m_Ghost1X>=614)
    {
        m_Ghost1X=1;
        m_Ghost1Y=318;
    }

    m_Ghost1.SetGhostX(m_Ghost1X);
    m_Ghost1.SetGhostY(m_Ghost1Y);
    m_Ghost1.SetNextGhostDirection(m_NextGhost1Dir);
}
void GameWindow::GhostMove2()
{
    QPoint p;

    int pac_x = m_Pacman.GetPacX();
    int pac_y = m_Pacman.GetPacY();
    int m_Ghost2X = m_Ghost2.GetGhostX();
    int m_Ghost2Y = m_Ghost2.GetGhostY();
    int m_Ghost2Dir = m_Ghost2.GetGhostDirection();
    int m_NextGhost2Dir = m_Ghost2.GetNextGhostDirection();

    if(!m_GhostMoving2)
    {
        m_Ghost2Dir=(qrand()%4)+1;
    }
    else
    {
        if(m_Ghost2Dir==4 &&m_Ghost2Y<pac_y || m_Ghost2Dir==1 && m_Ghost2Y>pac_y)
        {
            if(m_Ghost2Dir==1 && m_Ghost2Y>pac_y)
            {
                m_NextGhost2Dir=2;
            }
            else if(m_Ghost2Dir==4 &&m_Ghost2Y<pac_y)
            {
                m_NextGhost2Dir=3;
            }
        }
        else if(m_Ghost2Dir==3 && m_Ghost2X<pac_x || m_Ghost2Dir==2 && m_Ghost2X>pac_x)
        {
            if(m_Ghost2Dir==2 && m_Ghost2X>pac_x)
            {
                m_NextGhost2Dir=1;
            }
            else if(m_Ghost2Dir==3 && m_Ghost2X<pac_x)
            {
                m_NextGhost2Dir=4;
            }
        }
    }

    if(m_NextGhost2Dir!=m_Ghost2Dir)
    {
        switch(m_NextGhost2Dir)
        {
        case 1:
            p.setX(m_Ghost2X-1);
            p.setY(m_Ghost2Y);

            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost2Dir=m_NextGhost2Dir;
                m_NextGhost2Dir=0;
            }

            break;

        case 4:
            p.setX(m_Ghost2X+1);
            p.setY(m_Ghost2Y);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost2Dir=m_NextGhost2Dir;
                m_NextGhost2Dir=0;
            }

            break;
        case 3:
            p.setX(m_Ghost2X);
            p.setY(m_Ghost2Y+1);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost2Dir=m_NextGhost2Dir;
                m_NextGhost2Dir=0;
            }

            break;
        case 2:
            p.setX(m_Ghost2X);
            p.setY(m_Ghost2Y-1);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost2Dir=m_NextGhost2Dir;
                m_NextGhost2Dir=0;
            }
            break;
        }
    }

    switch(m_Ghost2Dir)
    {
    case 1:
        p.setX(m_Ghost2X-1);
        p.setY(m_Ghost2Y);
        m_Ghost2.SetGhostDirection(m_Ghost2Dir);

        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost2X-=1;
            m_GhostMoving2=true;
        }
        else
        {
            m_GhostMoving2=false;
        }

        break;

    case 4:
        m_Ghost2.SetGhostDirection(m_Ghost2Dir);
        p.setX(m_Ghost2X+1);
        p.setY(m_Ghost2Y);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost2X+=1;
            m_GhostMoving2=true;
        }
        else
        {
            m_GhostMoving2=false;
        }

        break;
    case 3:
        m_Ghost2.SetGhostDirection(m_Ghost2Dir);
        p.setX(m_Ghost2X);
        p.setY(m_Ghost2Y+1);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost2Y+=1;
            m_GhostMoving2=true;
        }
        else
        {
            m_GhostMoving2=false;
        }

        break;
    case 2:
        m_Ghost2.SetGhostDirection(m_Ghost2Dir);
        p.setX(m_Ghost2X);
        p.setY(m_Ghost2Y-1);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost2Y-=1;
            m_GhostMoving2=true;
        }
        else
        {
            m_GhostMoving2=false;
        }

        break;
    }

    if(m_Ghost2X<=0)
    {
        m_Ghost2X=613;
        m_Ghost2Y=318;
    }
    else if(m_Ghost2X>=614)
    {
        m_Ghost2X=1;
        m_Ghost2Y=318;
    }

    m_Ghost2.SetGhostX(m_Ghost2X);
    m_Ghost2.SetGhostY(m_Ghost2Y);
    m_Ghost2.SetNextGhostDirection(m_NextGhost2Dir);
}
void GameWindow::GhostMove3()
{
    QPoint p;

    int pac_x = m_Pacman.GetPacX();
    int pac_y = m_Pacman.GetPacY();
    int m_Ghost3X = m_Ghost3.GetGhostX();
    int m_Ghost3Y = m_Ghost3.GetGhostY();
    int m_Ghost3Dir = m_Ghost3.GetGhostDirection();
    int m_NextGhost3Dir = m_Ghost3.GetNextGhostDirection();

    if(!m_GhostMoving3)
    {
        m_Ghost3Dir=(qrand()%4)+1;
    }
    else
    {
        if(m_Ghost3Dir==4 &&m_Ghost3Y<pac_y || m_Ghost3Dir==1 && m_Ghost3Y>pac_y)
        {
            if(m_Ghost3Dir==1 && m_Ghost3Y>pac_y)
            {
                m_NextGhost3Dir=2;
            }
            else if(m_Ghost3Dir==4 &&m_Ghost3Y<pac_y)
            {
                m_NextGhost3Dir=3;
            }

        }
        else if(m_Ghost3Dir==3 && m_Ghost3X<pac_x || m_Ghost3Dir==2 && m_Ghost3X>pac_x)
        {
            if(m_Ghost3Dir==2 && m_Ghost3X>pac_x)
            {
                m_NextGhost3Dir=1;
            }
            else if(m_Ghost3Dir==3 && m_Ghost3X<pac_x)
            {
                m_NextGhost3Dir=4;
            }
        }
    }

    if(m_NextGhost3Dir!=m_Ghost3Dir)
    {
        switch(m_NextGhost3Dir)
        {
        case 1:
            p.setX(m_Ghost3X-1);
            p.setY(m_Ghost3Y);

            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost3Dir=m_NextGhost3Dir;
                m_NextGhost3Dir=0;

            }

            break;

        case 4:
            p.setX(m_Ghost3X+1);
            p.setY(m_Ghost3Y);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost3Dir=m_NextGhost3Dir;
                m_NextGhost3Dir=0;
            }

            break;
        case 3:
            p.setX(m_Ghost3X);
            p.setY(m_Ghost3Y+1);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost3Dir=m_NextGhost3Dir;
                m_NextGhost3Dir=0;
            }

            break;
        case 2:
            p.setX(m_Ghost3X);
            p.setY(m_Ghost3Y-1);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost3Dir=m_NextGhost3Dir;
                m_NextGhost3Dir=0;
            }
            break;
        }

    }
    switch(m_Ghost3Dir)
    {
    case 1:
        p.setX(m_Ghost3X-1);
        p.setY(m_Ghost3Y);
        m_Ghost3.SetGhostDirection(m_Ghost3Dir);

        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost3X-=1;
            m_GhostMoving3=true;

        }
        else
        {
            m_GhostMoving3=false;
        }

        break;

    case 4:
        m_Ghost3.SetGhostDirection(m_Ghost3Dir);
        p.setX(m_Ghost3X+1);
        p.setY(m_Ghost3Y);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost3X+=1;
            m_GhostMoving3=true;
        }
        else
        {
            m_GhostMoving3=false;
        }

        break;
    case 3:
        m_Ghost3.SetGhostDirection(m_Ghost3Dir);
        p.setX(m_Ghost3X);
        p.setY(m_Ghost3Y+1);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost3Y+=1;
            m_GhostMoving3=true;
        }
        else
        {
            m_GhostMoving3=false;
        }

        break;
    case 2:
        m_Ghost3.SetGhostDirection(m_Ghost3Dir);
        p.setX(m_Ghost3X);
        p.setY(m_Ghost3Y-1);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost3Y-=1;
            m_GhostMoving3=true;
        }
        else
        {
            m_GhostMoving3=false;
        }
        break;
    }


    if(m_Ghost3X<=0)
    {
        m_Ghost3X=613;
        m_Ghost3Y=318;
    }
    else if(m_Ghost3X>=614)
    {
        m_Ghost3X=1;
        m_Ghost3Y=318;
    }

    m_Ghost3.SetGhostX(m_Ghost3X);
    m_Ghost3.SetGhostY(m_Ghost3Y);
    m_Ghost3.SetNextGhostDirection(m_NextGhost3Dir);
}
void GameWindow::GhostMove4()
{
    QPoint p;

    int pac_x = m_Pacman.GetPacX();
    int pac_y = m_Pacman.GetPacY();
    int m_Ghost4X = m_Ghost4.GetGhostX();
    int m_Ghost4Y = m_Ghost4.GetGhostY();
    int m_Ghost4Dir = m_Ghost4.GetGhostDirection();
    int m_NextGhost4Dir = m_Ghost4.GetNextGhostDirection();

    if(!m_GhostMoving4)
    {
        m_Ghost4Dir=(qrand()%4)+1;
    }
    else
    {
        if(m_Ghost4Dir==4 &&m_Ghost4Y<pac_y || m_Ghost4Dir==1 && m_Ghost4Y>pac_y)
        {
            if(m_Ghost4Dir==1 && m_Ghost4Y>pac_y)
            {
                m_NextGhost4Dir=2;
            }
            else if(m_Ghost4Dir==4 &&m_Ghost4Y<pac_y)
            {
                m_NextGhost4Dir=3;
            }
        }
        else if(m_Ghost4Dir==3 && m_Ghost4X<pac_x || m_Ghost4Dir==2 && m_Ghost4X>pac_x)
        {
            if(m_Ghost4Dir==2 && m_Ghost4X>pac_x)
            {
                m_NextGhost4Dir=1;
            }
            else if(m_Ghost4Dir==3 && m_Ghost4X<pac_x)
            {
                m_NextGhost4Dir=4;
            }
        }
    }

    if(m_NextGhost4Dir!=m_Ghost4Dir)
    {
        switch(m_NextGhost4Dir)
        {
        case 1:
            p.setX(m_Ghost4X-1);
            p.setY(m_Ghost4Y);

            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost4Dir=m_NextGhost4Dir;
                m_NextGhost4Dir=0;
            }

            break;

        case 4:
            p.setX(m_Ghost4X+1);
            p.setY(m_Ghost4Y);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost4Dir=m_NextGhost4Dir;
                m_NextGhost4Dir=0;
            }

            break;
        case 3:
            p.setX(m_Ghost4X);
            p.setY(m_Ghost4Y+1);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost4Dir=m_NextGhost4Dir;
                m_NextGhost4Dir=0;
            }

            break;
        case 2:
            p.setX(m_Ghost4X);
            p.setY(m_Ghost4Y-1);
            if(m_PacMap.IsPointAvailable(p))
            {
                m_Ghost4Dir=m_NextGhost4Dir;
                m_NextGhost4Dir=0;
            }

            break;
        }

    }
    switch(m_Ghost4Dir)
    {
    case 1:
        p.setX(m_Ghost4X-1);
        p.setY(m_Ghost4Y);
        m_Ghost4.SetGhostDirection(m_Ghost4Dir);

        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost4X-=1;
            m_GhostMoving4=true;
        }
        else
        {
            m_GhostMoving4=false;
        }

        break;

    case 4:
        m_Ghost4.SetGhostDirection(m_Ghost4Dir);
        p.setX(m_Ghost4X+1);
        p.setY(m_Ghost4Y);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost4X+=1;
            m_GhostMoving4=true;
        }
        else
        {
            m_GhostMoving4=false;
        }

        break;
    case 3:
        m_Ghost4.SetGhostDirection(m_Ghost4Dir);
        p.setX(m_Ghost4X);
        p.setY(m_Ghost4Y+1);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost4Y+=1;
            m_GhostMoving4=true;
        }
        else
        {
            m_GhostMoving4=false;
        }

        break;
    case 2:
        m_Ghost4.SetGhostDirection(m_Ghost4Dir);
        p.setX(m_Ghost4X);
        p.setY(m_Ghost4Y-1);
        if(m_PacMap.IsPointAvailable(p))
        {
            m_Ghost4Y-=1;
            m_GhostMoving4=true;
        }
        else
        {
            m_GhostMoving4=false;
        }
        break;
    }

    if(m_Ghost4X<=0)
    {
        m_Ghost4X=613;
        m_Ghost4Y=318;
    }
    else if(m_Ghost4X>=614)
    {
        m_Ghost4X=1;
        m_Ghost4Y=318;
    }
    m_Ghost4.SetGhostX(m_Ghost4X);
    m_Ghost4.SetGhostY(m_Ghost4Y);
    m_Ghost4.SetNextGhostDirection(m_NextGhost4Dir);
}

void GameWindow::MoveGhostInStartingRect1()
{
    int m_Ghost1X = m_Ghost1.GetGhostX();
    int m_Ghost1Y = m_Ghost1.GetGhostY();
    int m_Ghost1Dir = m_Ghost1.GetGhostDirection();

    if(m_Ghost1X==307-50 || m_Ghost1X==307+50)
    {
        if(m_Ghost1Dir==4)
        {
            m_Ghost1Dir=1; //go left
        }
        else
        {
            m_Ghost1Dir=4; //go right
        }
    }

    if(m_Ghost1Dir==4)
    {
        m_Ghost1X+=1;
    }
    else
    {
        m_Ghost1X-=1;
    }

    m_Ghost1.SetGhostX(m_Ghost1X);
    m_Ghost1.SetGhostY(m_Ghost1Y);
    m_Ghost1.SetGhostDirection(m_Ghost1Dir);
}
void GameWindow::MoveGhostInStartingRect2()
{
    int m_Ghost2X = m_Ghost2.GetGhostX();
    int m_Ghost2Y = m_Ghost2.GetGhostY();
    int m_Ghost2Dir = m_Ghost2.GetGhostDirection();

    if(m_Ghost2X==307-50 || m_Ghost2X==307+50)
    {
        if(m_Ghost2Dir==4)
        {
            m_Ghost2Dir=1;
        }
        else
        {
            m_Ghost2Dir=4;
        }
    }
    if(m_Ghost2Dir==4)
    {
        m_Ghost2X+=1;
    }
    else
    {
        m_Ghost2X-=1;
    }

    m_Ghost2.SetGhostX(m_Ghost2X);
    m_Ghost2.SetGhostY(m_Ghost2Y);
    m_Ghost2.SetGhostDirection(m_Ghost2Dir);
}
void GameWindow::MoveGhostInStartingRect3()
{
    int m_Ghost3X = m_Ghost3.GetGhostX();
    int m_Ghost3Y = m_Ghost3.GetGhostY();
    int m_Ghost3Dir = m_Ghost3.GetGhostDirection();

    if(m_Ghost3X==307-50 || m_Ghost3X==307+50)
    {
        if(m_Ghost3Dir==4)
        {
            m_Ghost3Dir=1;
        }
        else
        {
            m_Ghost3Dir=4;
        }
    }
    if(m_Ghost3Dir==4)
    {
        m_Ghost3X+=1;
    }
    else
    {
        m_Ghost3X-=1;
    }

    m_Ghost3.SetGhostX(m_Ghost3X);
    m_Ghost3.SetGhostY(m_Ghost3Y);
    m_Ghost3.SetGhostDirection(m_Ghost3Dir);
}
void GameWindow::MoveGhostInStartingRect4()
{
    int m_Ghost4X = m_Ghost4.GetGhostX();
    int m_Ghost4Y = m_Ghost4.GetGhostY();
    int m_Ghost4Dir = m_Ghost4.GetGhostDirection();

    if(m_Ghost4X==307-50 || m_Ghost4X==307+50)
    {
        if(m_Ghost4Dir==4)
        {
            m_Ghost4Dir=1;
        }
        else
        {
            m_Ghost4Dir=4;
        }
    }
    if(m_Ghost4Dir==4)
    {
        m_Ghost4X+=1;
    }
    else
    {
        m_Ghost4X-=1;
    }

    m_Ghost4.SetGhostX(m_Ghost4X);
    m_Ghost4.SetGhostY(m_Ghost4Y);
    m_Ghost4.SetGhostDirection(m_Ghost4Dir);
}

/*Supports pacman movement using WSAD and directional keys*/
void GameWindow::keyPressEvent(QKeyEvent *event)
{
    int nextdirection=m_Pacman.GetNextDirection();

    switch(event->key())
    {
    case Qt::Key_Left:
        nextdirection=1;
        break;
    case Qt::Key_A:
        nextdirection=1;
        break;

    case Qt::Key_Right:
        nextdirection=4;
        break;
    case Qt::Key_D:
        nextdirection=4;
        break;

    case Qt::Key_Down:
        nextdirection=3;
        break;
    case Qt::Key_S:
        nextdirection=3;
        break;

    case Qt::Key_Up:
        nextdirection=2;
        break;
    case Qt::Key_W:
        nextdirection=2;
        break;

    case Qt::Key_Space:
        if(!m_Playing && m_ReadyToRestart == false)
        {
            m_Playing = true;
            StartGame();
        }
        if(!m_Playing && m_ReadyToRestart == true)
        {
            m_ReadyToRestart = false;
            m_Playing = true;
            RestartGame();
        }

    default:
        break;
    }
    m_Pacman.SetNextDirection(nextdirection);
}

void GameWindow::CheckCollision()
{
    if(m_Pacman.collidesWithItem(&m_Ghost1) ||
            m_Pacman.collidesWithItem(&m_Ghost2) ||
            m_Pacman.collidesWithItem(&m_Ghost3) ||
            m_Pacman.collidesWithItem(&m_Ghost4))
    {
        if(m_Pacman.collidesWithItem(&m_Ghost1) && m_Ghost1.GetIsScared())
        {
            m_Sounds.m_EatGhostSound.play();
            m_Score+=200;
            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));
            m_Ghost1.SetGhostX(307);
            m_Ghost1.SetGhostY(252);
            m_Ghost1.SetIsScared(false);
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost2) && m_Ghost2.GetIsScared())
        {
            m_Sounds.m_EatGhostSound.play();
            m_Score+=200;
            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));
            m_Ghost2.SetGhostX(307);
            m_Ghost2.SetGhostY(252);
            m_Ghost2.SetIsScared(false);
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost3) && m_Ghost3.GetIsScared())
        {
            m_Sounds.m_EatGhostSound.play();
            m_Score+=200;
            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));
            m_Ghost3.SetGhostX(307);
            m_Ghost3.SetGhostY(252);
            m_Ghost3.SetIsScared(false);
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost4) && m_Ghost4.GetIsScared())
        {
            m_Sounds.m_EatGhostSound.play();
            m_Score+=200;
            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));
            m_Ghost4.SetGhostX(307);
            m_Ghost4.SetGhostY(252);
            m_Ghost4.SetIsScared(false);
        }
        else
        {
            m_Timer.stop();
            m_GhostsTimer.stop();
            EndGame(0);
        }
    }
}

void GameWindow::Updater()
{
    int pac_x = m_Pacman.GetPacX();
    int pac_y = m_Pacman.GetPacY();

    if(m_CollisionDetectionDelay >= 500)
        CheckCollision();
    else
        m_CollisionDetectionDelay++;

    PacmanMove();  //changes position of pacman

    for(int i=0;i<m_FoodballPositions.size();i++)
    {
        if(pac_x==m_FoodballPositions.at(i).x() && pac_y==m_FoodballPositions.at(i).y())
        {
            m_FoodballPositions.remove(i);
            m_FoodballGraphicalItemsTable.at(i)->hide();
            m_FoodballGraphicalItemsTable.remove(i);

            if(m_Sounds.m_EatSound1.state()==QMediaPlayer::StoppedState)
            {
                m_Sounds.m_EatSound1.play();
            }

            if(m_Sounds.m_EatSound1.state()==QMediaPlayer::PlayingState)
            {
                m_Sounds.m_EatSound2.play();
            }

            m_Score++;
            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));

            m_FoodballItemsCount--;
        }
    }

    for(int i=0;i<m_PowerballPositions.size();i++)
    {
        if(pac_x==m_PowerballPositions.at(i).x() && pac_y==m_PowerballPositions.at(i).y())
        {
            m_PowerballPositions.remove(i);
            m_PowerballGraphicalItemsTable.at(i)->hide();
            m_PowerballGraphicalItemsTable.remove(i);

            m_Score += 100;
            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));

            m_ScareState = 0;

            m_Ghost1.SetIsScared(true);
            m_Ghost2.SetIsScared(true);
            m_Ghost3.SetIsScared(true);
            m_Ghost4.SetIsScared(true);

            m_Scared=true;

            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));
        }
    }

    if(m_FoodballItemsCount==0)
    {
        m_Timer.stop();
        m_GhostsTimer.stop();
        EndGame(1);
    }

    if(m_Scared)
    {
        m_ScareState+=1;

        if(m_ScareState==1)
        {
            m_GhostsTimer.setInterval(50);
        }

        if(m_ScareState==750)
        {
            m_Ghost1.SetScaredWhite(true);
            m_Ghost2.SetScaredWhite(true);
            m_Ghost3.SetScaredWhite(true);
            m_Ghost4.SetScaredWhite(true);
        }

        if(m_ScareState==1000)
        {
            m_Scared=false;
            m_Ghost1.SetIsScared(false);
            m_Ghost2.SetIsScared(false);
            m_Ghost3.SetIsScared(false);
            m_Ghost4.SetIsScared(false);

            m_Ghost1.SetScaredWhite(false);
            m_Ghost2.SetScaredWhite(false);
            m_Ghost3.SetScaredWhite(false);
            m_Ghost4.SetScaredWhite(false);

            m_ScareState = 0;
            m_GhostsTimer.setInterval(4);
        }
    }

    m_Pacman.Advance();
    m_Ghost1.Advance();
    m_Ghost2.Advance();
    m_Ghost3.Advance();
    m_Ghost4.Advance();

    m_Scene.update(m_Scene.sceneRect());
}

void GameWindow::GhostUpdater()
{
    int m_Ghost1X = m_Ghost1.GetGhostX();
    int m_Ghost1Y = m_Ghost1.GetGhostY();
    int m_Ghost2X = m_Ghost2.GetGhostX();
    int m_Ghost2Y = m_Ghost2.GetGhostY();
    int m_Ghost3X = m_Ghost3.GetGhostX();
    int m_Ghost3Y = m_Ghost3.GetGhostY();
    int m_Ghost4X = m_Ghost4.GetGhostX();
    int m_Ghost4Y = m_Ghost4.GetGhostY();

    if(m_AllGhostsStarted)
    {
        GhostMove1();
        GhostMove2();
        GhostMove3();
        GhostMove4();
    }
    else
    {
        if(!m_GhostStart1)
            MoveGhostInStartingRect1();
        else
            GhostMove1();

        if(!m_GhostStart2)
            MoveGhostInStartingRect2();
        else
            GhostMove2();

        if(!m_GhostStart3)
            MoveGhostInStartingRect3();
        else
            GhostMove3();

        if(!m_GhostStart4)
            MoveGhostInStartingRect4();
        else
            GhostMove4();

        if(m_Ghost1X==300 || m_Ghost2X==300 || m_Ghost3X==300 || m_Ghost4X==300) //substitute of timer to be implemented for every ghost do differentiate m_Start time
        {
            m_StartTimer++;
        }

        if(m_StartTimer>=3) // ghost 1 starts
        {
            QPoint p1;
            if(m_Ghost1X>307)
            {
                m_Ghost1X-=1;
            }
            else if(m_Ghost1X<307)
            {
                m_Ghost1X+=1;
            }

            if(!m_GhostStart1)
            {
                m_Ghost1Y-=1;
                m_Ghost1.SetGhostX(m_Ghost1X);
                m_Ghost1.SetGhostY(m_Ghost1Y);
                p1.setX(m_Ghost1X);
                p1.setY(m_Ghost1Y);
                if(m_PacMap.GetPacmanPaths().contains(p1))
                {
                    m_GhostStart1=true;
                }
            }
        }

        if(m_StartTimer>=6) // ghost 2 starts
        {
            QPoint p2;
            if(m_Ghost2X>307)
            {
                m_Ghost2X-=1;
            }
            else if(m_Ghost2X<307)
            {
                m_Ghost2X+=1;
            }

            if(!m_GhostStart2)
            {
                m_Ghost2Y-=1;
                m_Ghost2.SetGhostX(m_Ghost2X);
                m_Ghost2.SetGhostY(m_Ghost2Y);
                p2.setX(m_Ghost2X);
                p2.setY(m_Ghost2Y);
                if(m_PacMap.GetPacmanPaths().contains(p2))
                {
                    m_GhostStart2=true;
                }
            }
        }

        if(m_StartTimer>=9) // ghost 3 starts
        {
            QPoint p3;
            if(m_Ghost3X>307)
            {
                m_Ghost3X-=1;
            }
            else if(m_Ghost3X<307)
            {
                m_Ghost3X+=1;
            }

            if(!m_GhostStart3)
            {
                m_Ghost3Y-=1;
                m_Ghost3.SetGhostX(m_Ghost3X);
                m_Ghost3.SetGhostY(m_Ghost3Y);
                p3.setX(m_Ghost3X);
                p3.setY(m_Ghost3Y);
                if(m_PacMap.GetPacmanPaths().contains(p3))
                {
                    m_GhostStart3=true;
                }
            }
        }

        if(m_StartTimer>=12) // ghost 4 starts
        {
            QPoint p4;
            if(m_Ghost4X>307)
            {
                m_Ghost4X-=1;
            }
            else if(m_Ghost4X<307)
            {
                m_Ghost4X+=1;
            }

            if(!m_GhostStart4)
            {
                m_Ghost4Y-=1;
                m_Ghost4.SetGhostX(m_Ghost4X);
                m_Ghost4.SetGhostY(m_Ghost4Y);
                p4.setX(m_Ghost4X);
                p4.setY(m_Ghost4Y);
                if(m_PacMap.GetPacmanPaths().contains(p4))
                {
                    m_GhostStart4=true;
                }
            }
        }

        if(m_GhostStart1&&m_GhostStart2&&m_GhostStart3&&m_GhostStart4)
            m_AllGhostsStarted=true;
    }
}

GameWindow::~GameWindow()
{
    delete m_pUi;
}
