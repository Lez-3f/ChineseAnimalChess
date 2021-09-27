#include "StartGameWnd.h"
#include "ChooseGameMode.h"
#include "ui_StartGameWnd.h"
#include<QDebug>

StartGameWnd::StartGameWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartGameWnd)
{
    ui->setupUi(this);

    QImage img = QImage(":/image/gaitubao_leopard_png.png");
    QPixmap pixmap = QPixmap::fromImage(img);
    pixmap.scaled(QSize(ui->label->width(),ui->label->height()),Qt::KeepAspectRatioByExpanding);
    ui->label->setPixmap(pixmap);
    ui->label->show();

    this->_gameMode = -1;
}

StartGameWnd::~StartGameWnd()
{
    delete ui;
}

void StartGameWnd::on_pushButton_1_clicked()
{
    ChooseGameMode chmDlg(this);
    chmDlg.setWindowTitle("Choose game mode");

    if(chmDlg.exec() != QDialog::Accepted)
    {
        return;
    }
    this->_gameMode = chmDlg._selected;

    this->close();
    GameWnd *gWnd = new GameWnd(_gameMode);
    gWnd->setWindowTitle("AnimalChess");
    gWnd->show();

}


void StartGameWnd::on_pushButton_2_clicked()
{
    AboutWnd *aWnd = new AboutWnd;
    aWnd->setWindowTitle("About");
    aWnd->show();
}

