#ifndef ONLINEGAMEMODE_H
#define ONLINEGAMEMODE_H

#include "Board.h"
#include <QTcpServer>
#include <QTcpSocket>

/* protocol */
#define INIT_SIG 1
#define CLICK_SIG 2
#define BACK_SIG 3

class NetWorkGameMode : public Board
{
    Q_OBJECT
public:
    explicit NetWorkGameMode(bool server, QWidget *parent = 0);
    ~NetWorkGameMode();

    bool _isServer;
    QTcpServer* _server;
    QTcpSocket* _socket;

    void back();
    void click(int id, int row, int col);

    void backFromNetWork();
    void clickFromNetWork(QByteArray buf);
    void initFromNetWork(QByteArray buf);

public slots:
    void slotNewConnection();
    void slotDataArrive();
};

#endif // ONLINEGAMEMODE_H
