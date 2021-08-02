#include "inform.h"
#include "ui_inform.h"
#include "mainwindow.h"

inform::inform(QString id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inform)
{
    ui->setupUi(this);

    nowid=id;
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setFixedSize(this->width(),this->height());

    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 0);          //设置向哪个方向产生阴影效果(dx,dy)，特别地，(0,0)代表向四周发散
    effect->setColor(Qt::gray);       //设置阴影颜色，也可以setColor(QColor(220,220,220))
    effect->setBlurRadius(20);        //设定阴影的模糊半径，数值越大越模糊
    ui->frame->setGraphicsEffect(effect);

    ui->widget->hide();
    ui->widget_2->hide();
    ui->label_19->hide();
    ui->textEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset;color:rgb(100,100,100)");
    ui->textBrowser_2->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textBrowser_3->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textBrowser_4->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textBrowser_5->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textBrowser_6->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textBrowser_6->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setAlignment(Qt::AlignHCenter);
    ui->textEdit1->setStyleSheet("background:transparent;border-style:solid;border-width:1px");

    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString str=QString("select user_name,user_sex,year,month,date,user_state,user_city,signature,touxiang from userdata where user_id='%1'").arg(nowid);
    query.exec(str);

    QString name;
    int sex=1;
    QString yearr;
    QString monthh;
    QString datee;
    QString state;
    QString city;
    QString sign;
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
        toux=query.value(8).toString();
    }
    ui->textBrowser_2->setText(nowid);
    if(!name.isEmpty())
        ui->textEdit->setText(name);
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString nowyear = current_date_time.toString("yyyy");
    QString nowmon = current_date_time.toString("MM");
    QString nowdate = current_date_time.toString("dd");
    int old;
    int oldyear=yearr.left(yearr.length()-1).toInt();
    int oldmon=monthh.left(monthh.length()-1).toInt();
    int olddate=datee.left(datee.length()-1).toInt();
    if(nowmon.toInt()<oldmon||(nowmon.toInt()==oldmon&&nowdate.toInt()<olddate))
    {
        old=nowyear.toInt()-oldyear-1;
    }
    else old=nowyear.toInt()-oldyear;
    QString oldd;
    if(!yearr.isEmpty())
        oldd=oldd.number(old,10)+"岁";
    if(sex==1)
    {
        ui->textBrowser_3->setText("男    "+oldd);
    }
    else ui->textBrowser_3->setText("女    "+oldd);
    if(!yearr.isEmpty())
    {
        ui->textBrowser_4->setText(yearr+" "+monthh+" "+datee);
    }
    if(!state.isEmpty())
        ui->textBrowser_5->setText(state+" "+city);
    if(!sign.isEmpty())
        ui->textBrowser_6->setText(sign);
    QPixmap img1;
        img1.load(toux);
        QPixmap pixMap= img1.scaled(110,110, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pixMap =  PixmapToRound(pixMap, 55);
        ui->label->setPixmap(pixMap);
     QPixmap img2;
         img2.load(toux);

            //100,100为QLabel的宽高
            QPixmap pixMap2= img2.scaled(121,121, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            //50为圆形的半径
            ui->label_18->setPixmap(pixMap2);

    ui->scrollArea->verticalScrollBar()->setStyleSheet("QScrollArea{border:0px solid;"
                                                       "border-radius: 4px;}"
                                                       "QScrollBar:vertical{width: 8px;border:0px solid;"
                                                       "border-radius: 4px;margin: 0px,0px,0px,0px;"
                                                       "background-color: transparent;background:#e1f0fa;}"
                                                       "QScrollBar:vertical:hover{width: 8px;"
                                                       "border:0px solid;margin: 0px,0px,0px,0px;background:#e1f0fa;}"
                                                       "QScrollBar::handle:vertical{width:4px;background:#c0ddee;"
                                                       "border-radius: 4px;height: 40px;}"
                                                       "QScrollBar::handle:vertical:hover{background:#c0ddee;"
                                                       "border-radius: 4px;}"
                                                       "QScrollBar::add-line:vertical{height:11px;background-color: transparent;"
                                                       "subcontrol-position:bottom;border:0px solid;"
                                                       "border-radius: 4px;}"
                                                       "QScrollBar::sub-line:vertical{height:11px;"
                                                       "background-color: transparent;subcontrol-position:top;"
                                                       "border:0px solid;border-radius: 4px;}"
                                                       "QScrollBar::add-page:vertical{background-color: #e1f0fa;"
                                                       "border:0px solid;border-radius: 4px;}"
                                                       "QScrollBar::sub-page:vertical{background-color: #e1f0fa;"
                                                       "border:0px solid;border-radius: 4px;}"
                                                       "QScrollBar::up-arrow:vertical{"
                                                       "border:0px solid;border-radius: 3px;}"
                                                       "QScrollBar::down-arrow:vertical {"
                                                       "border:0px solid;border-radius: 3px;}");
}

inform::~inform()
{
    delete ui;
}

void inform::mousePressEvent(QMouseEvent *event)
{
    if(ui->label_2->geometry().contains(event->pos())
            ||ui->label_8->geometry().contains(event->pos())
            ||ui->label_16->geometry().contains(event->pos()))
    {
        m_pressed = true;
        m_movePos = event->globalPos() - pos();
    }

    return QDialog::mousePressEvent(event);
}
void inform::mouseMoveEvent(QMouseEvent *event)
{
    if(ui->label_2->geometry().contains(event->pos())
            ||ui->label_8->geometry().contains(event->pos())
            ||ui->label_16->geometry().contains(event->pos()))
    {
        if (m_pressed && (event->buttons()== Qt::LeftButton)
            && (event->globalPos() - m_movePos).manhattanLength() > QApplication::startDragDistance())
        {
            QPoint movePos = event->globalPos() - m_movePos;
            this->move(movePos);
            m_movePos = event->globalPos() - pos();
        }
    }

    return QDialog::mouseMoveEvent(event);
}
void inform::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;

    return QDialog::mouseReleaseEvent(event);
}


QPixmap inform::PixmapToRound(const QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }
    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);
    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}

void inform::on_pushButton_clicked()
{
    close();
}

void inform::on_pushButton_2_clicked()
{
    showMinimized();
}

void inform::on_pushButton_3_clicked()
{
    for(int i=2020;i>=1945;i--)
    {
        QString a=QString::number(i,10);
        ui->comboBox_4->addItem(a+"年");
    }
    for(int i=1;i<=31;i++)
    {
        QString a=QString::number(i,10);
        ui->comboBox_6->addItem(a+"日");
    }
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString str=QString("select user_name,user_sex,year,month,date,phonenumber,user_state,user_city,signature from userdata where user_id='%1'").arg(nowid);
    query.exec(str);

    QString name;
    QString phone;
    int sex=1;
    QString yearr;
    QString monthh;
    QString datee;
    QString state;
    QString city;
    QString sign;

    if(query.next())
    {
        name=query.value(0).toString();
        sex=query.value(1).toInt();
        yearr=query.value(2).toString();
        monthh=query.value(3).toString();
        datee=query.value(4).toString();
        phone=query.value(5).toString();
        state=query.value(6).toString();
        city=query.value(7).toString();
        sign=query.value(8).toString();
    }
    ui->widget->show();
    if(!name.isEmpty())
        ui->lineEdit_2->setText(name);
    if(!phone.isEmpty())
        ui->lineEdit->setText(phone);
    if(sex==1)
    {
        ui->comboBox->setCurrentText("男");
    }
    else ui->comboBox->setCurrentText("女");
    if(!yearr.isEmpty())
        ui->comboBox_4->setCurrentText(yearr);
    if(!monthh.isEmpty())
        ui->comboBox_5->setCurrentText(monthh);
    if(!datee.isEmpty())
        ui->comboBox_6->setCurrentText(datee);
    if(!state.isEmpty())
        ui->comboBox_2->setCurrentText(state);
    if(!city.isEmpty())
    {
        on_comboBox_2_activated(state);
        ui->comboBox_3->setCurrentText(city);
    }
    if(!sign.isEmpty())
        ui->textEdit1->setText(sign);
    if(ui->comboBox_3->currentText().isEmpty())
    {
        ui->comboBox_3->clear();
        QFile file(":/other/LocList.xml");
        if (!file.open(QFile::ReadOnly))
            return;
        QDomDocument doc;
        if (!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();

        QDomElement rootElement = doc.documentElement();
        if (rootElement.tagName() != "Location")
            return;

        QDomElement chinaElement;
        QDomNodeList nodeLsit = rootElement.childNodes();
        for (int i=0; i<nodeLsit.count(); ++i)
        {
            QDomElement element = nodeLsit.at(i).toElement();
            if (element.attribute("Name") == "中国")
            {
                chinaElement = element;
                break;
            }
        }
        if (chinaElement.isNull())
            return;
        QDomNodeList chinaNodeList = chinaElement.childNodes();
        for (int i=0; i<chinaNodeList.count(); ++i)
        {
            // 解析省/直辖市
            QDomElement element = chinaNodeList.at(i).toElement();
            if(ui->comboBox_2->currentText()==element.attribute("Name"))
            {
                QDomNodeList cityNodeList = element.childNodes();
                for (int j=0; j<cityNodeList.count(); ++j)
                {
                    QDomElement cityElement = cityNodeList.at(j).toElement();
                    QString cityName = cityElement.attribute("Name");
                    ui->comboBox_3->addItem(cityName);
                }
            }
        }
    }
}

void inform::on_pushButton_4_clicked()
{
    ui->widget->hide();
}

void inform::on_pushButton_5_clicked()
{
    showMinimized();
}

void inform::on_pushButton_6_clicked()
{
    QString name=ui->lineEdit_2->text();
    QString phone=ui->lineEdit->text();
    int sex;
    if(ui->comboBox->currentText()=="男")
        sex=1;
    else sex=0;
    QString yearr=ui->comboBox_4->currentText();
    QString monthh=ui->comboBox_5->currentText();
    QString datee=ui->comboBox_6->currentText();
    QString state=ui->comboBox_2->currentText();
    QString city=ui->comboBox_3->currentText();
    QString sign=ui->textEdit1->toPlainText();
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString str = QString("update user_inform set phonenumber='%1' where user_id='%2'").arg(phone).arg(nowid);
    QString str2 = QString("update userdata set user_name='%1', user_sex='%2',"
                           "year='%3', month='%4', date='%5',"
                           "phonenumber='%6', user_state='%7', user_city='%8', signature='%9'"
                           "where user_id='%10'"
                           ).arg(name).arg(sex).arg(yearr).arg(monthh).arg(datee).arg(phone).arg(state).arg(city).arg(sign).arg(nowid);
    bool flag=query.exec(str);
    bool flag2=query.exec(str2);
    if(flag&&flag2)
    {
        QMessageBox::information(this,"修改成功","修改成功");
        close();
    }
    else QMessageBox::warning(this,"修改失败","请检查你的输入格式");

}

void inform::on_comboBox_2_activated(const QString &arg1)
{
    ui->comboBox_3->clear();
    QFile file(":/other/LocList.xml");
        if (!file.open(QFile::ReadOnly))
            return;

        QDomDocument doc;
        if (!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();

        QDomElement rootElement = doc.documentElement();
        if (rootElement.tagName() != "Location")
            return;

        QDomElement chinaElement;
        QDomNodeList nodeLsit = rootElement.childNodes();
        for (int i=0; i<nodeLsit.count(); ++i)
        {
            QDomElement element = nodeLsit.at(i).toElement();
            if (element.attribute("Name") == "中国")
            {
                chinaElement = element;
                break;
            }
        }

        if (chinaElement.isNull())
            return;

        QDomNodeList chinaNodeList = chinaElement.childNodes();
        for (int i=0; i<chinaNodeList.count(); ++i)
        {
            // 解析省/直辖市
            QDomElement element = chinaNodeList.at(i).toElement();
            if(arg1==element.attribute("Name"))
            {
                QDomNodeList cityNodeList = element.childNodes();
                for (int j=0; j<cityNodeList.count(); ++j)
                {
                    QDomElement cityElement = cityNodeList.at(j).toElement();
                    QString cityName = cityElement.attribute("Name");
                    ui->comboBox_3->addItem(cityName);
                }
            }
        }
}

void inform::on_lineEdit_editingFinished()
{
    QString phone=ui->lineEdit->text();
    if(phone.length()!=11)
    {
        QMessageBox::warning(this,"错误","请输入正确的手机号码");
        ui->lineEdit->clear();
    }
}

void inform::on_comboBox_5_activated(const QString &arg1)
{
    ui->comboBox_6->clear();
    if(arg1=="1月"||arg1=="3月"||arg1=="5月"||arg1=="7月"||arg1=="8月"||arg1=="10月"||arg1=="12月")
    {
        for(int i=1;i<=31;i++)
        {
            ui->comboBox_6->addItem(QString::number(i,10)+"日");
        }
    }
    if(arg1=="4月"||arg1=="6月"||arg1=="9月"||arg1=="11月")
    {
        for(int i=1;i<=30;i++)
        {
            ui->comboBox_6->addItem(QString::number(i,10)+"日");
        }
    }
    if(arg1=="2月")
    {
        QString arg2=ui->comboBox_4->currentText();
        if(!arg2.isEmpty())
        {
            int flag=0;
            QString year;
            for(int i=1945;i<=2020;i++)
            {
                year=QString::number(i,10);
                year+="年";
                if(i%4==0&&year==arg2)
                {
                    flag=1;
                    for(int j=1;j<=29;j++)
                    {
                        QString date=QString::number(j,10);
                        ui->comboBox_6->addItem(date+"日");
                    }
                    break;
                }
            }
            if(flag!=1)
            {
                for(int j=1;j<=28;j++)
                {
                    QString date=QString::number(j,10);
                    ui->comboBox_6->addItem(date+"日");
                }
            }
        }
    }
}

void inform::on_comboBox_4_activated(const QString &arg1)
{
    ui->comboBox_6->clear();
    QString arg2=ui->comboBox_5->currentText();
    if(arg2=="1月"||arg2=="3月"||arg2=="5月"||arg2=="7月"||arg2=="8月"||arg2=="10月"||arg2=="12月")
    {
        for(int i=1;i<=31;i++)
        {
            ui->comboBox_6->addItem(QString::number(i,10)+"日");
        }
    }
    if(arg2=="4月"||arg2=="6月"||arg2=="9月"||arg2=="11月")
    {
        for(int i=1;i<=30;i++)
        {
            ui->comboBox_6->addItem(QString::number(i,10)+"日");
        }
    }
    if(arg2=="2月")
    {
        int flag=0;
        QString year;
        for(int i=1945;i<=2020;i++)
        {
            year=QString::number(i,10);
            year+="年";
            if(i%4==0&&year==arg1)
            {
                flag=1;
                for(int j=1;j<=29;j++)
                {
                    QString date=QString::number(j,10);
                    ui->comboBox_6->addItem(date+"日");
                }
                break;
            }
        }
        if(flag!=1)
        {
            for(int j=1;j<=28;j++)
            {
                QString date=QString::number(j,10);
                ui->comboBox_6->addItem(date+"日");
            }
        }
    }
}
void inform::on_pushButton_30_clicked()
{
    ui->widget_2->show();
}

void inform::on_pushButton_7_clicked()
{
    ui->widget_2->hide();
}

void inform::on_pushButton_8_clicked()
{
    showMinimized();
}

void inform::on_pushButton_9_clicked()
{
    QString toux=ui->label_19->text();
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec(QString("update userdata set touxiang='%1' where user_id='%2'").arg(toux).arg(nowid));
    int with = ui->label->width();
    int height = ui->label->height();
    QPixmap pixmap=QPixmap(toux);
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    fitpixmap=PixmapToRound(fitpixmap,55);
    ui->label->setPixmap(fitpixmap);
    ui->widget_2->hide();
}

void inform::on_pushButton_10_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/beizi.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/beizi.jpg");
}

void inform::on_pushButton_11_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/blownbear.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/blownbear.jpg");
}

void inform::on_pushButton_12_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/panda.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/panda.jpg");
}

void inform::on_pushButton_13_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/icebear.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/icebear.jpg");
}

void inform::on_pushButton_14_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/dog.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/dog.jpg");
}

void inform::on_pushButton_15_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/duolaameng.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/duolaameng.jpg");
}

void inform::on_pushButton_16_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/fenhongbao.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/fenhongbao.jpg");
}

void inform::on_pushButton_17_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/girl.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/girl.jpg");
}

void inform::on_pushButton_18_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/girl2.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/girl2.jpg");
}

void inform::on_pushButton_19_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/girl3.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/girl3.jpg");
}

void inform::on_pushButton_20_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/girl4.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/girl4.jpg");
}

void inform::on_pushButton_21_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/haimianbob.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/haimianbob.jpg");
}

void inform::on_pushButton_22_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/paidaxing.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/paidaxing.jpg");
}

void inform::on_pushButton_23_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/pig.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/pig.jpg");
}

void inform::on_pushButton_24_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/shuaya.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/shuaya.jpg");
}

void inform::on_pushButton_25_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/tom.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/tom.jpg");
}

void inform::on_pushButton_26_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/xiaowanzi.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/xiaowanzi.jpg");
}

void inform::on_pushButton_27_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/xiaoxin.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/xiaoxin.jpg");
}

void inform::on_pushButton_28_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/yazi.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/yazi.jpg");
}

void inform::on_pushButton_29_clicked()
{
    int with = ui->label_18->width();
    int height = ui->label_18->height();
    QPixmap pixmap=QPixmap(":/touxiang/Simpson.jpg");
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_18->setPixmap(fitpixmap);
    ui->label_19->setText(":/touxiang/Simpson.jpg");
}
