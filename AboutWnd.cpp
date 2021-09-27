#include "AboutWnd.h"
#include "ui_AboutWnd.h"

AboutWnd::AboutWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWnd)
{
    ui->setupUi(this);
}

AboutWnd::~AboutWnd()
{
    delete ui;
}
