#include "GameWnd.h"

GameWnd::GameWnd(int gameMode, QWidget *parent) : QWidget(parent)
{
    _gameMode = gameMode;

       if(_gameMode == 0)
       {
           SingleGameMode* game = new SingleGameMode;
           CtrlPanel* panel = new CtrlPanel;

           QHBoxLayout* hLay = new QHBoxLayout(this);
           hLay->addWidget(game, 1);
           hLay->addWidget(panel);
           connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
       }
       else if(_gameMode == 1)
       {
           MultiGameMode* game = new MultiGameMode;
           CtrlPanel* panel = new CtrlPanel;

           QHBoxLayout* hLay = new QHBoxLayout(this);
           hLay->addWidget(game, 1);
           hLay->addWidget(panel);
           connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
       }
       else if(_gameMode == 2)
       {
           NetWorkGameMode* game = new NetWorkGameMode(true);
           CtrlPanel* panel = new CtrlPanel;

           QHBoxLayout* hLay = new QHBoxLayout(this);
           hLay->addWidget(game, 1);
           hLay->addWidget(panel);
           connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
       }
       else if(_gameMode == 3)
       {
           NetWorkGameMode* game = new NetWorkGameMode(false);
           CtrlPanel* panel = new CtrlPanel;

           QHBoxLayout* hLay = new QHBoxLayout(this);
           hLay->addWidget(game, 1);
           hLay->addWidget(panel);
           connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
       }
}
