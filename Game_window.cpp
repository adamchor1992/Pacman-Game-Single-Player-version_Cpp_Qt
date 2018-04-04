#include "Game_window.h"
#include "ui_Game_window.h"
#include "map.h"
#include <QGraphicsScene>

Game_window::Game_window(QWidget *parent) : QDialog(parent),ui(new Ui::Game_window)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->gameplay_area->setScene(scene);
    ui->gameplay_area->setRenderHint(QPainter::Antialiasing);

    scene->setSceneRect(0,0,614,740);
    ui->gameplay_area->setSceneRect(scene->sceneRect());

    pac_map=new Map;

    scene->addPixmap(pac_map->map_background_picture);
    StartGame();
}

void Game_window::StartGame()
{
    pac_man=new Pacman();

    pac_x=320;
    pac_y=514;

    scene->addItem(pac_man);

    direction=1;    //pacman moves left after game start

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,SLOT(updater()));
    timer->start(4);

    this->setFocus(); //gives the keyboard input focus to this widget
}

void Game_window::PacmanMove()
{
    QPoint p;

    if(nextdirection!=direction)
    {
        switch(nextdirection)
        {
        case 1: //left
            p.setX(pac_x-1);
            p.setY(pac_y);

            if(pac_map->IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 2: //up
            p.setX(pac_x);
            p.setY(pac_y-1);
            if(pac_map->IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 3: //down
            p.setX(pac_x);
            p.setY(pac_y+1);
            if(pac_map->IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 4: //right
            p.setX(pac_x+1);
            p.setY(pac_y);
            if(pac_map->IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;
        }
    }

    switch(direction)
    {
    case 1: //left
        p.setX(pac_x-1);
        p.setY(pac_y);
        pac_man->SetDirection(direction);

        if(pac_map->IsPointAvailable(p))
        {
            pac_x = pac_x - 1;
        }

        break;

    case 2: //up
        p.setX(pac_x);
        p.setY(pac_y-1);
        pac_man->SetDirection(direction);

        if(pac_map->IsPointAvailable(p))
        {
            pac_y= pac_y - 1;
        }

        break;

    case 3: //down
        p.setX(pac_x);
        p.setY(pac_y+1);
        pac_man->SetDirection(direction);

        if(pac_map->IsPointAvailable(p))
        {
            pac_y= pac_y + 1;
        }

        break;

    case 4: //right
        p.setX(pac_x+1);
        p.setY(pac_y);
        pac_man->SetDirection(direction);

        if(pac_map->IsPointAvailable(p))
        {
            pac_x = pac_x + 1;
        }

        break;
    }

    if(pac_x==0 && pac_y==318) //teleportation when reached left boundary of middle horizontal line
    {
        pac_x=613;
    }

    if(pac_x==614 && pac_y==318) //teleportation when reached right boundary of middle horizontal line
    {
        pac_x=1;
    }

    pac_man->SetPacX(pac_x);
    pac_man->SetPacY(pac_y);
}

void Game_window::keyPressEvent(QKeyEvent *event) //supports pacman movement using WSAD and directional keys
{
    switch(event->key())
    {
    case Qt::Key_Left:
        nextdirection=1;
        break;
    case Qt::Key_A:
        nextdirection=1;
        break;

    case Qt::Key_Right:
        nextdirection=4;
        break;
    case Qt::Key_D:
        nextdirection=4;
        break;

    case Qt::Key_Down:
        nextdirection=3;
        break;
    case Qt::Key_S:
        nextdirection=3;
        break;

    case Qt::Key_Up:
        nextdirection=2;
        break;
    case Qt::Key_W:
        nextdirection=2;
        break;

    default:
        break;
    }
}

void Game_window::updater()
{
    PacmanMove();                          //changes position of pacman
    scene->update(pac_map->boundingRect()); //redraws objects visible on map
}

Game_window::~Game_window()
{
    delete ui;
    delete pac_map;
    delete scene;
}
