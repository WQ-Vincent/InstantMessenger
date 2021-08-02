#include "tcpserver.h"
#include "serverthread.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
     m_dialog = dynamic_cast<QtServer *>(parent);
}

TcpServer::~TcpServer()
{

}

void TcpServer::incomingConnection(int sockDesc)
{
    m_socketList.append(sockDesc);



        serverThread *thread = new serverThread(sockDesc);



        m_dialog->showConnection(sockDesc);



        connect(thread, SIGNAL(disconnectTCP(int)), this, SLOT(clientDisconnected(int)));

        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));



        connect(thread, SIGNAL(dataReady(const QString&, const QByteArray&)),

                m_dialog, SLOT(recvData(const QString&, const QByteArray&)));



        connect(m_dialog, SIGNAL(sendData(int, const QByteArray&)),

                thread, SLOT(sendDataSlot(int, const QByteArray&)));



        thread->start();
}
void TcpServer::clientDisconnected(int sockDesc)

{

    m_dialog->showDisconnection(sockDesc);

}
