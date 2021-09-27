#include "Stone.h"

Stone::Stone()
{

}

QString Stone::getText(){
    switch (this->_type) {
    case ELEPHANT:
        return "象";
    case LION:
        return "狮";
    case TIGER:
        return "虎";
    case LEOPARD:
        return "豹";
    case WOLF:
        return "狼";
    case DOG:
        return "狗";
    case CAT:
        return "猫";
    case MOUSE:
        return "鼠";
    }
    return "";
}

void Stone::init(int id){

    struct{
        int row, col;
        Stone::TYPE type;
    }   posInit[8]={
    {6, 2, ELEPHANT},
    {0, 0, LION},
    {6, 0, TIGER},
    {2, 2, LEOPARD},
    {4, 2, WOLF},
    {1, 1, DOG},
    {5, 1, CAT},
    {0, 2, MOUSE}
    };

    _id = id;
    _dead = false;
    _red = id < 8;

    if(id < 8){
        _row = posInit[id].row;
        _col = posInit[id].col;
        _type = posInit[id].type;
    }
    else{
        _row = 6 - posInit[id - 8].row;
        _col = 8 - posInit[id - 8].col;
        _type = posInit[id - 8].type;
    }
}

void Stone::rotate(){
    _row = 6 - _row;
    _col = 8 - _col;
}
