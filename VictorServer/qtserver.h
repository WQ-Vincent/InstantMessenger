#ifndef QTSERVER_H
#define QTSERVER_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDataStream>
#include <QString>
#include <QByteArray>
#include <QFileDialog>
#include <QDateTime>
#include <tcpserver.h>
#include <mysocket.h>
#include <QMessageBox>

QT_BEGIN_NAMESPACE

class TcpServer;

namespace Ui { class QtServer; }
QT_END_NAMESPACE

class QtServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtServer(QWidget *parent = nullptr);
    ~QtServer();

    //TcpServer *fileserver;

signals:
    void sendData(int id, const QByteArray &data);


public slots:

    void recvData(const QString &ip, const QByteArray &data);

private slots:
    void showConnection(int sockDesc);

    void showDisconnection(int sockDesc);

    void sendDataSlot(void);

    void clearData(void);

    //void acceptFileConnection();
    //void updateFileProgress();
    ///选择发送的文件
    //void selectFile();
    //void sendFile();
    ////更新文件传送进度
    //void updateFileProgress(qint64);

private:
    Ui::QtServer *ui;

    friend class TcpServer;
    int count;
    TcpServer *server;

    ////传送文件相关变量
    qint64 totalBytes;
    qint64 bytesReceived;
    qint64 bytestoWrite;
    qint64 bytesWritten;
    qint64 filenameSize;
    QString filename;
    ///每次发送数据大小
    qint64 perDataSize;
    QFile *localFile;
    ////本地缓冲区
    QByteArray inBlock;
    QByteArray outBlock;

    ////系统时间
    QDateTime current_date_time;
    QString str_date_time;
};
#endif // QTSERVER_H
