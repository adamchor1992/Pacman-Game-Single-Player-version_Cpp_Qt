#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QMediaPlayer>
#include <QGraphicsScene>

#include "game_map.h"
#include "pacman.h"
#include "powerball.h"
#include "foodball.h"
#include "ghost.h"
#include "start_end_text_display.h"
#include "score_display.h"
#include "sounds.h"

namespace Ui
{
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget* parent = nullptr);
    void GenerateMap();
    void PopulateMapWithBalls();
    void ResetMap();
    void ResetPacman();
    void ResetGhosts();
    void StartGame();
    void RestartGame();
    void HideSceneItems();
    void ClearContainers();
    void PacmanMove();
    void CheckCollisionWithGhost();
    void EndGame(bool win);
    ~GameWindow();

    void keyPressEvent(QKeyEvent *event);

    void MoveOutOfTheStartingBox();

public slots:
    void Updater();
    void GhostUpdater();

private:
    Ui::GameWindow *m_pUi;
    QGraphicsScene m_Scene;

    GameMap m_GameMap;
    Pacman m_Pacman;
    Ghost m_Ghost1;
    Ghost m_Ghost2;
    Ghost m_Ghost3;
    Ghost m_Ghost4;
    StartEndTextDisplay m_StartEndTextDisplay;
    ScoreDisplay m_ScoreDisplay;

    Sounds m_Sounds;
    QTimer m_Timer;
    QTimer m_GhostsTimer;

    int m_FoodballItemsCount;

    QGraphicsPixmapItem* m_pMapItem;

    std::vector<std::unique_ptr<Foodball>> m_FoodballGraphicalItemsTable;
    std::vector<std::unique_ptr<Powerball>> m_PowerballGraphicalItemsTable;

    enum class GameState
    {
        BeforeFirstRun,
        GameRunning,
        GameStopped
    };

    GameState m_GameState;

    void InitializeGameplayAreaScene();
    void PrepareFirstGameRun();
    void CheckCollisionWithFoodball(QPoint& pacmanPosition);
    void CheckCollisionWithPowerball(QPoint& pacmanPosition);
    void CheckCollisionWithFoodball();
    void CheckCollisionWithPowerball();
    void AddGraphicalItemsToScene();
    void MoveOutOfTheStartingBox(Ghost &ghost, int ghostX, int ghostY);
};

#endif // DIALOG_H
