#ifndef SINGLEGAMEMODE_H
#define SINGLEGAMEMODE_H

#include "Board.h"
#include <QTimer>
#include <QDebug>

class SingleGameMode : public Board
{
    Q_OBJECT
public:
    SingleGameMode(QWidget *parent = 0);

    int _level; //电脑考虑的层次

    void back();    //悔棋--人机模式
    void click(int id, int row, int col);

    Step* getBestMove();
    void getAllPossibleMove(QVector<Step*>& steps);
    int getMinScore(int level, int curMin);
    int getMaxScore(int level, int curMax);
    int calScore();

    void attemptMove(Step* step);
    void recoverAttemptMove(Step* step);

public slots:
    void computerMove();
};

#endif // SINGLEGAMEMODE_H
