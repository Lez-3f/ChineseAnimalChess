#include "MultiGameMode.h"

MultiGameMode::MultiGameMode(QWidget *parent) : Board(parent)
{
    init(qrand() % 2);
}
