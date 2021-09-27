#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include "Stone.h"
#include <QMouseEvent>
#include "Step.h"
#include <QVector>
#include <QMessageBox>
#include <QDebug>

/* Board size */
#define OFF_SET 80
#define GRID_WIDTH 60
#define STONE_RADIUS 25

/* Step limitations */
#define MAX_STEPS 100

QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE


class Board : public QWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);
    ~Board();

    /* Result */
    enum RESULT{RED_WIN, TIE, RED_LOSE};

    /* Game data */
    Stone _st[16];//stone 0-7Red 8-15Black
    struct{int row;int col; }TrapPos[6]={
    {2, 0}, {3, 1}, {4, 0},
    {2, 8}, {3, 7}, {4, 8}
    };  //trap position
    struct{int row;int col; }RiverPos[12]={
    {1, 3}, {1, 4}, {1, 5},
    {2, 3}, {2, 4}, {2, 5},
    {4, 3}, {4, 4}, {4, 5},
    {5, 3}, {5, 4}, {5, 5},
    };  //river position
    bool _isRedSide;    //which side -- not using when in singleGameMode

    RESULT _result;

    /* Game status */
    int _selectId;  //stone selected by mouse
    bool _isRedTurn;    //whose turn
    int _stepNum;   //how many steps has taken
    QVector<Step*> _steps;

    /* status functions */
    void init(bool chooseRedSide);

    /* Paint board */
    void paintEvent(QPaintEvent* event);//paint the board
    void drawField(QPainter&Pter);
    void drawLines(QPainter&Pter);
    void drawRiver(QPainter&Pter);
    void drawDen(QPainter&Pter);
    void drawDiagonal(QPainter&Pter, int row, int col);
    void drawTrap(QPainter&Pter);
    void drawStone(QPainter& Pter, int id);//draw the stone
    void drawStones(QPainter& Pter);

    /* Position functions */
    QPoint posInBoard(int row, int col);
    QPoint posInBoard(int id);

    /* Move the stone */
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void click(QPoint pt);
    virtual void click(int id, int row, int col);
    void trySelectStone(int id);
    void tryMoveStone(int id, int row, int col);
    void moveStone(int moveId, int row, int col);   //move selected stone
    void saveStep(int moveId, int killId, int row, int col, QVector<Step*>& steps);
    bool getRowCol(QPoint&pt, int &row, int &col);
    bool hasStone(int row, int col, int &sid);

    void backOneStep();
    void back(Step* step);
    virtual void back();

    void killStone(int killId);
    void reliveStone(int saveId);

    /* Rules */

    bool canMove(int moveId, int row, int col, int killId);
    bool canMoveElephant(int moveId, int row, int col, int killId);
    bool canMoveLion(int moveId, int row, int col, int killId);
    bool canMoveTiger(int moveId, int row, int col, int killId);
    bool canMoveLeopard(int moveId, int row, int col, int killId);
    bool canMoveWolf(int moveId, int row, int col, int killId);
    bool canMoveDog(int moveId, int row, int col, int killId);
    bool canMoveCat(int moveId, int row, int col, int killId);
    bool canMoveMouse(int moveId, int row, int col, int killId);

    static bool (Board::*canMoveFunc[8])(int, int, int, int);

    bool canJumpRiver(int moveId, int row, int col);  //tiger and lion can jump over the river except that mouse is on the line
    bool hasStoneType(int row, int col, Stone::TYPE type);

    bool isInRiver(int row, int col);
    bool isInTrap(int row, int col);
    bool isInDen(int row, int col);

    bool isGameOver();
    bool isAllDead(bool isRed); //1---red, 0---black
    bool isAllCannotMove(bool isRed); //1---red, 0---black

    /* Result hint */
    void showResult();

public slots:
    void slotBack();

private:
    Ui::Board *ui;
};
#endif // BOARD_H
