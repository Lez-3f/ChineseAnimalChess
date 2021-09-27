#ifndef GAMEWND_H
#define GAMEWND_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include "SingleGameMode.h"
#include "MultiGameMode.h"
#include "NetWorkGameMode.h"
#include "CtrlPanel.h"

class GameWnd : public QWidget
{
    Q_OBJECT
public:
    explicit GameWnd(int GameMode, QWidget *parent = nullptr);

    int _gameMode;

signals:

};

#endif // GAMEWND_H
