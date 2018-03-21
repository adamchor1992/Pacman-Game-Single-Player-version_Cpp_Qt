#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include "map.h"

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

public:
    explicit Game_window(QWidget *parent = 0);
    Map *pac_map;
    ~Game_window();
};

#endif // DIALOG_H
