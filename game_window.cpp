#include "game_window.h"
#include "ui_game_window.h"

GameWindow::GameWindow(QWidget* parent) : QDialog(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    /*Gives keyboard input focus to this widget*/
    setFocus(Qt::ActiveWindowFocusReason);

    InitializeGameplayAreaScene();

    PrepareFirstGameRun();
}

void GameWindow::InitializeGameplayAreaScene()
{
    m_Scene.setParent(this);
    ui->m_pGameplayArea->setScene(&m_Scene);
    ui->m_pGameplayArea->setRenderHint(QPainter::Antialiasing);
    m_Scene.setSceneRect(0, 0, 614, 740);
    ui->m_pGameplayArea->setSceneRect(m_Scene.sceneRect());
}

void GameWindow::PrepareFirstGameRun()
{
    m_GameState = GameState::BEFORE_FIRST_RUN;

    AddGraphicalItemsToScene();
    PopulateMapWithBalls();

    connect(&m_GameTickTimer, &QTimer::timeout, this, &GameWindow::GameTick);
    connect(&m_GhostsTimer, &QTimer::timeout, this, &GameWindow::GhostUpdater);
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
    m_Scene.addItem(&m_ScreenTextDisplay);
    m_Scene.addItem(&m_ScoreDisplay);
}

void GameWindow::PopulateMapWithBalls()
{  
    /*Get generated foodball nad powerball positions from GameMap object*/
    const QVector<QPoint> powerballPositions = m_GameMap.GetPowerballPositions();
    const QVector<QPoint> foodballPositions = m_GameMap.GetFoodballPositions();

    /*Create balls graphical items and put them into vector*/
    for(auto& powerballPosition : powerballPositions)
    {
        m_PowerballGraphicalItems.push_back(std::make_unique<Powerball>(powerballPosition.x(),
                                                                        powerballPosition.y()));
    }

    for(auto& foodballPosition : foodballPositions)
    {
        m_FoodballGraphicalItems.push_back(std::make_unique<Foodball>(foodballPosition.x(),
                                                                      foodballPosition.y()));
    }

    /*Add balls graphical items to scene*/
    for(auto& powerballGraphicalItem : m_PowerballGraphicalItems)
    {
        m_Scene.addItem(powerballGraphicalItem.get());
    }

    for(auto& foodballGraphicalItem : m_FoodballGraphicalItems)
    {
        m_Scene.addItem(foodballGraphicalItem.get());
    }
}

void GameWindow::StartGame()
{
    m_Sounds.PlayBeginningSound();

    if(m_GameState != GameState::BEFORE_FIRST_RUN)
    {
        PopulateMapWithBalls();
    }

    m_pMapItem->show();
    m_Pacman.show();
    m_Ghost1.show();
    m_Ghost2.show();
    m_Ghost3.show();
    m_Ghost4.show();

    m_ScoreDisplay.ResetScore();
    m_ScoreDisplay.show();

    m_ScreenTextDisplay.hide();

    m_GameTickTimer.start(NORMAL_MOVABLE_CHARACTER_SPEED);
    m_GhostsTimer.start(NORMAL_MOVABLE_CHARACTER_SPEED);

    m_GameState = GameState::GAME_RUNNING;
}

void GameWindow::ClearContainers()
{
    m_FoodballGraphicalItems.clear();
    m_PowerballGraphicalItems.clear();
}

void GameWindow::HideItems()
{
    m_pMapItem->hide();
    m_ScoreDisplay.hide();
    m_Pacman.hide();
    m_Ghost1.hide();
    m_Ghost2.hide();
    m_Ghost3.hide();
    m_Ghost4.hide();
}

void GameWindow::EndGame(GameResult gameResult)
{
    m_GameTickTimer.stop();
    m_GhostsTimer.stop();

    m_GameState = GameState::GAME_STOPPED;

    ClearContainers();

    HideItems();

    m_Pacman.Reset();
    m_Ghost1.Reset();
    m_Ghost2.Reset();
    m_Ghost3.Reset();
    m_Ghost4.Reset();

    m_ScreenTextDisplay.SetScore(m_ScoreDisplay.GetScore());
    m_ScreenTextDisplay.SetGameResult(gameResult);
    m_ScreenTextDisplay.show();

    if(gameResult == GameResult::GAME_LOST)
    {
        m_Sounds.PlayPacmanDeathSound();
    }

    m_Scene.update();
}

void GameWindow::CheckCollisionWithGhost()
{
    if(m_Pacman.collidesWithItem(&m_Ghost1) ||
            m_Pacman.collidesWithItem(&m_Ghost2) ||
            m_Pacman.collidesWithItem(&m_Ghost3) ||
            m_Pacman.collidesWithItem(&m_Ghost4))
    {
        if(m_Pacman.collidesWithItem(&m_Ghost1) && (m_Ghost1.GetScaredState() == Ghost::ScaredState::SCARED_BLUE || m_Ghost1.GetScaredState() == Ghost::ScaredState::SCARED_WHITE))
        {
            m_Sounds.PlayEatGhostSound();
            m_ScoreDisplay.IncreaseScore(ScoreDisplay::GHOST_KILL_SCORE);
            m_Ghost1.Respawn();
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost2) && (m_Ghost2.GetScaredState() == Ghost::ScaredState::SCARED_BLUE || m_Ghost2.GetScaredState() == Ghost::ScaredState::SCARED_WHITE))
        {
            m_Sounds.PlayEatGhostSound();
            m_ScoreDisplay.IncreaseScore(ScoreDisplay::GHOST_KILL_SCORE);
            m_Ghost2.Respawn();
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost3) && (m_Ghost3.GetScaredState() == Ghost::ScaredState::SCARED_BLUE || m_Ghost3.GetScaredState() == Ghost::ScaredState::SCARED_WHITE))
        {
            m_Sounds.PlayEatGhostSound();
            m_ScoreDisplay.IncreaseScore(ScoreDisplay::GHOST_KILL_SCORE);
            m_Ghost3.Respawn();
        }
        else if(m_Pacman.collidesWithItem(&m_Ghost4) && (m_Ghost4.GetScaredState() == Ghost::ScaredState::SCARED_BLUE || m_Ghost4.GetScaredState() == Ghost::ScaredState::SCARED_WHITE))
        {
            m_Sounds.PlayEatGhostSound();
            m_ScoreDisplay.IncreaseScore(ScoreDisplay::GHOST_KILL_SCORE);
            m_Ghost4.Respawn();
        }
        else
        {
            EndGame(GameResult::GAME_LOST);
        }
    }
}

void GameWindow::CheckCollisionWithFoodball()
{
    auto iter = std::begin(m_FoodballGraphicalItems);

    for (auto& foodballGraphicalItem : m_FoodballGraphicalItems)
    {
        if(m_Pacman.collidesWithItem(foodballGraphicalItem.get()))
        {
            m_FoodballGraphicalItems.erase(iter);

            m_Sounds.PlayEatFoodballSound1();

            m_ScoreDisplay.IncreaseScore(1);

            return;
        }

        ++iter;
    }
}

void GameWindow::CheckCollisionWithPowerball()
{
    auto iter = std::begin(m_PowerballGraphicalItems);

    for (auto& powerballGraphicalItem : m_PowerballGraphicalItems)
    {
        if(m_Pacman.collidesWithItem(powerballGraphicalItem.get()))
        {
            m_PowerballGraphicalItems.erase(iter);

            m_Sounds.PlayEatFoodballSound1();

            Ghost::SetAllGhostsScareState(0);

            m_Ghost1.SetScaredState(Ghost::ScaredState::SCARED_BLUE);
            m_Ghost2.SetScaredState(Ghost::ScaredState::SCARED_BLUE);
            m_Ghost3.SetScaredState(Ghost::ScaredState::SCARED_BLUE);
            m_Ghost4.SetScaredState(Ghost::ScaredState::SCARED_BLUE);

            m_ScoreDisplay.IncreaseScore(100);

            return;
        }

        ++iter;
    }
}

void GameWindow::GameTick()
{
    m_Pacman.Move();

    CheckCollisionWithGhost();

    CheckCollisionWithFoodball();

    CheckCollisionWithPowerball();

    if(m_GameState == GameState::GAME_RUNNING && m_FoodballGraphicalItems.size() == 0)
    {
        EndGame(GameResult::GAME_WIN);
    }

    auto CheckIfGhostsScared = [&](){return (m_Ghost1.GetScaredState() == Ghost::ScaredState::SCARED_BLUE || m_Ghost1.GetScaredState() == Ghost::ScaredState::SCARED_WHITE) ||
                (m_Ghost2.GetScaredState() == Ghost::ScaredState::SCARED_BLUE || m_Ghost2.GetScaredState() == Ghost::ScaredState::SCARED_WHITE) ||
                (m_Ghost3.GetScaredState() == Ghost::ScaredState::SCARED_BLUE || m_Ghost3.GetScaredState() == Ghost::ScaredState::SCARED_WHITE) ||
                (m_Ghost4.GetScaredState() == Ghost::ScaredState::SCARED_BLUE || m_Ghost4.GetScaredState() == Ghost::ScaredState::SCARED_WHITE);};

    if(CheckIfGhostsScared())
    {
        Ghost::IncrementAllGhostsScareState();

        if(Ghost::GetAllGhostsScareState() == 1)
        {
            m_GhostsTimer.setInterval(SCARED_GHOST_SPEED);
        }

        if(Ghost::GetAllGhostsScareState() == Ghost::WHITE_SCARE_STATE_THRESHOLD)
        {
            m_Ghost1.SetScaredState(Ghost::ScaredState::SCARED_WHITE);
            m_Ghost2.SetScaredState(Ghost::ScaredState::SCARED_WHITE);
            m_Ghost3.SetScaredState(Ghost::ScaredState::SCARED_WHITE);
            m_Ghost4.SetScaredState(Ghost::ScaredState::SCARED_WHITE);
        }

        if(Ghost::GetAllGhostsScareState() == Ghost::SCARE_STATE_TIMER_MAX)
        {
            m_Ghost1.SetScaredState(Ghost::ScaredState::NO_SCARED);
            m_Ghost2.SetScaredState(Ghost::ScaredState::NO_SCARED);
            m_Ghost3.SetScaredState(Ghost::ScaredState::NO_SCARED);
            m_Ghost4.SetScaredState(Ghost::ScaredState::NO_SCARED);

            Ghost::SetAllGhostsScareState(0);
            m_GhostsTimer.setInterval(NORMAL_MOVABLE_CHARACTER_SPEED);
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
    int ghost1X = m_Ghost1.GetX();
    int ghost1Y = m_Ghost1.GetY();
    int ghost2X = m_Ghost2.GetX();
    int ghost2Y = m_Ghost2.GetY();
    int ghost3X = m_Ghost3.GetX();
    int ghost3Y = m_Ghost3.GetY();
    int ghost4X = m_Ghost4.GetX();
    int ghost4Y = m_Ghost4.GetY();

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
        if(m_Ghost1.GetX() == 300 ||
                m_Ghost2.GetX() == 300 ||
                m_Ghost3.GetX() == 300 ||
                m_Ghost4.GetX() == 300)
        {
            Ghost::IncrementGhostsStartTimer();
        }

        /*Ghost 1 starts*/
        if(Ghost::GetGhostsStartTimer() >= 3)
        {
            m_Ghost1.MoveOutOfTheStartingBox(ghost1X, ghost1Y);
        }

        /*Ghost 2 starts*/
        if(Ghost::GetGhostsStartTimer() >= 6)
        {
            m_Ghost2.MoveOutOfTheStartingBox(ghost2X, ghost2Y);
        }

        /*Ghost 3 starts*/
        if(Ghost::GetGhostsStartTimer() >= 9)
        {
            m_Ghost3.MoveOutOfTheStartingBox(ghost3X, ghost3Y);
        }

        /*Ghost 4 starts*/
        if(Ghost::GetGhostsStartTimer() >= 12)
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
    delete ui;
}

/*Supports pacman movement using WSAD and directional keys*/
void GameWindow::keyPressEvent(QKeyEvent *event)
{
    Direction nextDirection =m_Pacman.GetNextDirection();

    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_A:
        nextDirection=Direction::LEFT;
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        nextDirection=Direction::RIGHT;
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
        nextDirection=Direction::DOWN;
        break;

    case Qt::Key_Up:
    case Qt::Key_W:
        nextDirection=Direction::UP;
        break;

    case Qt::Key_Space:
        if(m_GameState == GameState::BEFORE_FIRST_RUN || m_GameState == GameState::GAME_STOPPED)
        {
            StartGame();
        }
        break;

    default:
        break;
    }

    m_Pacman.SetNextDirection(nextDirection);
}
