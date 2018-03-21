#include "Game_window.h"
#include "ui_Game_window.h"
#include "map.h"

#include <QGraphicsScene>

Game_window::Game_window(QWidget *parent) : QDialog(parent),ui(new Ui::Game_window)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->gameplay_area->setScene(scene);
    scene->setSceneRect(0,0,614,740);
    ui->gameplay_area->setSceneRect(scene->sceneRect());

    pac_map=new Map;

    scene->addPixmap(pac_map->map_background_picture);
}

Game_window::~Game_window()
{
    delete ui;
    delete pac_map;
    delete scene;
}
