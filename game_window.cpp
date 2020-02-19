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
    AddGraphicalItemsToScene();

    PopulateMapWithBalls();
}

void GameWindow::PopulateMapWithBalls()
{  
    /*Get generated foodball nad powerball positions from GameMap object*/
    QVector<QPoint> const powerballPositions = m_GameMap.GetPowerballPositions();
    QVector<QPoint> const foodballPositions = m_GameMap.GetFoodballPositions();

    m_FoodballItemsCount=foodballPositions.size();

    int const powerballRadius = 15;

    for(auto powerballPosition : powerballPositions)
    {
        m_PowerballGraphicalItemsTable.push_back(std::make_unique<Powerball>(powerballPosition.x(),
                                                                             powerballPosition.y(),
                                                                             powerballRadius,
                                                                             powerballRadius));
    }

    int const foodballRadius = 7;

    for(auto foodballPosition : foodballPositions)
    {
        m_FoodballGraphicalItemsTable.push_back(std::make_unique<Foodball>(foodballPosition.x(),
                                                                           foodballPosition.y(),
                                                                           foodballRadius,
                                                                           foodballRadius));
    }

    AddPowerballGraphicalItemsToScene();
    AddFoodballGraphicalItemsToScene();
}

void GameWindow::AddGraphicalItemsToScene()
{
    /*Add background map picture*/
    m_pMapItem = m_Scene.addPixmap(m_GameMap.GetMapBackgroundPicture());

    m_Scene.addItem(&m_Pacman);

    m_Scene.addItem(&m_Ghost1);
    m_Scene.addItem(&m_Ghost2);
    m_Scene.addItem(&m_Ghost3);
    m_Scene.addItem(&m_Ghost4);

    m_Scene.addItem(&m_StartEndTextDisplay);
    m_Scene.addItem(&m_ScoreDisplay);
}

void GameWindow::AddPowerballGraphicalItemsToScene()
{
    for(auto& powerballGraphicalItem : m_PowerballGraphicalItemsTable)
    {
        m_Scene.addItem(powerballGraphicalItem.get());
    }
}

void GameWindow::AddFoodballGraphicalItemsToScene()
{
    for(auto& foodballGraphicalItem : m_FoodballGraphicalItemsTable)
    {
        m_Scene.addItem(foodballGraphicalItem.get());
    }
}

void GameWindow::StartGame()
{
    m_StartEndTextDisplay.hide();

    connect(&m_Timer, SIGNAL(timeout()), this,SLOT(Updater()));
    connect(&m_GhostsTimer, SIGNAL(timeout()), this,SLOT(GhostUpdater()));

    m_Sounds.PlayBeginningSound();

    m_Timer.start(4);
    m_GhostsTimer.start(4);

    m_GameState = GameState::GameRunning;

    /*Gives keyboard input focus to this widget*/
    setFocus();
}

void GameWindow::RestartGame()
{
    PopulateMapWithBalls();

    m_Pacman.Reset();
    m_Ghost1.Reset();
    m_Ghost2.Reset();
    m_Ghost3.Reset();
    m_Ghost4.Reset();

    m_pMapItem->show();
    m_Pacman.show();
    m_Ghost1.show();
    m_Ghost2.show();
    m_Ghost3.show();
    m_Ghost4.show();

    m_ScoreDisplay.resetScore();
    m_ScoreDisplay.show();

    m_StartEndTextDisplay.hide();

    m_Sounds.PlayBeginningSound();

    m_Timer.start(4);
    m_GhostsTimer.start(4);

    m_GameState = GameState::GameRunning;

    /*Gives keyboard input focus to this widget*/
    setFocus();
}

void GameWindow::ClearContainers()
{
    m_FoodballGraphicalItemsTable.clear();
    m_PowerballGraphicalItemsTable.clear();
}

void GameWindow::HideSceneItems()
{
    m_pMapItem->hide();
    m_ScoreDisplay.hide();

    m_Pacman.hide();

    m_Ghost1.hide();
    m_Ghost2.hide();
    m_Ghost3.hide();
    m_Ghost4.hide();
}

void GameWindow::EndGame(bool win)
{
    ClearContainers();

    HideSceneItems();

    m_StartEndTextDisplay.show();
    m_StartEndTextDisplay.SetScore(m_ScoreDisplay.getScore());

    if(win)
    {
        m_StartEndTextDisplay.SetGameWon(true);
    }
    else
    {
        m_Sounds.PlayPacmanDeathSound();
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
            m_Sounds.PlayEatGhostSound();
            m_ScoreDisplay.IncreaseScore(200);
            m_Ghost1.Respawn();
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost2) && m_Ghost2.GetIsScared())
        {
            m_Sounds.PlayEatGhostSound();
            m_ScoreDisplay.IncreaseScore(200);
            m_Ghost2.Respawn();
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost3) && m_Ghost3.GetIsScared())
        {
            m_Sounds.PlayEatGhostSound();
            m_ScoreDisplay.IncreaseScore(200);
            m_Ghost3.Respawn();
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost4) && m_Ghost4.GetIsScared())
        {
            m_Sounds.PlayEatGhostSound();
            m_ScoreDisplay.IncreaseScore(200);
            m_Ghost4.Respawn();
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
    auto iter = std::begin(m_FoodballGraphicalItemsTable);

    for (auto& foodballGraphicalItem : m_FoodballGraphicalItemsTable)
    {
        if(m_Pacman.collidesWithItem(foodballGraphicalItem.get()))
        {
            m_FoodballGraphicalItemsTable.erase(iter);

            m_Sounds.PlayEatFoodballSound1();

            m_ScoreDisplay.IncreaseScore(1);

            m_FoodballItemsCount--;

            return;
        }

        ++iter;
    }
}

void GameWindow::CheckCollisionWithPowerball()
{
    auto iter = std::begin(m_PowerballGraphicalItemsTable);

    for (auto& powerballGraphicalItem : m_PowerballGraphicalItemsTable)
    {
        if(m_Pacman.collidesWithItem(powerballGraphicalItem.get()))
        {
            m_PowerballGraphicalItemsTable.erase(iter);

            m_Sounds.PlayEatFoodballSound1();

            Ghost::SetAllGhostsScareState(0);

            m_Ghost1.SetIsScared(true);
            m_Ghost2.SetIsScared(true);
            m_Ghost3.SetIsScared(true);
            m_Ghost4.SetIsScared(true);

            Ghost::SetAllGhostsScared(true);

            m_ScoreDisplay.IncreaseScore(100);

            return;
        }

        ++iter;
    }
}

void GameWindow::Updater()
{
    /*Changes position of pacman*/
    m_Pacman.Move();

    CheckCollisionWithGhost();

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
    int ghost1X = m_Ghost1.GetGhostX();
    int ghost1Y = m_Ghost1.GetGhostY();
    int ghost2X = m_Ghost2.GetGhostX();
    int ghost2Y = m_Ghost2.GetGhostY();
    int ghost3X = m_Ghost3.GetGhostX();
    int ghost3Y = m_Ghost3.GetGhostY();
    int ghost4X = m_Ghost4.GetGhostX();
    int ghost4Y = m_Ghost4.GetGhostY();

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
            m_Ghost1.MoveOutOfTheStartingBox(ghost1X, ghost1Y);
        }

        /*Ghost 2 starts*/
        if(Ghost::GetGhostsStartTimer()>=6)
        {
            m_Ghost2.MoveOutOfTheStartingBox(ghost2X, ghost2Y);
        }

        /*Ghost 3 starts*/
        if(Ghost::GetGhostsStartTimer()>=9)
        {
            m_Ghost3.MoveOutOfTheStartingBox(ghost3X, ghost3Y);
        }

        /*Ghost 4 starts*/
        if(Ghost::GetGhostsStartTimer()>=12)
        {
            m_Ghost4.MoveOutOfTheStartingBox(ghost4X, ghost4Y);
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
