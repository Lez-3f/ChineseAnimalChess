#include "ChooseGameMode.h"

ChooseGameMode::ChooseGameMode(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->addWidget(_buttons[0] = new QPushButton("play with Computer"));
    lay->addWidget(_buttons[1] = new QPushButton("play with yourself"));
    lay->addWidget(_buttons[2] = new QPushButton("online battle(server)"));
    lay->addWidget(_buttons[3] = new QPushButton("online battle(client)"));

    for(int i=0; i<4; ++i)
    {
        connect(_buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
    }
}

void ChooseGameMode::slotClicked()
{
    QObject* s = sender();
    for(int i=0; i<4; ++i)
    {
        if(_buttons[i] == s)
        {
            this->_selected = i;
            break;
        }
    }
    accept();
}

ChooseGameMode::~ChooseGameMode()
{

}
