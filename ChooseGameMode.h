#ifndef CHOOSEGAMEMODE_H
#define CHOOSEGAMEMODE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>

class ChooseGameMode : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseGameMode(QWidget *parent = 0);
    ~ChooseGameMode();

    QPushButton* _buttons[4];
    int _selected;
signals:

public slots:
    void slotClicked();
};

#endif // CHOOSEGAMEMODE_H
