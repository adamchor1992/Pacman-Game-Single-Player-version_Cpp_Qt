#ifndef DIALOG_H
#define DIALOG_H

#include "map.h"
#include "pacman.h"
#include "powerball.h"
#include "foodball.h"
#include "ghost.h"
#include "textstartend.h"
#include "sounds.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QMediaPlayer>
#include <QGraphicsScene>

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
    void PopulateMap();
    void GenerateAndPopulateMap();
    void GenerateAndPlacePacman();
    void GenerateAndPlaceGhosts();
    void ResetMap();
    void ResetPacman();
    void ResetGhosts();
    void ShowScore();
    void StartGame();
    void RestartGame();
    void HideSceneItems();
    void ClearVariablesAndContainers();
    void PacmanMove();
    void RespawnGhost();
    void CheckCollision();
    void EndGame(int win);
    ~GameWindow();

    void keyPressEvent(QKeyEvent *event);

public slots:
    void Updater();
    void GhostUpdater();

private:
    Ui::GameWindow *m_pUi;
    QGraphicsScene m_Scene;
    TextStartEnd m_TextStartEnd;
    QTimer m_Timer;
    QTimer m_GhostsTimer;
    Map m_PacMap;
    PowerBall m_Powerball;
    FoodBall m_Foodball;
    Pacman m_Pacman;
    Ghost m_Ghost1;
    Ghost m_Ghost2;
    Ghost m_Ghost3;
    Ghost m_Ghost4;
    Sounds m_Sounds;
    int m_Score;
    int m_FoodballItemsCount;
    int m_CollisionDetectionDelay;
    int m_ScareState;
    bool m_ReadyToRestart;
    bool m_Playing;
    QVector<QPoint> m_PowerballPositions;
    QVector<QPoint> m_FoodballPositions;
    QGraphicsPixmapItem* m_pMapItem;
    QVector<QGraphicsEllipseItem*> m_FoodballGraphicalItemsTable;
    QVector<QGraphicsEllipseItem*> m_PowerballGraphicalItemsTable;
    QGraphicsTextItem* m_pScoreDisplay;
    QGraphicsTextItem* m_pLivesDisplay;
    QMediaPlayer* m_pBeginningSound;
    QMediaPlayer* m_pEatSound1;
    QMediaPlayer* m_pEatSound2;
    QMediaPlayer* m_pEatGhostSound;
    QMediaPlayer* m_pPacmanDeathSound;
    void InitializeGameplayAreaScene();
};

#endif // DIALOG_H
