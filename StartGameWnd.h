#ifndef STARTGAMEWND_H
#define STARTGAMEWND_H

#include <QMainWindow>
#include <QLabel>
#include <QtGui>
#include <QImage>
#include <QPixmap>
#include "GameWnd.h"
#include "AboutWnd.h"

namespace Ui {
class StartGameWnd;
}

class StartGameWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartGameWnd(QWidget *parent = nullptr);
    ~StartGameWnd();

    int _gameMode;

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::StartGameWnd *ui;
};

#endif // STARTGAMEWND_H
