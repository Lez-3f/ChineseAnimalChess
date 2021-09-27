#include "SingleGameMode.h"

SingleGameMode::SingleGameMode(QWidget *parent) : Board(parent)
{
    _level = 4;
}

void SingleGameMode::back()
{
    if(_isRedTurn)
    {
        backOneStep();
        backOneStep();
    }
}

void SingleGameMode::click(int id, int row, int col)
{
    if(_isRedTurn)
    {
        Board::click(id, row, col);

        if(!_isRedTurn)
        {
            QTimer::singleShot(100, this, SLOT(computerMove()));
        }
    }
}

Step* SingleGameMode::getBestMove()
{
    Step* ret = NULL;
    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int maxInAllMinScore = -300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();

        attemptMove(step);
        int minScore = getMinScore(this->_level-1, maxInAllMinScore);
        recoverAttemptMove(step);

        if(minScore > maxInAllMinScore)
        {
            if(ret) delete ret;

            ret = step;
            maxInAllMinScore = minScore;
        }
        else
        {
            delete step;
        }
    }

    qDebug() << maxInAllMinScore;

    return ret;
}

void SingleGameMode::getAllPossibleMove(QVector<Step*>& steps)
{
    int initIndex = (_isRedTurn) ? 0 : 8;

    for(int i= initIndex ;i < initIndex + 8; ++i)
    {
        if(this->_st[i]._dead) continue;
        for(int row = 0; row< 7; ++row)
        {
            for(int col = 0; col < 9; ++col)
            {
                int killid = -1;
                hasStone(row, col, killid);
                if(killid != -1 && _st[i]._red == _st[killid]._red) continue;

                 if(canMove(i,  row, col, killid))  //attention to parameter
                 {
                    saveStep(i, killid, row, col, steps);
                 }
            }
        }
    }
}

int SingleGameMode::getMinScore(int level, int curMin)
{
    if(level == 0){
        return calScore();
    }

    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int minInAllMaxScore = 300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();

        attemptMove(step);
        int maxScore = getMaxScore(level-1, minInAllMaxScore);
        recoverAttemptMove(step);
        delete step;

        if(maxScore <= curMin)
        {
            while(steps.count())
            {
                Step* step = steps.last();
                steps.removeLast();
                delete step;
            }
            return maxScore;
        }

        if(maxScore < minInAllMaxScore)
        {
            minInAllMaxScore = maxScore;
        }


    }
    return minInAllMaxScore;
}

int SingleGameMode::getMaxScore(int level, int curMax)
{
    if(level == 0){
        return calScore();
    }

    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int maxInAllMinScore = -300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();

        attemptMove(step);
        int minScore = getMinScore(level-1, maxInAllMinScore);
        recoverAttemptMove(step);
        delete step;

        if(minScore >= curMax)
        {
            while(steps.count())
            {
                Step* step = steps.last();
                steps.removeLast();
                delete step;
            }
            return minScore;
        }
        if(minScore > maxInAllMinScore)
        {
            maxInAllMinScore = minScore;
        }


    }
    return maxInAllMinScore;
}

int SingleGameMode::calScore()
{
    static int s[] = {64, 32, 16, 8, 4, 2, 1, 4};
    int scoreBlack = 0;
    int scoreRed = 0;
    for(int i=0; i < 8; ++i)
    {
        if(_st[i]._dead) continue;
        scoreRed += s[_st[i]._type];
    }
    for(int i = 8; i < 16; ++i)
    {
        if(_st[i]._dead) continue;
        scoreBlack += s[_st[i]._type];
    }
    return scoreBlack - scoreRed;
}

void SingleGameMode::attemptMove(Step* step)
{
    killStone(step->_killId);
    moveStone(step->_moveId, step->_rowTo, step->_colTo);
    _isRedTurn  = !_isRedTurn;
}

void SingleGameMode::recoverAttemptMove(Step* step)
{
    reliveStone(step->_killId);
    moveStone(step->_moveId, step->_rowFrom, step->_colFrom);
    _isRedTurn = !_isRedTurn;
}

void SingleGameMode::computerMove()
{
    //Debug
    //qDebug() << QString("%1").arg(canMove(9, 0, 7, -1));

    Step* step = getBestMove();

    //save the steps
    saveStep(step->_moveId, step->_killId, step->_rowTo, step->_colTo, this->_steps);

    //move the stone
    moveStone(step->_moveId, step->_rowTo, step->_colTo);

    //eat the previous stone
    killStone(step->_killId);

    _selectId = -1;
    _isRedTurn = !_isRedTurn;   //change the turn
    ++_stepNum;

    if(isGameOver()){
        exit(0);
    }
    delete step;
    update();
}
