#ifndef CTRLPANEL_H
#define CTRLPANEL_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>

class CtrlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CtrlPanel(QWidget *parent = nullptr);

    QPushButton* _back;

signals:
    void sigBack();
};

#endif // CTRLPANEL_H
