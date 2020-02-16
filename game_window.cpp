#include "game_window.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) : QDialog(parent), m_pUi(new Ui::GameWindow)
{
    m_pUi->setupUi(this);

    setFocus(Qt::ActiveWindowFocusReason);

    m_GameState = GameState::BeforeFirstRun;

    InitializeGameplayAreaScene();

    PrepareFirstGameRun();
}

void GameWindow::InitializeGameplayAreaScene()
{
    m_Scene.setParent(this);
    m_pUi->m_pGameplayArea->setScene(&m_Scene);
    m_pUi->m_pGameplayArea->setRenderHint(QPainter::Antialiasing);
    m_Scene.setSceneRect(0,0,614,740);
    m_pUi->m_pGameplayArea->setSceneRect(m_Scene.sceneRect());
}

void GameWindow::PrepareFirstGameRun()
{
    GenerateAndPopulateMap();
    GenerateAndPlacePacman();
    GenerateAndPlaceGhosts();
    GenerateAndPlaceScoreDisplay();

    /*Delay collision detection after game restart*/
    m_CollisionWithGhostDetectionDelay = 0;

    m_Scene.addItem(&m_StartEndTextDisplay);
}

void GameWindow::GenerateAndPopulateMap()
{
    /*Add background map picture*/
    m_pMapItem = m_Scene.addPixmap(m_PacMap.GetMapBackgroundPicture());

    m_PowerballPositions = m_Powerball.GetPowerBallPositions();
    m_FoodballPositions = m_Foodball.GetFoodBallPositions();

    int const powerballRadius = 15;

    for(int i=0; i<m_PowerballPositions.size();i++)
    {
        m_PowerballGraphicalItemsTable.push_back(m_Scene.addEllipse(m_PowerballPositions.at(i).x()-5,
                                                                    m_PowerballPositions.at(i).y()-8,
                                                                    powerballRadius,
                                                                    powerballRadius,
                                                                    QPen(Qt::NoPen),
                                                                    QBrush(Qt::white)));
    }

    m_FoodballItemsCount=m_FoodballPositions.size();

    int const foodballRadius = 7;

    for(int i=0;i<m_FoodballPositions.size();i++)
    {
        m_FoodballGraphicalItemsTable.push_back(m_Scene.addEllipse(m_FoodballPositions.at(i).x(),
                                                                   m_FoodballPositions.at(i).y(),
                                                                   foodballRadius,
                                                                   foodballRadius,
                                                                   QPen(Qt::NoPen),
                                                                   QBrush(Qt::white)));
    }
}

void GameWindow::GenerateAndPlacePacman()
{
    m_Pacman.Reset();

    m_Scene.addItem(&m_Pacman);
}

void GameWindow::GenerateAndPlaceGhosts()
{
    Ghost::SetAllGhostsScared(false);

    Ghost::SetAllGhostsScareState(0);

    m_Ghost1.Reset();
    m_Ghost2.Reset();
    m_Ghost3.Reset();
    m_Ghost4.Reset();

    m_Ghost1.SetGhostColor("orange");
    m_Ghost2.SetGhostColor("red");
    m_Ghost3.SetGhostColor("blue");

    Ghost::SetAllGhostsStartedFreeMovement(false);

    m_Scene.addItem(&m_Ghost1);
    m_Scene.addItem(&m_Ghost2);
    m_Scene.addItem(&m_Ghost3);
    m_Scene.addItem(&m_Ghost4);
}

void GameWindow::GenerateAndPlaceScoreDisplay()
{
    m_Score=0;

    m_pScoreDisplay = m_Scene.addText("Score: " + QString::number(m_Score));

    m_pScoreDisplay->setDefaultTextColor(Qt::white);
    m_pScoreDisplay->setFont(QFont("Arial", 40));
    m_pScoreDisplay->setPos(0,671);
}

void GameWindow::StartGame()
{
    m_Sounds.m_BeginningSound.play();

    m_StartEndTextDisplay.hide();

    connect(&m_Timer, SIGNAL(timeout()), this,SLOT(Updater()));
    connect(&m_GhostsTimer, SIGNAL(timeout()), this,SLOT(GhostUpdater()));

    m_Timer.start(4);
    m_GhostsTimer.start(4);

    m_GameState = GameState::GameRunning;

    /*Gives keyboard input focus to this widget*/
    setFocus();
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

    GenerateAndPlaceScoreDisplay();

    m_Sounds.m_BeginningSound.play();

    m_StartEndTextDisplay.hide();

    m_Timer.start(4);
    m_GhostsTimer.start(4);

    m_GameState = GameState::GameRunning;

    /*Gives keyboard input focus to this widget*/
    this->setFocus();
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

void GameWindow::EndGame(bool win)
{
    HideSceneItems();

    m_StartEndTextDisplay.show();
    m_StartEndTextDisplay.SetScore(m_Score);
    m_StartEndTextDisplay.SetScore(m_Score);
    m_Score=0;

    if(win)
    {
        m_StartEndTextDisplay.SetGameWon(true);
    }
    else
    {
        m_Sounds.m_PacmanDeathSound.play();
        m_StartEndTextDisplay.SetGameLost(true);
    }

    m_Scene.update();

    m_GameState = GameState::GameStopped;
}

void GameWindow::CheckCollisionWithGhost()
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
            m_Ghost1.SetGhostX(Ghost::STARTING_X);
            m_Ghost1.SetGhostY(252);
            m_Ghost1.SetIsScared(false);
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost2) && m_Ghost2.GetIsScared())
        {
            m_Sounds.m_EatGhostSound.play();
            m_Score+=200;
            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));
            m_Ghost2.SetGhostX(Ghost::STARTING_X);
            m_Ghost2.SetGhostY(252);
            m_Ghost2.SetIsScared(false);
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost3) && m_Ghost3.GetIsScared())
        {
            m_Sounds.m_EatGhostSound.play();
            m_Score+=200;
            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));
            m_Ghost3.SetGhostX(Ghost::STARTING_X);
            m_Ghost3.SetGhostY(252);
            m_Ghost3.SetIsScared(false);
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost4) && m_Ghost4.GetIsScared())
        {
            m_Sounds.m_EatGhostSound.play();
            m_Score+=200;
            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));
            m_Ghost4.SetGhostX(Ghost::STARTING_X);
            m_Ghost4.SetGhostY(252);
            m_Ghost4.SetIsScared(false);
        }
        else
        {
            m_Timer.stop();
            m_GhostsTimer.stop();
            EndGame(false);
        }
    }
}

void GameWindow::CheckCollisionWithFoodball()
{
    QPoint pacmanPosition(m_Pacman.GetPacX(), m_Pacman.GetPacY());

    for(int i=0;i<m_FoodballPositions.size();i++)
    {
        if(pacmanPosition == m_FoodballPositions.at(i))
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
}

void GameWindow::CheckCollisionWithPowerball()
{
    QPoint pacmanPosition(m_Pacman.GetPacX(), m_Pacman.GetPacY());

    for(int i=0;i<m_PowerballPositions.size();i++)
    {
        if(pacmanPosition == m_PowerballPositions.at(i))
        {
            m_PowerballPositions.remove(i);
            m_PowerballGraphicalItemsTable.at(i)->hide();
            m_PowerballGraphicalItemsTable.remove(i);

            m_Score += 100;
            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));

            Ghost::SetAllGhostsScareState(0);

            m_Ghost1.SetIsScared(true);
            m_Ghost2.SetIsScared(true);
            m_Ghost3.SetIsScared(true);
            m_Ghost4.SetIsScared(true);

            Ghost::SetAllGhostsScared(true);

            m_pScoreDisplay->setPlainText("Score: " + QString::number(m_Score));
        }
    }
}

void GameWindow::Updater()
{
    /*Changes position of pacman*/
    m_Pacman.Move();

    if(m_CollisionWithGhostDetectionDelay >= 500)
    {
        CheckCollisionWithGhost();
    }
    else
    {
        m_CollisionWithGhostDetectionDelay++;
    }

    CheckCollisionWithFoodball();

    CheckCollisionWithPowerball();

    if(m_FoodballItemsCount==0)
    {
        m_Timer.stop();
        m_GhostsTimer.stop();
        EndGame(true);
    }

    if(Ghost::GetAllGhostsScared())
    {
        Ghost::IncrementAllGhostsScareState();

        if(Ghost::GetAllGhostsScareState()==1)
        {
            m_GhostsTimer.setInterval(50);
        }

        if(Ghost::GetAllGhostsScareState()==750)
        {
            m_Ghost1.SetScaredWhite(true);
            m_Ghost2.SetScaredWhite(true);
            m_Ghost3.SetScaredWhite(true);
            m_Ghost4.SetScaredWhite(true);
        }

        if(Ghost::GetAllGhostsScareState()==1000)
        {
            Ghost::SetAllGhostsScared(false);

            m_Ghost1.SetIsScared(false);
            m_Ghost2.SetIsScared(false);
            m_Ghost3.SetIsScared(false);
            m_Ghost4.SetIsScared(false);

            m_Ghost1.SetScaredWhite(false);
            m_Ghost2.SetScaredWhite(false);
            m_Ghost3.SetScaredWhite(false);
            m_Ghost4.SetScaredWhite(false);

            Ghost::SetAllGhostsScareState(0);
            m_GhostsTimer.setInterval(4);
        }
    }

    m_Pacman.AdvanceAnimation();
    m_Ghost1.AdvanceAnimation();
    m_Ghost2.AdvanceAnimation();
    m_Ghost3.AdvanceAnimation();
    m_Ghost4.AdvanceAnimation();

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

    if(Ghost::GetAllGhostsStartedFreeMovement())
    {
        m_Ghost1.Move();
        m_Ghost2.Move();
        m_Ghost3.Move();
        m_Ghost4.Move();
    }
    else
    {
        if(!m_Ghost1.GetGhostStartedFreeMovement())
        {
            m_Ghost1.MoveInStartingRect();
        }
        else
        {
            m_Ghost1.Move();
        }

        if(!m_Ghost2.GetGhostStartedFreeMovement())
        {
            m_Ghost2.MoveInStartingRect();
        }
        else
        {
            m_Ghost2.Move();
        }

        if(!m_Ghost3.GetGhostStartedFreeMovement())
        {
            m_Ghost3.MoveInStartingRect();
        }
        else
        {
            m_Ghost3.Move();
        }

        if(!m_Ghost4.GetGhostStartedFreeMovement())
        {
            m_Ghost4.MoveInStartingRect();
        }
        else
        {
            m_Ghost4.Move();
        }

        /*Substitute of timer implemented for every ghost to differentiate their start time*/
        if(m_Ghost1.GetGhostX()==300 ||
                m_Ghost2.GetGhostX()==300 ||
                m_Ghost3.GetGhostX()==300 ||
                m_Ghost4.GetGhostX()==300)
        {
            Ghost::IncrementGhostsStartTimer();
        }

        /*Ghost 1 starts*/
        if(Ghost::GetGhostsStartTimer()>=3)
        {
            if(m_Ghost1X>Ghost::STARTING_X)
            {
                m_Ghost1X-=1;
            }
            else if(m_Ghost1X<Ghost::STARTING_X)
            {
                m_Ghost1X+=1;
            }

            if(!m_Ghost1.GetGhostStartedFreeMovement())
            {
                m_Ghost1Y-=1;
                m_Ghost1.SetGhostX(m_Ghost1X);
                m_Ghost1.SetGhostY(m_Ghost1Y);

                QPoint point(m_Ghost1X, m_Ghost1Y);

                if(m_PacMap.GetPathPoints().contains(point))
                {
                    m_Ghost1.SetGhostStartedFreeMovement(true);
                }
            }
        }

        /*Ghost 2 starts*/
        if(Ghost::GetGhostsStartTimer()>=6)
        {
            if(m_Ghost2X>Ghost::STARTING_X)
            {
                m_Ghost2X-=1;
            }
            else if(m_Ghost2X<Ghost::STARTING_X)
            {
                m_Ghost2X+=1;
            }

            if(!m_Ghost2.GetGhostStartedFreeMovement())
            {
                m_Ghost2Y-=1;
                m_Ghost2.SetGhostX(m_Ghost2X);
                m_Ghost2.SetGhostY(m_Ghost2Y);

                QPoint point(m_Ghost2X, m_Ghost2Y);

                if(m_PacMap.GetPathPoints().contains(point))
                {
                    m_Ghost2.SetGhostStartedFreeMovement(true);
                }
            }
        }

        /*Ghost 3 starts*/
        if(Ghost::GetGhostsStartTimer()>=9)
        {
            if(m_Ghost3X>Ghost::STARTING_X)
            {
                m_Ghost3X-=1;
            }
            else if(m_Ghost3X<Ghost::STARTING_X)
            {
                m_Ghost3X+=1;
            }

            if(!m_Ghost3.GetGhostStartedFreeMovement())
            {
                m_Ghost3Y-=1;
                m_Ghost3.SetGhostX(m_Ghost3X);
                m_Ghost3.SetGhostY(m_Ghost3Y);

                QPoint point(m_Ghost3X, m_Ghost3Y);

                if(m_PacMap.GetPathPoints().contains(point))
                {
                    m_Ghost3.SetGhostStartedFreeMovement(true);
                }
            }
        }

        /*Ghost 4 starts*/
        if(Ghost::GetGhostsStartTimer()>=12)
        {
            if(m_Ghost4X>Ghost::STARTING_X)
            {
                m_Ghost4X-=1;
            }
            else if(m_Ghost4X<Ghost::STARTING_X)
            {
                m_Ghost4X+=1;
            }

            if(!m_Ghost4.GetGhostStartedFreeMovement())
            {
                m_Ghost4Y-=1;
                m_Ghost4.SetGhostX(m_Ghost4X);
                m_Ghost4.SetGhostY(m_Ghost4Y);

                QPoint point(m_Ghost4X, m_Ghost4Y);

                if(m_PacMap.GetPathPoints().contains(point))
                {
                    m_Ghost4.SetGhostStartedFreeMovement(true);
                }
            }
        }

        if(m_Ghost1.GetGhostStartedFreeMovement()&&
                m_Ghost2.GetGhostStartedFreeMovement()&&
                m_Ghost3.GetGhostStartedFreeMovement()&&
                m_Ghost4.GetGhostStartedFreeMovement())
        {
            Ghost::SetAllGhostsStartedFreeMovement(true);
        }
    }
}

GameWindow::~GameWindow()
{
    delete m_pUi;
}

/*Supports pacman movement using WSAD and directional keys*/
void GameWindow::keyPressEvent(QKeyEvent *event)
{
    Direction nextDirection =m_Pacman.GetNextDirection();

    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_A:
        nextDirection=Direction::left;
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        nextDirection=Direction::right;
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
        nextDirection=Direction::down;
        break;

    case Qt::Key_Up:
    case Qt::Key_W:
        nextDirection=Direction::up;
        break;

    case Qt::Key_Space:
        if(m_GameState == GameState::BeforeFirstRun)
        {
            StartGame();
        }
        if(m_GameState == GameState::GameStopped)
        {
            RestartGame();
        }
        break;
    default:
        break;
    }

    m_Pacman.SetNextDirection(nextDirection);
}
