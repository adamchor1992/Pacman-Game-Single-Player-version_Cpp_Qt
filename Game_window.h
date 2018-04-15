#ifndef DIALOG_H
#define DIALOG_H

#include "map.h"
#include "pacman.h"
#include "powerball.h"
#include "foodball.h"
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
    QTimer *timer;
    int direction;
    int nextdirection;
    int pac_x,pac_y;

    int score;
    int foodball_items_count;

    QVector<QPoint> *powerball_positions;
    QVector<QPoint> *foodball_positions;

    QGraphicsEllipseItem powerball_items;
    QGraphicsEllipseItem foodball_items;

    QVector<QGraphicsEllipseItem*> foodball_graphical_items_table;
    QVector<QGraphicsEllipseItem*> powerball_graphical_items_table;

    QGraphicsTextItem *score_display;

public:
    explicit Game_window(QWidget *parent = 0);
    void StartGame();
    void PacmanMove();
    Map *pac_map;
    PowerBall *power_ball;
    FoodBall *food_ball;

    Pacman *pac_man;
    ~Game_window();

public slots:
    void updater();
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // DIALOG_H
