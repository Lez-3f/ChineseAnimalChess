#include "Board.h"
#include "ui_Board.h"

bool (Board::*Board::canMoveFunc[8])(int, int, int, int) = {&Board::canMoveElephant, &Board::canMoveLion, &Board::canMoveTiger,
        &Board::canMoveLeopard, &Board::canMoveWolf, &Board::canMoveDog, &Board::canMoveCat, &Board::canMoveMouse};


Board::Board(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Board)
{
    ui->setupUi(this);
    setWindowTitle("AnimalChess");

    //init(qrand() % 2);
    init(true);
}

void Board::init(bool chooseRedSide){
    for(int i = 0; i < 16; ++i){
        _st[i].init(i);
    }
    if(chooseRedSide){
        for(int i = 0; i < 16; ++i){
            _st[i].rotate();
        }
    }

    _selectId = -1;
    _isRedTurn = true; //red first as default
    _isRedSide = chooseRedSide;
    _stepNum = 0;

    update();
}

Board::~Board()
{
    delete ui;

    for(auto it = _steps.begin(); it != _steps.end(); ++it)
    {
        delete *it;
    }
}

void Board::paintEvent(QPaintEvent *){

    QPainter Painter(this);

    Painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //Field
    Painter.save();
    drawField(Painter);
    Painter.restore();

    //lines
    Painter.save();
    drawLines(Painter);
    Painter.restore();

    //river
    Painter.save();
    drawRiver(Painter);
    Painter.restore();

    //trap
    Painter.save();
    drawTrap(Painter);
    Painter.restore();

    //Den
    Painter.save();
    drawDen(Painter);
    Painter.restore();

    //Stone
    Painter.save();
    drawStones(Painter);
    Painter.restore();

    //show step number
    ui->StepNumber->display(_stepNum);
}

void Board::drawRiver(QPainter &Painter){

    Painter.setBrush(QColor(0, 200, 255));
    QRect River_l = QRect(OFF_SET + GRID_WIDTH, OFF_SET + 3*GRID_WIDTH, 2*GRID_WIDTH, 3*GRID_WIDTH);
    QRect River_r = QRect(OFF_SET + 4*GRID_WIDTH, OFF_SET + 3*GRID_WIDTH, 2*GRID_WIDTH, 3*GRID_WIDTH);
    Painter.drawRect(River_l);
    Painter.drawRect(River_r);
    Painter.setBrush(Qt::NoBrush);
}

void Board::drawField(QPainter &Painter){
    Painter.setBrush(QColor(0, 255, 0));
    QRect Fd = QRect(OFF_SET, OFF_SET, 7*GRID_WIDTH, 9*GRID_WIDTH);
    Painter.drawRect(Fd);
    Painter.setBrush(Qt::NoBrush);
}

void Board::drawLines(QPainter &Painter){
    for(int i = 0; i < 10; ++i){
        if(i!=4 && i!=5){
            Painter.drawLine(QPoint(OFF_SET, OFF_SET + i*GRID_WIDTH),
                             QPoint(OFF_SET + 7*GRID_WIDTH, OFF_SET + i*GRID_WIDTH));
        }
        else{
            Painter.drawLine(QPoint(OFF_SET, OFF_SET + i*GRID_WIDTH),
                             QPoint(OFF_SET + 1*GRID_WIDTH, OFF_SET + i*GRID_WIDTH));
            Painter.drawLine(QPoint(OFF_SET + 3*GRID_WIDTH, OFF_SET + i*GRID_WIDTH),
                             QPoint(OFF_SET + 4*GRID_WIDTH, OFF_SET + i*GRID_WIDTH));
            Painter.drawLine(QPoint(OFF_SET + 6*GRID_WIDTH, OFF_SET + i*GRID_WIDTH),
                             QPoint(OFF_SET + 7*GRID_WIDTH, OFF_SET + i*GRID_WIDTH));
        }
    }
    for(int i = 0; i < 8; ++i){
        if(i!=2 && i!= 5){
            Painter.drawLine(QPoint(OFF_SET + i*GRID_WIDTH, OFF_SET),
                             QPoint(OFF_SET + i*GRID_WIDTH, OFF_SET + 9*GRID_WIDTH));
        }
        else{
            Painter.drawLine(QPoint(OFF_SET + i*GRID_WIDTH, OFF_SET),
                             QPoint(OFF_SET + i*GRID_WIDTH, OFF_SET + 3*GRID_WIDTH));
            Painter.drawLine(QPoint(OFF_SET + i*GRID_WIDTH, OFF_SET + 6*GRID_WIDTH),
                             QPoint(OFF_SET + i*GRID_WIDTH, OFF_SET + 9*GRID_WIDTH));
        }
    }
}

void Board::drawDen(QPainter &Painter){
    Painter.setBrush(Qt::NoBrush);
    Painter.drawEllipse(posInBoard(3, 0), STONE_RADIUS, STONE_RADIUS);
    Painter.drawEllipse(posInBoard(3, 8), STONE_RADIUS, STONE_RADIUS);
}

void Board::drawStones(QPainter &Painter){
    for(int i = 0; i < 16; ++i){
        drawStone(Painter, i);
    }
}

QPoint Board::posInBoard(int row, int col){
    return QPoint(OFF_SET + row*GRID_WIDTH + 0.5*GRID_WIDTH,
                  OFF_SET + col*GRID_WIDTH + 0.5*GRID_WIDTH);
}

QPoint Board::posInBoard(int id){
    return posInBoard(_st[id]._row, _st[id]._col);
}

void Board::drawStone(QPainter &Pter, int id){
    if(_st[id]._dead){
        return;
    }

    QPoint c = posInBoard(id);
    QRect R = QRect(c.x() - STONE_RADIUS, c.y() - STONE_RADIUS, STONE_RADIUS*2, STONE_RADIUS*2);

    if(_selectId == id){
        Pter.setBrush(QBrush(Qt::lightGray));
    }
    else{
        Pter.setBrush(QBrush(Qt::yellow));
    }

    Pter.setPen(Qt::black);
    Pter.drawEllipse(posInBoard(_st[id]._row, _st[id]._col), STONE_RADIUS, STONE_RADIUS);

    if(_st[id]._red){
        Pter.setPen(Qt::red);
    }
    Pter.setFont(QFont("SimHei", 0.8*STONE_RADIUS, 800));
    Pter.drawText(R, _st[id].getText(), QTextOption(Qt::AlignCenter));

}

void Board::drawDiagonal(QPainter &Pter, int row, int col){
    Pter.drawLine(QPoint(OFF_SET + row*GRID_WIDTH, OFF_SET + col*GRID_WIDTH),
                  QPoint(OFF_SET + (row+1)*GRID_WIDTH, OFF_SET + (col+1)*GRID_WIDTH));
    Pter.drawLine(QPoint(OFF_SET + (row+1)*GRID_WIDTH, OFF_SET + col*GRID_WIDTH),
                  QPoint(OFF_SET + row*GRID_WIDTH, OFF_SET + (col+1)*GRID_WIDTH));
}

void Board::drawTrap(QPainter &Pter){
    for(int i = 0; i < 6; ++i){
        drawDiagonal(Pter, TrapPos[i].row, TrapPos[i].col);
    }
}

bool Board::getRowCol(QPoint&pt, int &row, int &col){
    row = (pt.x() - OFF_SET) / GRID_WIDTH;
    col = (pt.y() - OFF_SET) / GRID_WIDTH;
    if(row < 7 && col < 9){
        return true;
    }
    else{
        return false;
    }
}

bool Board::hasStone(int row, int col, int&selectId){
    for(int i = 0; i < 16; ++i){
        if(_st[i]._row == row && _st[i]._col == col && !_st[i]._dead){
            selectId = i;
            return true;
        }
    }
    return false;
}

void Board::moveStone(int moveId, int row, int col)
{
    //move the stone
    _st[moveId]._row = row;
    _st[moveId]._col = col;
}

void Board::killStone(int killId)
{
    if(killId == -1){
        return;
    }

    _st[killId]._dead = true;
}

void Board::trySelectStone(int clickId)
{
    //try select stone
    if(clickId != -1 && _isRedTurn == _st[clickId]._red){
        _selectId = clickId;
        update();
    }
}

void Board::tryMoveStone(int clickId, int row, int col)
{
    //try move stone
    if(canMove(_selectId, row, col, clickId)){

        //save the steps
        saveStep(_selectId, clickId, row, col, _steps);

        //move the stone
        moveStone(_selectId, row, col);

        //ATTETION : Must save the step before you move the stone

        //eat the previous stone
        killStone(clickId);

        _selectId = -1;
        _isRedTurn = !_isRedTurn;   //change the turn
        ++_stepNum;

        if(isGameOver()){
            exit(0);
        }

        update();
    }
}

void Board::click(int clickId, int row, int col){
    if(_selectId == -1){
        trySelectStone(clickId);
    }
    else{
        tryMoveStone(clickId, row, col);
    }
}

void Board::click(QPoint pt){

    int col = -1, row = -1;
    bool bRet = getRowCol(pt, row, col);
    int clickId = -1;

    if(!bRet){
        return;
    }

    if(hasStone(row, col, clickId)){
        update();
    }

    click(clickId, row, col);
}

void Board::mouseReleaseEvent(QMouseEvent *event){
     QPoint pt = event->pos();

     click(pt);
}

void Board::mousePressEvent(QMouseEvent *){

}

bool Board::canMove(int moveId, int row, int col, int killId){

    //cannot eat the stone with the same color
    if(killId != -1 && _st[moveId]._red == _st[killId]._red){
        _selectId = killId;
        update();
        return false;
    }

    //you dont move
    if(row == _st[moveId]._row && col == _st[moveId]._col ){
        return false;
    }

    //cannot go into your den
    if(_st[moveId]._red && _isRedSide && row == 3 && col == 8){
        return false;
    }
    else if(_st[moveId]._red && !_isRedSide && row == 3 && col == 0){
        return false;
    }
    else if(!_st[moveId]._red && !_isRedSide && row == 3 && col == 8){
        return false;
    }
    else if(_st[moveId]._red && !_isRedSide && row == 3 && col == 0){
        return false;
    }


    switch (_st[moveId]._type) {
    case Stone::ELEPHANT:
        return canMoveElephant(moveId, row, col, killId);
        break;
    case Stone::LION:
        return canMoveLion(moveId, row, col, killId);
        break;
    case Stone::TIGER:
        return canMoveTiger(moveId, row, col, killId);
        break;
    case Stone::LEOPARD:
        return canMoveLeopard(moveId, row, col, killId);
        break;
    case Stone::WOLF:
        return canMoveWolf(moveId, row, col, killId);
        break;
    case Stone::DOG:
        return canMoveDog(moveId, row, col, killId);
        break;
    case Stone::CAT:
        return canMoveCat(moveId, row, col, killId);
        break;
    case Stone::MOUSE:
        return canMoveMouse(moveId, row, col, killId);
        break;
    default:
        break;
    }
    return false;
}

bool Board::isInRiver(int row, int col){
    for(int i = 0; i < 12; ++i){
        if(row == RiverPos[i].row && col == RiverPos[i].col){
            return true;
        }
    }

    return false;
}

bool Board::isInTrap(int row, int col){
    for(int i = 0; i < 6; ++i){
        if(row == TrapPos[i].row && col == TrapPos[i].col){
            return true;
        }
    }

    return false;
}

bool Board::hasStoneType(int row, int col, Stone::TYPE type){
    for(int i = 0; i < 16; ++i){
        if(_st[i]._row == row && _st[i]._col == col
                && !_st[i]._dead && _st[i]._type == type){
            return true;
        }
    }
    return false;
}

bool Board::canJumpRiver(int moveId, int row, int col){

    //is near river
    //int nearId = -1; //the nearest point in river if the stone is near the river
    int mrow = _st[moveId]._row;
    int mcol = _st[moveId]._col;
    int i = 0;
    for(i = 0; i < 12; ++i){
        int dr = mrow - RiverPos[i].row;
        int dc = mcol - RiverPos[i].col;

        if(abs(dr) + abs(dc) == 1){
            //nearId = i;
            break;
        }
    }
    if(i == 12){
        return false;
    }

    if(mrow == 0){
        if(hasStoneType(1, mcol, Stone::MOUSE) || hasStoneType(2, mcol, Stone::MOUSE)){
            return false;
        }
        if(mcol == col && row == 3){
            return true;
        }
    }
    else if(mrow == 6){
        if(hasStoneType(4, mcol, Stone::MOUSE) || hasStoneType(5, mcol, Stone::MOUSE)){
            return false;
        }
        if(mcol == col && row == 3){
            return true;
        }
    }
    else if(mrow == 3){
        if(!hasStoneType(4, mcol, Stone::MOUSE) && !hasStoneType(5, mcol, Stone::MOUSE)
                && mcol == col && row == 6){
            return true;
        }
        if(!hasStoneType(1, mcol, Stone::MOUSE) && !hasStoneType(2, mcol, Stone::MOUSE)
                && mcol == col && row == 0){
            return true;
        }
    }
    else if(mcol == 2){
        if(hasStoneType(mrow, 3, Stone::MOUSE) || hasStoneType(mrow, 4, Stone::MOUSE)
                || hasStoneType(mrow, 5, Stone::MOUSE)){
            return false;
        }
        if(mrow == row && col == 6){
            return true;
        }
    }
    else if(mcol == 6){
        if(hasStoneType(mrow, 3, Stone::MOUSE) || hasStoneType(mrow, 4, Stone::MOUSE)
                || hasStoneType(mrow, 5, Stone::MOUSE)){
            return false;
        }
        if(mrow == row && col == 2){
            return true;
        }
    }

    return false;
}

bool Board::canMoveElephant(int moveId, int row, int col, int killId){

    //cannot go into the river
    if(isInRiver(row, col)){
        return false;
    }

    //can only move one step
    int dr = _st[moveId]._row - row;
    int dc = _st[moveId]._col - col;

    int d = abs(dr) + abs(dc);
    if(d != 1){
        return false;
    }

    //if the other stone is in trap, you can kill it no matter which type you are
    if(isInTrap(_st[killId]._row, _st[killId]._col)){
        return true;
    }

    //can eat except mouse
    if(killId != -1 && _st[killId]._type == Stone::MOUSE){
        return false;
    }

    return true;
}

bool Board::canMoveLion(int moveId, int row, int col, int killId){

    //cannot go into the river
    if(isInRiver(row, col)){
        return false;
    }


    //can only move one step except that the stone can jump over the river
    int dr = _st[moveId]._row - row;
    int dc = _st[moveId]._col - col;

    int d = abs(dr) + abs(dc);
    if(d != 1){
        //can jump cross the river
        if(!canJumpRiver(moveId, row, col)){
            return false;
        }
    }

    //if the other stone is in trap, you can kill it no matter which type you are
    if(isInTrap(_st[killId]._row, _st[killId]._col)){
        return true;
    }

    //can eat except elephant
    if(killId != -1 && _st[killId]._type == Stone::ELEPHANT){
        return false;
    }

    return true;
}

bool Board::canMoveTiger(int moveId, int row, int col, int killId){

    //cannot go into the river
    if(isInRiver(row, col)){
        return false;
    }


    //can only move one step except that the stone can jump over the river
    int dr = _st[moveId]._row - row;
    int dc = _st[moveId]._col - col;

    int d = abs(dr) + abs(dc);
    if(d != 1){
        //can jump cross the river
        if(!canJumpRiver(moveId, row, col)){
            return false;
        }
    }

    //if the other stone is in trap, you can kill it no matter which type you are
    if(isInTrap(_st[killId]._row, _st[killId]._col)){
        return true;
    }

    //can eat except elephant, lion
    if(killId != -1 && (_st[killId]._type == Stone::ELEPHANT || _st[killId]._type == Stone::LION)){
        return false;
    }

    return true;
}

bool Board::canMoveLeopard(int moveId, int row, int col, int killId){

    //cannot go into the river
    if(isInRiver(row, col)){
        return false;
    }

    //can only move one step
    int dr = _st[moveId]._row - row;
    int dc = _st[moveId]._col - col;

    int d = abs(dr) + abs(dc);
    if(d != 1){
        return false;
    }

    //if the other stone is in trap, you can kill it no matter which type you are
    if(isInTrap(_st[killId]._row, _st[killId]._col)){
        return true;
    }

    //can eat except elephant, lion, tiger
    if(killId >= 0 && (_st[killId]._type == Stone::ELEPHANT
                       || _st[killId]._type == Stone::LION || _st[killId]._type == Stone::TIGER)){
        return false;
    }

    return true;
}

bool Board::canMoveWolf(int moveId, int row, int col, int killId){

    //cannot go into the river
    if(isInRiver(row, col)){
        return false;
    }

    //can only move one step
    int dr = _st[moveId]._row - row;
    int dc = _st[moveId]._col - col;

    int d = abs(dr) + abs(dc);
    if(d != 1){
        return false;
    }

    //if the other stone is in trap, you can kill it no matter which type you are
    if(isInTrap(_st[killId]._row, _st[killId]._col)){
        return true;
    }

    //can eat only wolf, cat, dog, mouse
    if(killId == -1 || _st[killId]._type == Stone::WOLF || _st[killId]._type == Stone::MOUSE
            || _st[killId]._type == Stone::CAT || _st[killId]._type == Stone::DOG){
        return true;
    }
    else{
        return false;
    }
}

bool Board::canMoveDog(int moveId, int row, int col, int killId){

    //cannot go into the river
    if(isInRiver(row, col)){
        return false;
    }

    //can only move one step
    int dr = _st[moveId]._row - row;
    int dc = _st[moveId]._col - col;

    int d = abs(dr) + abs(dc);
    if(d != 1){
        return false;
    }

    //if the other stone is in trap, you can kill it no matter which type you are
    if(isInTrap(_st[killId]._row, _st[killId]._col)){
        return true;
    }

    //can eat only dog, cat, mouse
    if(killId == -1 || _st[killId]._type == Stone::DOG ||
            _st[killId]._type == Stone::CAT || _st[killId]._type == Stone::MOUSE){
        return true;
    }
    else{
        return false;
    }
}

bool Board::canMoveCat(int moveId, int row, int col, int killId){

    //cannot go into the river
    if(isInRiver(row, col)){
        return false;
    }

    //can only move one step
    int dr = _st[moveId]._row - row;
    int dc = _st[moveId]._col - col;

    int d = abs(dr) + abs(dc);
    if(d != 1){
        return false;
    }

    //if the other stone is in trap, you can kill it no matter which type you are
    if(isInTrap(_st[killId]._row, _st[killId]._col)){
        return true;
    }

    //can eat only cat, mouse
    if(killId == -1 || _st[killId]._type == Stone::MOUSE
            ||_st[killId]._type == Stone::CAT){
        return true;
    }
    else{
        return false;
    };
}

bool Board::canMoveMouse(int moveId, int row, int col, int killId){

    //can only move one step
    int dr = _st[moveId]._row - row;
    int dc = _st[moveId]._col - col;

    int d = abs(dr) + abs(dc);
    if(d != 1){
        return false;
    }

    //if mouse is in river, it cannot eat others
    if(killId != -1 && !isInRiver(row, col) && isInRiver(_st[moveId]._row, _st[moveId]._col)){
        return false;
    }

    //if the other stone is in trap, you can kill it no matter which type you are
    if(isInTrap(_st[killId]._row, _st[killId]._col)){
        return true;
    }

    //can eat only mouse, elephant
    if(killId == -1 || _st[killId]._type == Stone::MOUSE ||
            _st[killId]._type == Stone::ELEPHANT){
        return true;
    }
    else{
        return false;
    }
}

void Board::reliveStone(int saveId)
{
    if(saveId == -1){
        return;
    }

    _st[saveId]._dead = false;
}

void Board::back(Step *step)
{
    //relive the killed stone
    reliveStone(step->_killId);

    //return to previous position
    //qDebug() << _st[4]._row << " " << _st[4]._col;
    moveStone(step->_moveId, step->_rowFrom, step->_colFrom);
    //qDebug() << _st[4]._row << " " << _st[4]._col;
}

void Board::backOneStep(){
    if(_steps.size() == 0)
    {
        return;
    }

    Step* step = this->_steps.last();
    _steps.removeLast();
    back(step);

    --_stepNum;

    //qDebug() << _st[4]._row << " " << _st[4]._col;
    update();
    delete step;
}

void Board::saveStep(int moveId, int killId, int row, int col, QVector<Step*>&steps)
{
    Step* newstep = new Step;
    newstep->_moveId = moveId;
    newstep->_killId = killId;
    newstep->_rowFrom = _st[moveId]._row;
    newstep->_colFrom = _st[moveId]._col;

    newstep->_rowTo = row;
    newstep->_colTo = col;

    steps.append(newstep);
}

void Board::back()
{
    backOneStep();
}

void Board::slotBack()
{
    back();
}

void Board::showResult(){

    QString GOinfo("GAME OVER!!     "); //game is over
    QMessageBox RetInfo;
    RetInfo.setWindowTitle("Game Result");
    RetInfo.setText(GOinfo);

    switch (_result) {
    case TIE:

        RetInfo.setInformativeText("Tie, you two are evenly matched!");
        RetInfo.exec();
        break;
    case RED_WIN:
        RetInfo.setInformativeText("Red wins!       ");
        RetInfo.exec();
        break;
    case RED_LOSE:
        RetInfo.setInformativeText("Black wins!     ");
        RetInfo.exec();
        break;
    default:
        break;
    }
}

bool Board::isGameOver(){

    /* Occupy the opponent's den, you win */
    int denId = -1;
    if(hasStone(3, 0, denId)){
        if(_isRedSide && _st[denId]._red){
            _result = RED_WIN;
            showResult();
        }
        else if(!_isRedSide && !_st[denId]._red){
            _result = RED_LOSE;
            showResult();
        }
    }

    if(hasStone(3, 8, denId)){
        if(_isRedSide && !_st[denId]._red){
            _result = RED_LOSE;
            showResult();
        }
        else if(!_isRedSide && _st[denId]._red){
            _result = RED_WIN;
            showResult();
        }
    }

    /* All your animals are dead or cannot move, you lose */
    if(isAllDead(true) || isAllCannotMove(true)){
        _result = RED_LOSE;
        showResult();
    }
    if(isAllDead(false) || isAllCannotMove(false)){
        _result = RED_WIN;
        showResult();
    }

    /* move than max move-times limit, tie */
    if(_stepNum == MAX_STEPS){
        _result = TIE;
        showResult();
    }

    return false;
}

bool Board::isAllDead(bool isRed){
    int initIndex = isRed?0 : 8;
    for(int i = 0; i < 8; ++i){
        if(!_st[i + initIndex]._dead){ //not dead yet
            return false;
        }
    }
    return true;
}

bool Board::isAllCannotMove(bool isRed){
    int initIndex = isRed?0 : 8;
    for(int i = 0; i < 8; ++i){
        if(!_st[i + initIndex]._dead){ //not dead yet
            int mrow = _st[i + initIndex]._row;
            int mcol = _st[i + initIndex]._col;

            if(i == 1 || i == 2){
                //lion or tiger
                for(int k = 0; k < 7; ++k){
                    for(int l = 0; l < 9; ++l){
                        if(k == mrow && l == mcol){
                            continue;
                        }
                        int targetId = -1;
                        hasStone(k, l , targetId);

                        if(targetId != -1 && _st[targetId]._red == isRed){
                            continue;
                        }
                        if((this->*Board::canMoveFunc[i])(i + initIndex, k, l, targetId)){
                            return false; //can move the stone
                        }
                    }
                }
            }
            else{
                //not lion nor tiger
                struct{int row; int col;}nearP[4] = {
                {mrow + 1, mcol},
                {mrow, mcol + 1},
                {mrow - 1, mcol},
                {mrow, mcol - 1}
                };
                for(int m = 0; m < 4; ++m){
                    int targetId = -1;
                    hasStone(nearP[m].row, nearP[m].col, targetId);
                    if(targetId != -1 && _st[targetId]._red == isRed){
                        continue;
                    }
                    if((this->*Board::canMoveFunc[i])(i + initIndex, nearP[m].row, nearP[m].col, targetId)){
                        return false; //can move the stone
                    }
                }
            }
        }
    }

    return true;
}
