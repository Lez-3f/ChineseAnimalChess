#ifndef STEP_H
#define STEP_H

#include <QObject>

class Step : public QObject
{
    Q_OBJECT
public:
    explicit Step(QObject *parent = nullptr);

    int _moveId;
    int _killId;
    int _rowFrom;
    int _colFrom;
    int _rowTo;
    int _colTo;

signals:

};

#endif // STEP_H
