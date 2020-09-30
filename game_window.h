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
    void GameTick();
    void GhostUpdater();

private:    
    const int NORMAL_MOVABLE_CHARACTER_SPEED = 4;
    const int SCARED_GHOST_SPEED = 50;

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
    QGraphicsPixmapItem* m_pMapItem = nullptr;

    Sounds m_Sounds;
    QTimer m_GameTickTimer;
    QTimer m_GhostsTimer;

    std::vector<std::unique_ptr<Foodball>> m_FoodballGraphicalItems;
    std::vector<std::unique_ptr<Powerball>> m_PowerballGraphicalItems;

    GameState m_GameState;

    void InitializeGameplayAreaScene();
    void PrepareFirstGameRun();
    void PopulateMapWithBalls();
    void AddGraphicalItemsToScene();

    void StartGame();
    void EndGame(GameResult gameResult);
    void HideSceneItems();
    void ClearContainers();

    void CheckCollisionWithGhost();
    void CheckCollisionWithFoodball();
    void CheckCollisionWithPowerball();

    void keyPressEvent(QKeyEvent *event) override;
};
