#ifndef ABOUTWND_H
#define ABOUTWND_H

#include <QWidget>

namespace Ui {
class AboutWnd;
}

class AboutWnd : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWnd(QWidget *parent = nullptr);
    ~AboutWnd();

private:
    Ui::AboutWnd *ui;
};

#endif // ABOUTWND_H
