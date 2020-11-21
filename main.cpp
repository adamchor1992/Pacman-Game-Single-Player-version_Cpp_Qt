#include "game_window.h"
#include <QApplication>
#include "log_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogManager::ActivateLogging();

    GameWindow gameWindow;
    gameWindow.show();

    QApplication::exec();

    return 0;
}
