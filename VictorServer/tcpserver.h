#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QTcpServer>
#include <QDialog>
#include <QThread>
#include "serverthread.h"
#include "qtserver.h"
class QtServer;
class TcpServer:public QTcpServer
{
    Q_OBJECT
public:

    explicit TcpServer(QObject *parent = Q_NULLPTR);

    ~TcpServer();

private:

    void incomingConnection(int sockDesc);

private slots:

    void clientDisconnected(int sockDesc);

private:

    QtServer *m_dialog;

    QList<int> m_socketList;
};

#endif // TCPSERVER_H
