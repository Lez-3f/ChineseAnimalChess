#ifndef STONE_H
#define STONE_H
#include <QString>

class Stone
{
public:
    Stone();
    //~Stone();

    enum TYPE{ELEPHANT, LION, TIGER, LEOPARD, WOLF, DOG, CAT, MOUSE};

    int _row, _col; //position row(0-6) col(0-8)
    int _id; //id
    bool _dead; //if dead
    bool _red; //if red
    TYPE _type; //type

    QString getText();

    void init(int id);

    //rotate
    void rotate();
};

#endif // STONE_H
