#include "qtserver.h"
#include "ui_qtserver.h"

QtServer::QtServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtServer)
{
    ui->setupUi(this);

    count=0;
    setWindowFlags(this->windowFlags() | Qt::WindowMinMaxButtonsHint);
    ui->labelNum->setText(QString("%1").arg(count));
    this->server = new TcpServer(this);
    ///开启监听
    this->server->listen(QHostAddress::Any,6666);
    connect(this->server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));

    ///文件传送套接字
    //this->filesocket = new QTcpSocket(this);
    //this->fileserver = new TcpServer(this);
    //this->fileserver->listen(QHostAddress::Any,8888);
    //connect(this->fileserver,SIGNAL(newConnection()),this,SLOT(acceptFileConnection()));

    //// 文件传送相关变量初始化
    bytesReceived = 0;
    totalBytes = 0;
    filenameSize = 0;
    connect(ui->btnSend,SIGNAL(clicked()),this, SLOT(sendDataSlot()));
    connect(ui->btnClear,SIGNAL(clicked()),this, SLOT(clearData()));
}

QtServer::~QtServer()
{
    delete ui;
}

void QtServer::showConnection(int sockDesc)

{
    count++;
    /* add socket object that join in */
    ui->comboBoxObj->addItem(QString("%1").arg(sockDesc), sockDesc);

    /* change connect number while connection is connecting */
    ui->labelNum->setText(QString("%1").arg(count));
}



void QtServer::showDisconnection(int sockDesc)
{
    count--;

    /* refresh combobox */

    ui->comboBoxObj->clear();
    int index = ui->comboBoxObj->findData(sockDesc);

    ui->comboBoxObj->removeItem(index);
    /* change connect number while connection is disconnecting */

    ui->labelNum->setText(QString("%1").arg(count));

}

void QtServer::sendDataSlot(void)

{

    /* if send message is null return */

    if (ui->lineEditMsg->text().isEmpty()) {

        QMessageBox::information(Q_NULLPTR, QString("注意"), QString("发送内容不能为空！"), QMessageBox::Yes);

        return ;

    }

     /* send original data */

    for(int i=0;i<ui->comboBoxObj->count();i++)
    {
        qDebug()<<i;
        emit sendData(ui->comboBoxObj->itemText(i).toInt(), ui->lineEditMsg->text().toUtf8());
    }

    ui->lineEditMsg->setText("");

}
void QtServer::recvData(const QString &ip, const QByteArray &data)

{

    QString msg;

    /* add ip address string to displaying string */


    /* choose data format to display */

        msg.prepend(data) + "\n";
    /* send back data */
    for(int i=0;i<ui->comboBoxObj->count();i++)
    {
        emit sendData(ui->comboBoxObj->itemText(i).toInt(), msg.toUtf8());
    }
    ui->textBrowser->append(msg);
}

void QtServer::clearData(void)

{
    ui->textBrowser->clear();
}

/*void QtServer::acceptFileConnection()
{
    bytesWritten = 0;
    ///每次发送数据大小为64kb
    perDataSize = 64*1024;
    this->filesocket = this->fileserver->nextPendingConnection();
    ///接受文件
    connect(filesocket,SIGNAL(readyRead()),this,SLOT(updateFileProgress()));
    connect(filesocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(updateFileProgress(qint64)));
    connect(filesocket,SIGNAL(bytesWritten(qint64)),this,SLOT(displayError(QAbstractSocket::SocketError socketError)));
}

void QtServer::updateFileProgress()
{
    QDataStream inFile(this->filesocket);
    inFile.setVersion(QDataStream::Qt_4_8);

    ///如果接收到的数据小于16个字节，保存到来的文件头结构
    if(bytesReceived <= sizeof(qint64)*2)
    {
        if((filesocket->bytesAvailable()>=(sizeof(qint64))*2) && (filenameSize==0))
        {
            inFile>>totalBytes>>filenameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if((filesocket->bytesAvailable()>=filenameSize) && (filenameSize != 0))
        {
            inFile>>filename;
            bytesReceived += filenameSize;
            ////接收的文件放在指定目录下
            filename = "ClientData/"+filename;
            localFile = new QFile(filename);
            if(!localFile->open(QFile::WriteOnly))
            {
                qDebug()<<"Server::open file error!";
                return;
            }
        }
        else
            return;
    }
    /////如果接收的数据小于总数据，则写入文件
    if(bytesReceived < totalBytes)
    {
        bytesReceived += filesocket->bytesAvailable();
        inBlock = filesocket->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    ////更新进度条显示
    //this->ui->progressBar_fileProgress->setMaximum(totalBytes);
    //this->ui->progressBar_fileProgress->setValue(bytesReceived);
    ////数据接收完成时
    if(bytesReceived == totalBytes)
    {
        this->ui->browser->append("Receive file successfully!");
        bytesReceived = 0;
        totalBytes = 0;
        filenameSize = 0;
        localFile->close();
        //filesocket->close();
    }
}

void QtServer::selectFile()
{
    filesocket->open(QIODevice::WriteOnly);
    ////文件传送进度更新
    connect(filesocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateFileProgress(qint64)));

    this->filename = QFileDialog::getOpenFileName(this,"Open a file","/","files (*)");
    ui->lineEdit_fileName->setText(filename);
}

void QtServer::sendFile()
{
    this->localFile = new QFile(filename);
    if(!localFile->open(QFile::ReadOnly))
    {
        qDebug()<<"发送文件失败";
        return;
    }
    ///获取文件大小
    this->totalBytes = localFile->size();
    QDataStream sendout(&outBlock,QIODevice::WriteOnly);
    sendout.setVersion(QDataStream::Qt_4_8);
    QString currentFileName = filename.right(filename.size()-filename.lastIndexOf('/')-1);

    ////保留总代大小信息空间、文件名大小信息空间、文件名
    sendout<<qint64(0)<<qint64(0)<<currentFileName;
    totalBytes += outBlock.size();
    sendout.device()->seek(0);
    sendout<<totalBytes<<qint64((outBlock.size()-sizeof(qint64)*2));

    bytestoWrite = totalBytes-filesocket->write(outBlock);
    outBlock.resize(0);
}

void QtServer::updateFileProgress(qint64 numBytes)
{
    ////已经发送的数据大小
    bytesWritten += (int)numBytes;

    ////如果已经发送了数据
    if(bytestoWrite > 0)
    {
        outBlock = localFile->read(qMin(bytestoWrite,perDataSize));
        ///发送完一次数据后还剩余数据的大小
        bytestoWrite -= ((int)filesocket->write(outBlock));
        ///清空发送缓冲区
        outBlock.resize(0);
    }
    else
        localFile->close();

    ////如果发送完毕
    if(bytesWritten == totalBytes)
    {
        localFile->close();
        //filesocket->close();
    }
}*/

