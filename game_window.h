#pragma once

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
#include "screen_text_display.h"
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
    ~GameWindow() override;

private slots:
    void Updater();
    void GhostUpdater();

private:    
    Ui::GameWindow* ui;
    QGraphicsScene m_Scene;

    GameMap m_GameMap;
    Pacman m_Pacman;
    Ghost m_Ghost1;
    Ghost m_Ghost2;
    Ghost m_Ghost3;
    Ghost m_Ghost4;
    ScreenTextDisplay m_ScreenTextDisplay;
    ScoreDisplay m_ScoreDisplay;

    Sounds m_Sounds;
    QTimer m_Timer;
    QTimer m_GhostsTimer;

    QGraphicsPixmapItem* m_pMapItem{nullptr};

    std::vector<std::unique_ptr<Foodball>> m_FoodballGraphicalItemsTable;
    std::vector<std::unique_ptr<Powerball>> m_PowerballGraphicalItemsTable;

    GameState m_GameState;

    void InitializeGameplayAreaScene();
    void PrepareFirstGameRun();
    void PopulateMapWithBalls();
    void AddGraphicalItemsToScene();
    void AddPowerballGraphicalItemsToScene();
    void AddFoodballGraphicalItemsToScene();

    void StartGame();
    void EndGame(GameResult gameResult);
    void HideSceneItems();
    void ClearContainers();
    void PacmanMove();

    void CheckCollisionWithGhost();
    void CheckCollisionWithFoodball();
    void CheckCollisionWithPowerball();

    void keyPressEvent(QKeyEvent *event) override;
};
