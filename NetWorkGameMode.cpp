#include "NetWorkGameMode.h"

NetWorkGameMode::NetWorkGameMode(bool server, QWidget *parent) : Board(parent)
{
    _server = NULL;
    _socket = NULL;
    _isServer = server;

    if(_isServer)
    {
        _server = new QTcpServer(this);
        _server->listen(QHostAddress::Any, 9899);
        connect(_server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    }
    else
    {
        _socket = new QTcpSocket(this);
        _socket->connectToHost(QHostAddress("127.0.0.1"), 9899);
        connect(_socket, SIGNAL(readyRead()), this, SLOT(slotDataArrive()));
    }
}

NetWorkGameMode::~NetWorkGameMode()
{
    delete _server;
    delete _socket;
}

void NetWorkGameMode::slotNewConnection()
{
    if(_socket) return;

    _socket = _server->nextPendingConnection();
    connect(_socket, SIGNAL(readyRead()), this, SLOT(slotDataArrive()));

    /* depend who goes red stones */
    bool isRedSide = qrand()%2>0;
    init(isRedSide);

    /* send the msg to opponent */
    QByteArray buf;
    buf.append(INIT_SIG);
    buf.append(isRedSide?0:1);
    _socket->write(buf);
}

void NetWorkGameMode::back()
{
    if(_isRedTurn != _isRedSide)
    {
        return;
    }

    backOneStep();
    backOneStep();

    QByteArray buf;
    buf.append(BACK_SIG);
    _socket->write(buf);
}

void NetWorkGameMode::click(int id, int row, int col)
{
    if(_isRedTurn != _isRedSide)
    {
        return;
    }

    Board::click(id, row, col);

    QByteArray buf;
    buf.append(CLICK_SIG);
    buf.append(id);
    buf.append(row);
    buf.append(col);
    _socket->write(buf);

}

void NetWorkGameMode::backFromNetWork()
{
    backOneStep();
    backOneStep();
}

void NetWorkGameMode::clickFromNetWork(QByteArray buf)
{
    Board::click(buf[1], 6-buf[2], 8-buf[3]);
}

void NetWorkGameMode::initFromNetWork(QByteArray buf)
{
    bool isRedSide = buf[1] ? true : false;
    init(isRedSide);
}

void NetWorkGameMode::slotDataArrive()
{
    QByteArray buf = _socket->readAll();

    switch (buf[0]) {
    case INIT_SIG:
        initFromNetWork(buf);
        break;
    case CLICK_SIG:
        clickFromNetWork(buf);
        break;
    case BACK_SIG:
        backFromNetWork();
        break;
    default:
        break;
    }
}
