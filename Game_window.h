#ifndef DIALOG_H
#define DIALOG_H

#include "map.h"
#include "pacman.h"
#include "powerball.h"
#include "foodball.h"
#include "ghost.h"
#include "textstartend.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui
{
class Game_window;
}

class Game_window : public QDialog
{
    Q_OBJECT

private:
    Ui::Game_window *ui;
    QGraphicsScene *scene;
    TextStartEnd *text_start_end;
    QTimer *timer;
    QTimer *ghoststimer;
    Map *pac_map;
    PowerBall *power_ball;
    FoodBall *food_ball;
    Pacman *pac_man;
    Ghost *ghost1;
    Ghost *ghost2;
    Ghost *ghost3;
    Ghost *ghost4;

    bool playing;

    int score;
    int foodball_items_count;
    int collision_detection_delay;
    bool all_ghosts_started;
    bool scared;
    int scarestate;
    bool moving,ghostmoving1,ghostmoving2,ghostmoving3,ghostmoving4;
    bool ghoststart1,ghoststart2,ghoststart3,ghoststart4;
    int start_timer;
    bool start;

    QVector<QPoint> *powerball_positions;
    QVector<QPoint> *foodball_positions;

    QGraphicsPixmapItem *map_item;

    QGraphicsEllipseItem powerball_items;
    QGraphicsEllipseItem foodball_items;

    QVector<QGraphicsEllipseItem*> foodball_graphical_items_table;
    QVector<QGraphicsEllipseItem*> powerball_graphical_items_table;

    QGraphicsTextItem *score_display;
    QGraphicsTextItem *lives_display;

public:
    explicit Game_window(QWidget *parent = 0);
    void GenerateAndPopulateMap();
    void GenerateAndPlacePacman();
    void GenerateAndPlaceGhosts();
    void ShowScoresAndLives();

    void GhostMove1();
    void GhostMove2();
    void GhostMove3();
    void GhostMove4();
    void MoveGhostInStartingRect1();
    void MoveGhostInStartingRect2();
    void MoveGhostInStartingRect3();
    void MoveGhostInStartingRect4();
    void StartGame();
    void PacmanMove(); 
    void RespawnGhost();
    void CheckCollision();
    void EndGame(int win);

    ~Game_window();

public slots:
    void updater();
    void ghostupdater();

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // DIALOG_H
