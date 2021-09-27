#include "Board.h"
#include "MultiGameMode.h"
#include "SingleGameMode.h"
#include "StartGameWnd.h"
#include "GameWnd.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    StartGameWnd *startWnd = new StartGameWnd;
    startWnd->setWindowTitle("AnimalChess--getStarted!!!");
    startWnd->show();

    return app.exec();
}
