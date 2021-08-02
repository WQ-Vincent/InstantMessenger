#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDesktopServices>
#include <QUrl>
#include <database.h>
#include <QMessageBox>
#include <setting.h>
#include <QMouseEvent>
#include <QFrame>
#include <QMenu>
#include <QDomDocument>
#include <QFile>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <inform.h>
#include <login.h>
#include <addfrd.h>
#include <QButtonGroup>
#include <QListWidgetItem>
#include <listwidget.h>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QScrollBar>
#include <QPixmap>
#include <QDateTime>
#include <QDebug>
#include <qnchatmessage.h>
#include <QTime>
#include <QtGlobal>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDataStream>
#include <QString>
#include <QByteArray>
#include <QFileDialog>
#include <QHostAddress>
#include <QNetworkInterface>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time,  QNChatMessage::User_Type type);

    void dealMessageTime(QString curMsgTime);

    void initTCP();
    void newConnect();

    bool ifopen;
    QString nowid;

protected:
    bool eventFilter(QObject *target, QEvent *event);

private slots:        // 客户端方法
    ////连接服务器
    QString getHostIpAddress();

    void connectServer();
    ////与服务器断开连接
    void disconnectServer();
    ////接收服务器发送的数据
    void receiveData();
    ////向服务器发送数据
    void send_message();
    ////浏览文件
    void selectFile();
    ////发送文件
    void sendFile();
    ////更新文件发送进度
    void updateFileProgress(qint64);
    ////更新文件接收进度
    void updateFileProgress();

private slots:

    void initial_friendlist();

    void initial_talklist();

    void frdinform_display();

    void delete_frd();

    void set_top();

    void delete_talk();

    void talkto();

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_15_clicked(bool checked);

    void on_pushButton_6_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_8_clicked(bool checked);

    void on_pushButton_20_clicked();

    void on_pushButton_23_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_24_clicked();

    void on_pushButton_11_clicked();

    void on_commandLinkButton_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_22_clicked();

private:
    Ui::MainWindow *ui;

    // 客户端成员
    QString ip_address;
    QTcpSocket *tcpSocket;
    QTcpSocket *fileSocket;

      ///文件传送
    QFile *localFile;
      ///文件大小
    qint64 totalBytes;      //文件总字节数
    qint64 bytesWritten;    //已发送的字节数
    qint64 bytestoWrite;    //尚未发送的字节数
    qint64 filenameSize;    //文件名字的字节数
    qint64 bytesReceived;   //接收的字节数
    ///每次发送数据大小
    qint64 perDataSize;
    QString filename;
    ///数据缓冲区
    QByteArray inBlock;
    QByteArray outBlock;

    ////系统时间
    QDateTime current_date_time;
    QString str_date_time;

    bool     m_pressed;
    QPoint   m_movePos;
};

#endif // MAINWINDOW_H
