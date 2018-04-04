#ifndef DIALOG_H
#define DIALOG_H

#include "map.h"
#include "pacman.h"
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

public:
    explicit Game_window(QWidget *parent = 0);
    void StartGame();
    void PacmanMove();
    Map *pac_map;
    Pacman *pac_man;
    ~Game_window();

public slots:
    void updater();
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // DIALOG_H
