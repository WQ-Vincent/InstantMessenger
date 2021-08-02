#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ip_address=getHostIpAddress();
        /////文件传送相关变量初始化
        ///每次发送数据大小为64kb
        perDataSize = 64*1024;
        totalBytes = 0;
        bytestoWrite = 0;
        bytesWritten = 0;
        bytesReceived = 0;
        filenameSize = 0;

        connect(this->ui->pushButton_10,SIGNAL(clicked()),this,SLOT(selectFile()));
        //connect(this->ui.pushButton_sendFile,SIGNAL(clicked()),this,SLOT(sendFile()));


    ui->textEdit->installEventFilter(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setFixedSize(this->width(),this->height());

    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 0);          //设置向哪个方向产生阴影效果(dx,dy)，特别地，(0,0)代表向四周发散
    effect->setColor(Qt::gray);       //设置阴影颜色，也可以setColor(QColor(220,220,220))
    effect->setBlurRadius(20);        //设定阴影的模糊半径，数值越大越模糊
    ui->frame->setGraphicsEffect(effect);

    login a;
    ifopen=true;
    if(a.exec()==QDialog::Accepted)
    {
        nowid=a.getid();
        initTCP();
        initial_friendlist();
        initial_talklist();
        a.close();
        this->show();
    }
    else
    {
        ifopen=false;
    }
    ui->lineEdit->setPlaceholderText(" 搜索");
    ui->lineEdit->setStyleSheet("border:gray");
    ui->lineEdit_2->setPlaceholderText(" 搜索");
    ui->lineEdit_2->setStyleSheet("border:gray");
    ui->textEdit->setStyleSheet("border:gray");
    ui->listWidget_3->setStyleSheet("border:gray");
    ui->label_17->setStyleSheet("background:red; border-radius:5px;");
    ui->label_17->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->label_18->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->label_20->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->pushButton_24->hide();
    ui->widget_2->hide();
    ui->widget_3->hide();
    ui->widget_4->hide();
    ui->widget_5->hide();
    ui->listWidget->setFrameShape(QListWidget::NoFrame);
    ui->listWidget_4->setFrameShape(QListWidget::NoFrame);

    ui->listWidget->setStyleSheet("QListWidget{background:rgb(238, 247, 255);}"
                                  "QListWidget::item:hover{background-color:rgb(200, 230, 250);}"
                                  "QListWidget::item:selected{background-color:rgb(170, 210, 250);}"
                                  "QListWidget{outline:0px;}"
                                  "QListWidget::item{background-color:rgb(225, 240, 250);}");
    ui->listWidget->verticalScrollBar()->setStyleSheet("QScrollArea{border:0px solid;"
                                                       "border-radius: 2px;}"
                                                       "QScrollBar:vertical{width: 4px;border:0px solid;"
                                                       "border-radius: 2px;margin: 0px,0px,0px,0px;"
                                                       "background-color: transparent;background:#e1f0fa;}"
                                                       "QScrollBar:vertical:hover{width: 4px;"
                                                       "border:0px solid;margin: 0px,0px,0px,0px;background:#e1f0fa;}"
                                                       "QScrollBar::handle:vertical{width:4px;background:#c0ddee;"
                                                       "border-radius: 2px;height: 40px;}"
                                                       "QScrollBar::handle:vertical:hover{background:#c0ddee;"
                                                       "border-radius: 2px;}"
                                                       "QScrollBar::add-line:vertical{height:11px;background-color: transparent;"
                                                       "subcontrol-position:bottom;border:0px solid;"
                                                       "border-radius: 2px;}"
                                                       "QScrollBar::sub-line:vertical{height:11px;"
                                                       "background-color: transparent;subcontrol-position:top;"
                                                       "border:0px solid;border-radius: 2px;}"
                                                       "QScrollBar::add-page:vertical{background-color: #e1f0fa;"
                                                       "border:0px solid;border-radius: 2px;}"
                                                       "QScrollBar::sub-page:vertical{background-color: #e1f0fa;"
                                                       "border:0px solid;border-radius: 2px;}"
                                                       "QScrollBar::up-arrow:vertical{"
                                                       "border:0px solid;border-radius: 3px;}"
                                                       "QScrollBar::down-arrow:vertical {"
                                                       "border:0px solid;border-radius: 3px;}");

    ui->listWidget_2->setStyleSheet("QListWidget{background:rgb(238, 247, 255);border:0px;}"
                                  "QListWidget::item:hover{background-color:rgb(200, 230, 250);}"
                                  "QListWidget::item:selected{background-color:rgb(170, 210, 250);}"
                                  "QListWidget{outline:0px;}"
                                  "QListWidget::item{background-color:rgb(225, 240, 250);}");
    ui->listWidget_2->verticalScrollBar()->setStyleSheet("QScrollArea{border:0px solid;"
                                                       "border-radius: 2px;}"
                                                       "QScrollBar:vertical{width: 4px;border:0px solid;"
                                                       "border-radius: 2px;margin: 0px,0px,0px,0px;"
                                                       "background-color: transparent;background:#e1f0fa;}"
                                                       "QScrollBar:vertical:hover{width: 4px;"
                                                       "border:0px solid;margin: 0px,0px,0px,0px;background:#e1f0fa;}"
                                                       "QScrollBar::handle:vertical{width:4px;background:#c0ddee;"
                                                       "border-radius: 2px;height: 40px;}"
                                                       "QScrollBar::handle:vertical:hover{background:#c0ddee;"
                                                       "border-radius: 2px;}"
                                                       "QScrollBar::add-line:vertical{height:11px;background-color: transparent;"
                                                       "subcontrol-position:bottom;border:0px solid;"
                                                       "border-radius: 2px;}"
                                                       "QScrollBar::sub-line:vertical{height:11px;"
                                                       "background-color: transparent;subcontrol-position:top;"
                                                       "border:0px solid;border-radius: 2px;}"
                                                       "QScrollBar::add-page:vertical{background-color: #e1f0fa;"
                                                       "border:0px solid;border-radius: 2px;}"
                                                       "QScrollBar::sub-page:vertical{background-color: #e1f0fa;"
                                                       "border:0px solid;border-radius: 2px;}"
                                                       "QScrollBar::up-arrow:vertical{"
                                                       "border:0px solid;border-radius: 3px;}"
                                                       "QScrollBar::down-arrow:vertical {"
                                                       "border:0px solid;border-radius: 3px;}");
    ui->listWidget_3->setStyleSheet("QListWidget{background-color: rgb(245, 249, 253);border:0px;}"
                                  "QListWidget{outline:0px;}"
                                  "QListWidget::item{background-color: rgb(245, 249, 253);}");
    ui->listWidget_3->verticalScrollBar()->setStyleSheet("QScrollArea{border:0px solid;"
                                                       "border-radius: 5px;}"
                                                       "QScrollBar:vertical{width: 10px;border:0px solid;"
                                                       "border-radius: 5px;margin: 0px,0px,0px,0px;"
                                                       "background-color: transparent;background:#e1f0fa;}"
                                                       "QScrollBar:vertical:hover{width: 10px;"
                                                       "border:0px solid;margin: 0px,0px,0px,0px;background:#e1f0fa;}"
                                                       "QScrollBar::handle:vertical{width:10px;background:#c0ddee;"
                                                       "border-radius: 5px;height: 40px;}"
                                                       "QScrollBar::handle:vertical:hover{background:#c0ddee;"
                                                       "border-radius: 5px;}"
                                                       "QScrollBar::add-line:vertical{height:11px;background-color: transparent;"
                                                       "subcontrol-position:bottom;border:0px solid;"
                                                       "border-radius: 5px;}"
                                                       "QScrollBar::sub-line:vertical{height:11px;"
                                                       "background-color: transparent;subcontrol-position:top;"
                                                       "border:0px solid;border-radius: 5px;}"
                                                       "QScrollBar::add-page:vertical{background-color: #e1f0fa;"
                                                       "border:0px solid;border-radius: 5px;}"
                                                       "QScrollBar::sub-page:vertical{background-color: #e1f0fa;"
                                                       "border:0px solid;border-radius: 5px;}"
                                                       "QScrollBar::up-arrow:vertical{"
                                                       "border:0px solid;border-radius: 3px;}"
                                                       "QScrollBar::down-arrow:vertical {"
                                                       "border:0px solid;border-radius: 3px;}");
    ui->listWidget_4->setStyleSheet("QListWidget{background:rgb(238, 247, 255);}"
                                  "QListWidget::item:hover{background-color:rgb(200, 230, 250);}"
                                  "QListWidget::item:selected{background-color:rgb(170, 210, 250);}"
                                  "QListWidget{outline:0px;}"
                                  "QListWidget::item{background-color:rgb(225, 240, 250);}");
    ui->listWidget_4->verticalScrollBar()->setStyleSheet("QScrollArea{border:0px solid;"
                                                       "border-radius: 2px;}"
                                                       "QScrollBar:vertical{width: 4px;border:0px solid;"
                                                       "border-radius: 2px;margin: 0px,0px,0px,0px;"
                                                       "background-color: transparent;background:#e1f0fa;}"
                                                       "QScrollBar:vertical:hover{width: 4px;"
                                                       "border:0px solid;margin: 0px,0px,0px,0px;background:#e1f0fa;}"
                                                       "QScrollBar::handle:vertical{width:4px;background:#c0ddee;"
                                                       "border-radius: 2px;height: 40px;}"
                                                       "QScrollBar::handle:vertical:hover{background:#c0ddee;"
                                                       "border-radius: 2px;}"
                                                       "QScrollBar::add-line:vertical{height:11px;background-color: transparent;"
                                                       "subcontrol-position:bottom;border:0px solid;"
                                                       "border-radius: 2px;}"
                                                       "QScrollBar::sub-line:vertical{height:11px;"
                                                       "background-color: transparent;subcontrol-position:top;"
                                                       "border:0px solid;border-radius: 2px;}"
                                                       "QScrollBar::add-page:vertical{background-color: #e1f0fa;"
                                                       "border:0px solid;border-radius: 2px;}"
                                                       "QScrollBar::sub-page:vertical{background-color: #e1f0fa;"
                                                       "border:0px solid;border-radius: 2px;}"
                                                       "QScrollBar::up-arrow:vertical{"
                                                       "border:0px solid;border-radius: 3px;}"
                                                       "QScrollBar::down-arrow:vertical {"
                                                       "border:0px solid;border-radius: 3px;}");

    connect(ui->listWidget->action1,SIGNAL(clicked()), this, SLOT(send_message()));
    connect(ui->listWidget->action2,SIGNAL(clicked()), this, SLOT(delete_frd()));
    connect(ui->listWidget->action3,SIGNAL(clicked()), this, SLOT(frdinform_display()));
    connect(ui->listWidget_2->action1,SIGNAL(clicked()), this, SLOT(set_top()));
    connect(ui->listWidget_2->action2,SIGNAL(clicked()), this, SLOT(delete_talk()));
    connect(ui->listWidget_2->action3,SIGNAL(clicked()), this, SLOT(talkto()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//客户端方法
QString MainWindow::getHostIpAddress()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
               ipAddressesList.at(i).toIPv4Address()) {
               strIpAddress = ipAddressesList.at(i).toString();
               break;
           }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
     return strIpAddress;
}

void MainWindow::initTCP()
{
    this->tcpSocket = new QTcpSocket(this);
    connectServer();
}

void MainWindow::connectServer()
{
    tcpSocket->abort();
    tcpSocket->connectToHost(ip_address,6666);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveData()));
}

void MainWindow::disconnectServer()
{
    QMessageBox::warning(this,"错误","请检查网络或服务器设置");
}

void MainWindow::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time,  QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(ui->listWidget_3->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget_3->setItemWidget(item, messageW);
}

void MainWindow::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget_3->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget_3->item(ui->listWidget_3->count() - 1);
        QNChatMessage* messageW = qobject_cast<QNChatMessage*>(ui->listWidget_3->itemWidget(lastItem));
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    }
    else
    {
        isShowTime = true;
    }
    if(isShowTime)
    {
        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget_3->parentWidget(),nowid,ui->listWidget_2->frdid);
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget_3);
        QSize size = QSize(ui->listWidget_3->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->listWidget_3->setItemWidget(itemTime, messageTime);
    }

}

void MainWindow::receiveData()
{
    QString msg;
    msg.prepend(tcpSocket->readAll());
    QStringList msglist=msg.split("|");
    if(msglist[1]!=nowid)return;
    int flag=0;
    for(int i=0;i<ui->listWidget_2->count();i++)
    {
        QListWidgetItem *item=ui->listWidget_2->item(i);
        QWidget* pwig = ui->listWidget_2->itemWidget(item);
        QList<QLineEdit*> linedList = pwig->findChildren<QLineEdit*>();
        foreach(QLineEdit *lined, linedList)
        {
            if(!lined->text().isEmpty())
            {
                QString frdid=lined->text();
                if(frdid==msglist[0])
                {
                    flag=1;
                    item->setSelected(true);
                    ui->listWidget_2->frdid=msglist[0];
                    set_top();
                }
            }
        }
    }
    if(flag==0)
    {
        QString oldfid=ui->listWidget->frdid;
        ui->listWidget->frdid=msglist[0];
        send_message();
        ui->listWidget->frdid=oldfid;
    }
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    dealMessageTime(time);
    QNChatMessage* messageW = new QNChatMessage(ui->listWidget_3->parentWidget(),nowid,msglist[0]);
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget_3);
    dealMessage(messageW, item, msglist[2], time, QNChatMessage::User_She);
}

void MainWindow::on_pushButton_11_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    if(msg.isEmpty())
    {
        ui->textEdit->setFocus();
        return;
    }
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    bool isSending = true; // 发送中
    //if(ui->listWidget_3->count()%2)
    //{
        if(isSending)
        {
            dealMessageTime(time);
            QNChatMessage* messageW = new QNChatMessage(ui->listWidget_3->parentWidget(),nowid,ui->listWidget_2->frdid);
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_3);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
        }
        /*else
        {
            bool isOver = true;
            for(int i = ui->listWidget_3->count()-1; i>0; i--)
            {
                QNChatMessage* messageW = qobject_cast<QNChatMessage*>(ui->listWidget_3->itemWidget(ui->listWidget_3->item(i)));
                if(messageW->text() == msg)
                {
                    isOver = false;
                    messageW->setTextSuccess();
                }
            }
            if(isOver)
            {
                dealMessageTime(time);
                QNChatMessage* messageW = new QNChatMessage(ui->listWidget_3->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(ui->listWidget_3);
                dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
                messageW->setTextSuccess();
            }

        }
    else
    {
        if(msg != "")
        {
            dealMessageTime(time);
            QNChatMessage* messageW = new QNChatMessage(ui->listWidget_3->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_3);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
        }
    }*/
    ui->listWidget_3->setCurrentRow(ui->listWidget_3->count()-1);
    QString fid=ui->listWidget_2->frdid;
    msg=nowid+"|"+fid+"|"+msg;
    this->tcpSocket->write(msg.toUtf8());
}

void MainWindow::send_message()
{
    ui->textEdit->setFocus();
    ui->listWidget_3->clear();
    ui->tabWidget->setCurrentWidget(ui->tab_3);
    QString fid=ui->listWidget->frdid;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString str=QString("select user_friend from talklist where user_id='%1'").arg(nowid);
    query.exec(str);
    QString frdlist1,frdlist2;
    if(query.next())
    {
        frdlist1=query.value(0).toString();
    }

    QString str1=QString("select user_name,touxiang from userdata where user_id='%1'").arg(fid);
    query.exec(str1);
    QString name;
    QString toux;
    if(query.next())
    {
        name=query.value(0).toString();
        toux=query.value(1).toString();
    }
    int num=ui->listWidget_2->count();
    if(num==0)
    {
        query.exec(QString("update talklist set user_friend='%1' where user_id='%2'").arg(fid).arg(nowid));
        QWidget *widget=new QWidget(this);
        QLabel *touLabel = new QLabel(widget);
        QLabel *namelabel=new QLabel(widget);
        QLineEdit *idlinet=new QLineEdit(widget);

        //设置不同控件的样式
        widget->setStyleSheet(" background: transparent");
        namelabel->setFixedSize(180,30);
        namelabel->move(80,10);
        namelabel->setText(name);
        namelabel->setAlignment(Qt::AlignLeft);
        namelabel->setAlignment(Qt::AlignVCenter);
        QFont font("微软雅黑",10,50);
        namelabel->setFont(font);
        namelabel->setStyleSheet("color: rgb(70,70,70)");
        touLabel->setFixedSize(50,50);
        //touLabel->setStyleSheet("background:red; border-radius:15px;color:white;");
        touLabel->move(15,15);
        QPixmap pixmap=QPixmap(toux);
        QPixmap fitpixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        touLabel->setPixmap(fitpixmap);
        touLabel-> setScaledContents(true);
        //QIcon icon3(":/image/WeCloudIcon2.png");
        idlinet->setText(fid);
        idlinet->hide();
        QListWidgetItem *item=new QListWidgetItem;
        QSize size = item->sizeHint();
        item->setSizeHint(QSize(size.width(), 80));
        ui->listWidget_2->addItem(item);
        widget->setSizeIncrement(size.width(), 80);
        ui->listWidget_2->setItemWidget(item, widget);
        item->setSelected(true);
        ui->listWidget_2->frdid=fid;
    }
    else
    {
        int flag=0;
        for(int i=0;i<num;i++)
        {
            QListWidgetItem *olditem=ui->listWidget_2->item(i);
            QWidget* pwig = ui->listWidget_2->itemWidget(olditem);
            QList<QLineEdit*> linedList = pwig->findChildren<QLineEdit*>();
            foreach(QLineEdit *lined, linedList)
            {
                if(!lined->text().isEmpty())
                {
                    if(fid==lined->text())
                    {
                        flag=1;
                        olditem->setSelected(true);
                        break;
                    }
                }
            }
        }
        if(flag==0)
        {
            frdlist2=frdlist1+"|"+fid;
            query.exec(QString("update talklist set user_friend='%1' where user_id='%2'").arg(frdlist2).arg(nowid));
            QWidget *widget=new QWidget(this);
            QLabel *touLabel = new QLabel(widget);
            QLabel *namelabel=new QLabel(widget);
            QLineEdit *idlinet=new QLineEdit(widget);

            //设置不同控件的样式
            widget->setStyleSheet(" background: transparent");
            namelabel->setFixedSize(180,30);
            namelabel->move(80,10);
            namelabel->setText(name);
            namelabel->setAlignment(Qt::AlignLeft);
            namelabel->setAlignment(Qt::AlignVCenter);
            QFont font("微软雅黑",10,50);
            namelabel->setFont(font);
            namelabel->setStyleSheet("color: rgb(70,70,70)");
            touLabel->setFixedSize(50,50);
            //touLabel->setStyleSheet("background:red; border-radius:15px;color:white;");
            touLabel->move(15,15);
            QPixmap pixmap=QPixmap(toux);
            QPixmap fitpixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            touLabel->setPixmap(fitpixmap);
            touLabel-> setScaledContents(true);
            //QIcon icon3(":/image/WeCloudIcon2.png");
            idlinet->setText(fid);
            idlinet->hide();
            QListWidgetItem *item=new QListWidgetItem;
            QSize size = item->sizeHint();
            item->setSizeHint(QSize(size.width(), 80));
            ui->listWidget_2->insertItem(0,item);
            widget->setSizeIncrement(size.width(), 80);
            ui->listWidget_2->setItemWidget(item, widget);
            item->setSelected(true);
            ui->listWidget_2->frdid=fid;
        }
    }
}

void MainWindow::selectFile()
{
    this->fileSocket = new QTcpSocket(this);
    fileSocket->abort();
    fileSocket->connectToHost(ip_address,8888);
    ////文件传送进度更新
    connect(fileSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateFileProgress(qint64)));
    connect(fileSocket,SIGNAL(readyRead()),this,SLOT(updateFileProgress()));
    this->filename = QFileDialog::getOpenFileName(this,"Open a file","/","files (*)");
}

void MainWindow::sendFile()
{
    this->localFile = new QFile(filename);
    if(!localFile->open(QFile::ReadOnly))
    {
        QMessageBox::critical(this,"失败","文件传输失败");
        return;
    }
    ///获取文件大小
    this->totalBytes = localFile->size();
    QDataStream sendout(&outBlock,QIODevice::WriteOnly);
    sendout.setVersion(QDataStream::Qt_4_8);
    QString currentFileName = filename.right(filename.size()-filename.lastIndexOf('/')-1);

    qDebug()<<sizeof(currentFileName);
    ////保留总代大小信息空间、文件名大小信息空间、文件名
    sendout<<qint64(0)<<qint64(0)<<currentFileName;
    totalBytes += outBlock.size();
    sendout.device()->seek(0);
    sendout<<totalBytes<<qint64((outBlock.size()-sizeof(qint64)*2));

    bytestoWrite = totalBytes-fileSocket->write(outBlock);
    outBlock.resize(0);
}

void MainWindow::updateFileProgress(qint64 numBytes)
{
    ////已经发送的数据大小
    bytesWritten += (int)numBytes;

    ////如果已经发送了数据
    if(bytestoWrite > 0)
    {
        outBlock = localFile->read(qMin(bytestoWrite,perDataSize));
        ///发送完一次数据后还剩余数据的大小
        bytestoWrite -= ((int)fileSocket->write(outBlock));
        ///清空发送缓冲区
        outBlock.resize(0);
    }
    else
        localFile->close();

    ////如果发送完毕
    if(bytesWritten == totalBytes)
    {
        localFile->close();
        //fileSocket->close();
    }
}

void MainWindow::updateFileProgress()
{
    QDataStream inFile(this->fileSocket);
    inFile.setVersion(QDataStream::Qt_4_8);

    ///如果接收到的数据小于16个字节，保存到来的文件头结构
    if(bytesReceived <= sizeof(qint64)*2)
    {
        if((fileSocket->bytesAvailable()>=(sizeof(qint64))*2) && (filenameSize==0))
        {
            inFile>>totalBytes>>filenameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if((fileSocket->bytesAvailable()>=filenameSize) && (filenameSize != 0))
        {
            inFile>>filename;
            bytesReceived += filenameSize;
            filename = "ServerData/"+filename;
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
        bytesReceived += fileSocket->bytesAvailable();
        inBlock = fileSocket->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }

    ////数据接收完成时
    if(bytesReceived == totalBytes)
    {
        qDebug()<<"Receive file successfully!";
        bytesReceived = 0;
        totalBytes = 0;
        filenameSize = 0;
        localFile->close();
        //fileSocket->close();
    }
}




void MainWindow::initial_friendlist()
{
    ui->listWidget->clear();
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec(QString("select touxiang from userdata where user_id='%1'").arg(nowid));
    QString toux;
    if(query.next())
        {
            toux=query.value(0).toString();
        }
    QPixmap touxiang;
    touxiang.load(toux);
    ui->pushButton_6->setIcon(touxiang);
    QString str=QString("select user_friend from userfriend where user_id='%1'").arg(nowid);
    query.exec(str);
    QString frd;
    if(query.next())
    {
        frd=query.value(0).toString();
    }
    if(frd.isEmpty())return;
    QStringList frdlist=frd.split("|");
    for(int i=0;i<frdlist.count();i++)
    {
        QString str1=QString("select user_name,touxiang from userdata where user_id='%1'").arg(frdlist[i]);
        query.exec(str1);
        QString name;
        QString toux;
        if(query.next())
        {
            name=query.value(0).toString();
            toux=query.value(1).toString();
        }
        QWidget *widget=new QWidget(this);
        QLabel *touLabel = new QLabel(widget);
        QLabel *namelabel=new QLabel(widget);
        QLineEdit *idlinet=new QLineEdit(widget);

        //设置不同控件的样式
        widget->setStyleSheet(" background: transparent");
        namelabel->setFixedSize(180,60);
        namelabel->move(80,10);
        namelabel->setText(name);
        namelabel->setAlignment(Qt::AlignLeft);
        namelabel->setAlignment(Qt::AlignVCenter);
        QFont font("微软雅黑",11,50);
        namelabel->setFont(font);
        namelabel->setStyleSheet("color: rgb(70,70,70)");
        touLabel->setFixedSize(50,50);
        //touLabel->setStyleSheet("background:red; border-radius:15px;color:white;");
        touLabel->move(15,15);
        QPixmap pixmap=QPixmap(toux);
        QPixmap fitpixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        touLabel->setPixmap(fitpixmap);
        touLabel-> setScaledContents(true);
        //QIcon icon3(":/image/WeCloudIcon2.png");
        idlinet->setText(frdlist[i]);
        idlinet->hide();
        QListWidgetItem *item=new QListWidgetItem;
        QSize size = item->sizeHint();
        item->setSizeHint(QSize(size.width(), 80));
        ui->listWidget->addItem(item);
        widget->setSizeIncrement(size.width(), 80);
        ui->listWidget->setItemWidget(item, widget);
    }
}

void MainWindow::initial_talklist()
{
    ui->listWidget_2->clear();
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec(QString("select touxiang from userdata where user_id='%1'").arg(nowid));
    QString toux;
    if(query.next())
        {
            toux=query.value(0).toString();
        }
    QPixmap touxiang;
    touxiang.load(toux);
    ui->pushButton_6->setIcon(touxiang);
    QString str=QString("select user_friend from talklist where user_id='%1'").arg(nowid);
    query.exec(str);
    QString frd;
    if(query.next())
    {
        frd=query.value(0).toString();
    }
    if(frd.isEmpty())return;
    QStringList frdlist=frd.split("|");
    for(int i=0;i<frdlist.count();i++)
    {
        QString str1=QString("select user_name,touxiang from userdata where user_id='%1'").arg(frdlist[i]);
        query.exec(str1);
        QString name;
        QString toux;
        if(query.next())
        {
            name=query.value(0).toString();
            toux=query.value(1).toString();
        }
        QWidget *widget=new QWidget(this);
        QLabel *touLabel = new QLabel(widget);
        QLabel *namelabel=new QLabel(widget);
        QLineEdit *idlinet=new QLineEdit(widget);

        //设置不同控件的样式
        widget->setStyleSheet(" background: transparent");
        namelabel->setFixedSize(180,30);
        namelabel->move(80,10);
        namelabel->setText(name);
        namelabel->setAlignment(Qt::AlignLeft);
        namelabel->setAlignment(Qt::AlignVCenter);
        QFont font("微软雅黑",10,50);
        namelabel->setFont(font);
        namelabel->setStyleSheet("color: rgb(70,70,70)");
        touLabel->setFixedSize(50,50);
        //touLabel->setStyleSheet("background:red; border-radius:15px;color:white;");
        touLabel->move(15,15);
        QPixmap pixmap=QPixmap(toux);
        QPixmap fitpixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        touLabel->setPixmap(fitpixmap);
        touLabel-> setScaledContents(true);
        //QIcon icon3(":/image/WeCloudIcon2.png");
        idlinet->setText(frdlist[i]);
        idlinet->hide();
        QListWidgetItem *item=new QListWidgetItem;
        QSize size = item->sizeHint();
        item->setSizeHint(QSize(size.width(), 80));
        ui->listWidget_2->addItem(item);
        widget->setSizeIncrement(size.width(), 80);
        ui->listWidget_2->setItemWidget(item, widget);
        item->setSelected(true);
        ui->listWidget_2->frdid=frdlist[i];
    }
}

void MainWindow::frdinform_display()
{
    ui->widget_5->show();
    QString fid=ui->listWidget->frdid;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString str=QString("select user_name,user_sex,year,month,date,user_state,user_city,signature,canlookover,touxiang from userdata where user_id='%1'").arg(fid);
    query.exec(str);
    QString name;
    int sex=1;
    QString yearr;
    QString monthh;
    QString datee;
    QString state;
    QString city;
    QString sign;
    int lookover=1;
    QString toux;

    if(query.next())
    {
        name=query.value(0).toString();
        sex=query.value(1).toInt();
        yearr=query.value(2).toString();
        monthh=query.value(3).toString();
        datee=query.value(4).toString();
        state=query.value(5).toString();
        city=query.value(6).toString();
        sign=query.value(7).toString();
        lookover=query.value(8).toInt();
        toux=query.value(9).toString();
    }
    if(lookover==1||lookover==2)
    {
        ui->label_24->setText(fid);
        if(!name.isEmpty())
        {
            ui->label_22->setText(name);
            ui->label_22->adjustSize();
            int a=ui->label_22->width();
            int b=ui->label_22->y();
            ui->label_22->move(235-a/2,b);
        }
        else
        {
            ui->label_22->setText("");
            ui->label_22->adjustSize();
            int a=ui->label_22->width();
            int b=ui->label_22->y();
            ui->label_22->move(235-a/2,b);
        }
        if(sex==1)
        {
            int aa=ui->label_22->width();
            int bb=ui->label_22->y();
            ui->label_23->move(235+aa/2+1,bb);
            ui->label_23->show();
            ui->label_33->hide();
        }
        else
        {
            int aa=ui->label_22->width();
            int bb=ui->label_22->y();
            ui->label_33->move(235+aa/2+1,bb);
            ui->label_23->hide();
            ui->label_33->show();
        }
        if(!yearr.isEmpty())
        {
            ui->label_25->setText(yearr+" "+monthh+" "+datee);
        }
        if(!state.isEmpty())
            ui->label_26->setText(state+" "+city);
        QPixmap pixmap=QPixmap(toux);
        QPixmap fitpixmap = pixmap.scaled(121, 121, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label_21->setPixmap(fitpixmap);
    }
    else if(lookover==3)
    {
        ui->label_24->setText(fid);
        if(!name.isEmpty())
        {
            ui->label_22->setText(name);
            ui->label_22->adjustSize();
            int a=ui->label_22->width();
            int b=ui->label_22->y();
            ui->label_22->move(235-a/2,b);
        }
        if(sex==1)
        {
            int aa=ui->label_22->width();
            int bb=ui->label_22->y();
            ui->label_23->move(235+aa/2+1,bb);
            ui->label_23->show();
            ui->label_33->hide();
        }
        else
        {
            int aa=ui->label_22->width();
            int bb=ui->label_22->y();
            ui->label_33->move(235+aa/2+1,bb);
            ui->label_23->hide();
            ui->label_33->show();
        }
        if(!yearr.isEmpty())
        {
            ui->label_25->setText("- -");
        }
        if(!state.isEmpty())
            ui->label_26->setText("- -");
        QPixmap pixmap=QPixmap(toux);
        QPixmap fitpixmap = pixmap.scaled(121, 121, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label_21->setPixmap(fitpixmap);
    }
}

void MainWindow::delete_frd()
{
    QString fid=ui->listWidget->frdid;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString stq=QString("select user_friend from userfriend where user_id='%1'").arg(nowid);
    query.exec(stq);
    QString frd;
    if(query.next())
    {
        frd=query.value(0).toString();
    }
    QStringList frdlist=frd.split("|");
    frdlist.removeOne(fid);
    QString frd1=frdlist.join("|");
    QString str=QString("update userfriend set user_friend='%1' where user_id='%2'").arg(frd1).arg(nowid);
    query.exec(str);

    QString sts=QString("select user_friend from userfriend where user_id='%1'").arg(fid);
    query.exec(sts);
    QString frd2;
    if(query.next())
    {
        frd2=query.value(0).toString();
    }
    QStringList frdlist1=frd2.split("|");
    frdlist1.removeOne(nowid);
    QString frd3=frdlist1.join("|");
    QString stx=QString("update userfriend set user_friend='%1' where user_id='%2'").arg(frd3).arg(fid);
    query.exec(stx);
    initial_friendlist();
    ui->widget_5->hide();
}

void MainWindow::set_top()
{
    int num=ui->listWidget_2->count();
    QString fid=ui->listWidget_2->frdid;
    for(int i=0;i<num;i++)
    {
        QListWidgetItem *olditem=ui->listWidget_2->item(i);
        QWidget* pwig = ui->listWidget_2->itemWidget(olditem);
        QList<QLineEdit*> linedList = pwig->findChildren<QLineEdit*>();
        foreach(QLineEdit *lined, linedList)
        {
            if(!lined->text().isEmpty())
            {
                if(fid==lined->text())
                {
                    ui->listWidget_2->takeItem(i);
                    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
                    QSqlQuery query(db);
                    QString str1=QString("select user_name,touxiang from userdata where user_id='%1'").arg(fid);
                    query.exec(str1);
                    QString name;
                    QString toux;
                    if(query.next())
                    {
                        name=query.value(0).toString();
                        toux=query.value(1).toString();
                    }
                    QWidget *widget=new QWidget(this);
                    QLabel *touLabel = new QLabel(widget);
                    QLabel *namelabel=new QLabel(widget);
                    QLineEdit *idlinet=new QLineEdit(widget);

                    widget->setStyleSheet(" background: transparent");
                    namelabel->setFixedSize(180,30);
                    namelabel->move(80,10);
                    namelabel->setText(name);
                    namelabel->setAlignment(Qt::AlignLeft);
                    namelabel->setAlignment(Qt::AlignVCenter);
                    QFont font("微软雅黑",10,50);
                    namelabel->setFont(font);
                    namelabel->setStyleSheet("color: rgb(70,70,70)");
                    touLabel->setFixedSize(50,50);
                    touLabel->move(15,15);
                    QPixmap pixmap=QPixmap(toux);
                    QPixmap fitpixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                    touLabel->setPixmap(fitpixmap);
                    touLabel-> setScaledContents(true);
                    idlinet->setText(fid);
                    idlinet->hide();
                    QListWidgetItem *item=new QListWidgetItem;
                    QSize size = item->sizeHint();
                    item->setSizeHint(QSize(size.width(), 80));
                    ui->listWidget_2->insertItem(0,item);
                    widget->setSizeIncrement(size.width(), 80);
                    ui->listWidget_2->setItemWidget(item, widget);
                    item->setSelected(true);
                    break;
                }
            }
        }
    }
}

void MainWindow::delete_talk()
{
    int num=ui->listWidget_2->count();
    QString fid=ui->listWidget_2->frdid;
    for(int i=0;i<num;i++)
    {
        QListWidgetItem *olditem=ui->listWidget_2->item(i);
        QWidget* pwig = ui->listWidget_2->itemWidget(olditem);
        QList<QLineEdit*> linedList = pwig->findChildren<QLineEdit*>();
        foreach(QLineEdit *lined, linedList)
        {
            if(!lined->text().isEmpty())
            {
                if(fid==lined->text())
                {
                    ui->listWidget_2->takeItem(i);
                    break;
                }
            }
        }
    }
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString stq=QString("select user_friend from talklist where user_id='%1'").arg(nowid);
    query.exec(stq);
    QString frd;
    if(query.next())
    {
        frd=query.value(0).toString();
    }
    QStringList frdlist=frd.split("|");
    frdlist.removeOne(fid);
    QString frd1=frdlist.join("|");
    QString str=QString("update talklist set user_friend='%1' where user_id='%2'").arg(frd1).arg(nowid);
    query.exec(str);

    QString sts=QString("select user_friend from talklist where user_id='%1'").arg(fid);
    query.exec(sts);
    QString frd2;
    if(query.next())
    {
        frd2=query.value(0).toString();
    }
    QStringList frdlist1=frd2.split("|");
    frdlist1.removeOne(nowid);
    QString frd3=frdlist1.join("|");
    QString stx=QString("update talklist set user_friend='%1' where user_id='%2'").arg(frd3).arg(fid);
    query.exec(stx);
}

void MainWindow::talkto()
{
    ui->listWidget_3->clear();
    QString fid=ui->listWidget_2->frdid;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("delete from talkuser");
    query.exec(QString("insert into talkuser (user_id) values('%1')").arg(fid));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    m_movePos = event->globalPos() - pos();

    return QMainWindow::mousePressEvent(event);
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressed
        && (event->buttons()== Qt::LeftButton)
        && (event->globalPos() - m_movePos).manhattanLength() > QApplication::startDragDistance())
    {
        QPoint movePos = event->globalPos() - m_movePos;
        this->move(movePos);
        m_movePos = event->globalPos() - pos();
    }

    return QMainWindow::mouseMoveEvent(event);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;

    return QMainWindow::mouseReleaseEvent(event);
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->textEdit)
    {
        if(event->type() == QEvent::KeyPress)//回车键
        {
             QKeyEvent *k = static_cast<QKeyEvent *>(event);
             if(k->key() == Qt::Key_Return)
             {
                 on_pushButton_11_clicked();
                 return true;
             }
        }
    }
    return QWidget::eventFilter(target,event);
}

/*void MainWindow::resizeEvent(QResizeEvent *event)

{
    Q_UNUSED(event)
    ui->textEdit->resize(ui->listWidget_3->width() - 20, ui->widget->height() - 20);
    for(int i = 0; i < ui->listWidget_3->count(); i++)
    {
        QNChatMessage* messageW = qobject_cast<QNChatMessage*>(ui->listWidget_3->itemWidget(ui->listWidget_3->item(i)));
        QListWidgetItem* item = ui->listWidget_3->item(i);
        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }

}*/

void MainWindow::on_pushButton_2_clicked()
{
    bool a=QProcess::startDetached("C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe",QStringList());
    if(!a)QDesktopServices::openUrl(QUrl("https://im.qq.com/pcqq"));
}

void MainWindow::on_pushButton_clicked()
{
    bool a=QProcess::startDetached("C:\\Program Files (x86)\\Tencent\\WeChat\\WeChat.exe",QStringList());
    if(!a)QDesktopServices::openUrl(QUrl("https://weixin.qq.com"));
}

void MainWindow::on_pushButton_3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.weibo.com"));
}

void MainWindow::on_pushButton_4_clicked()
{
    close();
}

void MainWindow::on_pushButton_5_clicked()
{
    showMinimized();
}

void MainWindow::on_pushButton_7_clicked()
{
    setting a;
    login b;
    if(a.exec()==QDialog::Accepted)
    {
       this->hide();
        if(b.exec()==QDialog::Accepted)
        {
            ui->widget_3->hide();
            ui->widget_4->hide();
            ui->widget_5->hide();
            ui->pushButton_8->setChecked(false);
            ui->pushButton_15->setChecked(false);
            nowid=b.getid();
            initial_friendlist();
            initial_talklist();
            b.close();
            this->show();
        }
    }
    else
    {
        ifopen=false;
    }
}

void MainWindow::on_pushButton_15_clicked(bool checked)
{
    if(!checked)
    {
        ui->widget_3->hide();
    }
    else ui->widget_3->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    inform a(nowid);
    a.exec();
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec(QString("select touxiang from userdata where user_id='%1'").arg(nowid));
    QString toux;
    if(query.next())
    {
        toux=query.value(0).toString();
    }
    ui->pushButton_6->setIcon(QIcon(toux));
}

void MainWindow::on_pushButton_17_clicked()
{
    this->hide();
    login a;
    if(a.exec()==QDialog::Accepted)
    {
        nowid=a.getid();
        initial_friendlist();
        initial_talklist();
        ui->widget_3->hide();
        ui->widget_4->hide();
        ui->widget_5->hide();
        ui->pushButton_8->setChecked(false);
        ui->pushButton_15->setChecked(false);
        a.close();
        this->show();
    }
    else
    {
        ifopen=false;
    }
}

void MainWindow::on_pushButton_19_clicked()
{
    ui->widget_2->hide();
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->widget_2->show();
    ui->widget_3->hide();
    ui->pushButton_15->setChecked(false);
}

void MainWindow::on_pushButton_8_clicked(bool checked)
{
    if(!checked)
    {
        ui->widget_4->hide();
    }
    else ui->widget_4->show();
}

void MainWindow::on_pushButton_20_clicked()
{
    addfrd a;
    ui->widget_4->hide();
    ui->pushButton_8->setChecked(false);
    a.exec();
    initial_friendlist();
}

void MainWindow::on_pushButton_23_clicked()
{
    ui->listWidget_3->clear();
    ui->tabWidget->setCurrentWidget(ui->tab_3);
    QString fid=ui->label_24->text();
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("delete from talkuser");
    query.exec(QString("insert into talkuser (user_id) values('%1')").arg(fid));
    QString str1=QString("select user_name,touxiang from userdata where user_id='%1'").arg(fid);
    query.exec(str1);
    QString name;
    QString toux;
    if(query.next())
    {
        name=query.value(0).toString();
        toux=query.value(1).toString();
    }
    int num=ui->listWidget_2->count();
    if(num==0)
    {
        QWidget *widget=new QWidget(this);
        QLabel *touLabel = new QLabel(widget);
        QLabel *namelabel=new QLabel(widget);
        QLineEdit *idlinet=new QLineEdit(widget);

        //设置不同控件的样式
        widget->setStyleSheet(" background: transparent");
        namelabel->setFixedSize(180,30);
        namelabel->move(80,10);
        namelabel->setText(name);
        namelabel->setAlignment(Qt::AlignLeft);
        namelabel->setAlignment(Qt::AlignVCenter);
        QFont font("微软雅黑",10,50);
        namelabel->setFont(font);
        namelabel->setStyleSheet("color: rgb(70,70,70)");
        touLabel->setFixedSize(50,50);
        //touLabel->setStyleSheet("background:red; border-radius:15px;color:white;");
        touLabel->move(15,15);
        QPixmap pixmap=QPixmap(toux);
        QPixmap fitpixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        touLabel->setPixmap(fitpixmap);
        touLabel-> setScaledContents(true);
        //QIcon icon3(":/image/WeCloudIcon2.png");
        idlinet->setText(fid);
        idlinet->hide();
        QListWidgetItem *item=new QListWidgetItem;
        QSize size = item->sizeHint();
        item->setSizeHint(QSize(size.width(), 80));
        ui->listWidget_2->addItem(item);
        widget->setSizeIncrement(size.width(), 80);
        ui->listWidget_2->setItemWidget(item, widget);
        item->setSelected(true);
    }
    else
    {
        int flag=0;
        for(int i=0;i<num;i++)
        {
            QListWidgetItem *olditem=ui->listWidget_2->item(i);
            QWidget* pwig = ui->listWidget_2->itemWidget(olditem);
            QList<QLineEdit*> linedList = pwig->findChildren<QLineEdit*>();
            foreach(QLineEdit *lined, linedList)
            {
                if(!lined->text().isEmpty())
                {
                    if(fid==lined->text())
                    {
                        flag=1;
                        olditem->setSelected(true);
                        break;
                    }
                }
            }
        }
        if(flag==0)
        {
            QWidget *widget=new QWidget(this);
            QLabel *touLabel = new QLabel(widget);
            QLabel *namelabel=new QLabel(widget);
            QLineEdit *idlinet=new QLineEdit(widget);

            //设置不同控件的样式
            widget->setStyleSheet(" background: transparent");
            namelabel->setFixedSize(180,30);
            namelabel->move(80,10);
            namelabel->setText(name);
            namelabel->setAlignment(Qt::AlignLeft);
            namelabel->setAlignment(Qt::AlignVCenter);
            QFont font("微软雅黑",10,50);
            namelabel->setFont(font);
            namelabel->setStyleSheet("color: rgb(70,70,70)");
            touLabel->setFixedSize(50,50);
            //touLabel->setStyleSheet("background:red; border-radius:15px;color:white;");
            touLabel->move(15,15);
            QPixmap pixmap=QPixmap(toux);
            QPixmap fitpixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            touLabel->setPixmap(fitpixmap);
            touLabel-> setScaledContents(true);
            //QIcon icon3(":/image/WeCloudIcon2.png");
            idlinet->setText(fid);
            idlinet->hide();
            QListWidgetItem *item=new QListWidgetItem;
            QSize size = item->sizeHint();
            item->setSizeHint(QSize(size.width(), 80));
            ui->listWidget_2->insertItem(0,item);
            widget->setSizeIncrement(size.width(), 80);
            ui->listWidget_2->setItemWidget(item, widget);
            item->setSelected(true);
        }
    }
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->pushButton_24->show();
    if(!arg1.isEmpty())
    {
        int num=ui->listWidget->count();
        for(int i=0;i<num;i++)
        {
            QListWidgetItem *olditem=ui->listWidget->item(i);
            QWidget* pwig = ui->listWidget->itemWidget(olditem);
            QList<QLabel*> linedList = pwig->findChildren<QLabel*>();
            foreach(QLabel *lined, linedList)
            {
                if(!lined->text().isEmpty())
                {
                    if(lined->text().contains(arg1,Qt::CaseInsensitive))
                    {
                        QList<QLineEdit*> linedList2 = pwig->findChildren<QLineEdit*>();
                        foreach(QLineEdit *lined2, linedList2)
                        {
                            if(!lined2->text().isEmpty())
                            {
                                QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
                                QSqlQuery query(db);
                                QString str1=QString("select user_name,touxiang from userdata where user_id='%1'").arg(lined2->text());
                                query.exec(str1);
                                QString name;
                                QString toux;
                                if(query.next())
                                {
                                    name=query.value(0).toString();
                                    toux=query.value(1).toString();
                                }
                                QWidget *widget=new QWidget(this);
                                QLabel *touLabel = new QLabel(widget);
                                QLabel *namelabel=new QLabel(widget);
                                QLineEdit *idlinet=new QLineEdit(widget);

                                widget->setStyleSheet(" background: transparent");
                                namelabel->setFixedSize(180,60);
                                namelabel->move(80,10);
                                namelabel->setText(name);
                                namelabel->setAlignment(Qt::AlignLeft);
                                namelabel->setAlignment(Qt::AlignVCenter);
                                QFont font("微软雅黑",11,50);
                                namelabel->setFont(font);
                                namelabel->setStyleSheet("color: rgb(70,70,70)");
                                touLabel->setFixedSize(50,50);
                                touLabel->move(15,15);
                                QPixmap pixmap=QPixmap(toux);
                                QPixmap fitpixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                                touLabel->setPixmap(fitpixmap);
                                touLabel-> setScaledContents(true);
                                idlinet->setText(lined2->text());
                                idlinet->hide();
                                QListWidgetItem *item=new QListWidgetItem;
                                QSize size = item->sizeHint();
                                item->setSizeHint(QSize(size.width(), 80));
                                ui->listWidget->addItem(item);
                                widget->setSizeIncrement(size.width(), 80);
                                ui->listWidget->setItemWidget(item, widget);
                            }
                        }
                    }
                }
            }
        }
        for(int i=0;i<num;i++)
        {
            ui->listWidget->takeItem(0);
        }
    }
    else
    {
        initial_friendlist();
    }
}

void MainWindow::on_pushButton_24_clicked()
{
    ui->lineEdit_2->clear();
    ui->pushButton_24->hide();
}

void MainWindow::on_commandLinkButton_clicked()
{
    QUrl url("https://www.cnblogs.com/wqvincent/");
    QDesktopServices::openUrl(url);
}

void MainWindow::on_pushButton_18_clicked()
{
    QMessageBox::information(this,"检查更新","已是最新版本");
}

void MainWindow::on_pushButton_22_clicked()
{
    QMessageBox::information(this,"验证消息","请求添加你为好友");
}
