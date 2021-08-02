#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "loginlose.h"
#include "regist.h"
#include "pwback.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setFixedSize(this->width(),this->height());

    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 0);          //设置向哪个方向产生阴影效果(dx,dy)，特别地，(0,0)代表向四周发散
    effect->setColor(Qt::gray);       //设置阴影颜色，也可以setColor(QColor(220,220,220))
    effect->setBlurRadius(20);        //设定阴影的模糊半径，数值越大越模糊
    ui->frame->setGraphicsEffect(effect);

    ui->lineEdit->setPlaceholderText(" 用户名");
    ui->lineEdit_2->setPlaceholderText(" 密码");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString idd,pwd;
    int jizhu=0;
    query.exec("select * from loginuser");
    if(query.next())
    {
        idd=query.value(0).toString();
        pwd=query.value(1).toString();
        jizhu=query.value(2).toInt();
    }
    ui->lineEdit->setText(idd);
    if(jizhu==1)
    {
        ui->lineEdit_2->setText(pwd);
        ui->checkBox_2->setCheckState(Qt::Checked);
    }
    query.exec(QString("select touxiang from userdata where user_id='%1'").arg(idd));
    QString toux;
    if(query.next())
    {
        toux=query.value(0).toString();
    }
    QPixmap img1;
    img1.load(toux);
    if(idd.isEmpty())
        img1.load(":/image/victoricon2.png");
    QPixmap pixMap= img1.scaled(90,90, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pixMap =  PixmapToRound(pixMap, 45);
    ui->label_7->setPixmap(pixMap);
}

login::~login()
{
    delete ui;
}

void login::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    m_movePos = event->globalPos() - pos();

    return QDialog::mousePressEvent(event);
}
void login::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressed && (event->buttons()== Qt::LeftButton)
        && (event->globalPos() - m_movePos).manhattanLength() > QApplication::startDragDistance())
    {
        QPoint movePos = event->globalPos() - m_movePos;
        this->move(movePos);
        m_movePos = event->globalPos() - pos();
    }

    return QDialog::mouseMoveEvent(event);
}
void login::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;

    return QDialog::mouseReleaseEvent(event);
}

QString login::getid()
{
    return trueid;
}

QPixmap login::PixmapToRound(const QPixmap &src, int radius)
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

void login::on_pushButton_3_clicked()
{
    QString id=ui->lineEdit->text();
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString str=QString("select user_password from user_inform where user_id='%1'").arg(id);
    query.exec(str);
    QString truepw;
    if(query.next())
    {
        truepw = query.value(0).toString();
    }
    if(ui->lineEdit_2->text()!=""&&ui->lineEdit_2->text()==truepw)
    {   //加trimmed()可以去除用户名字符串开头和结尾的空白字符
        trueid=id;
        int rem=0;
        if(ui->checkBox_2->isChecked())
            rem=1;
        query.exec("delete from loginuser");
        QString str1=QString("insert into loginuser(user_id,user_password,ifrem) values('%1','%2','%3')").arg(id).arg(truepw).arg(rem);
        query.exec(str1);
        accept();
    }
    else
    {
        loginlose a;
        a.exec();
        ui->lineEdit_2->clear();
        ui->lineEdit_2->setFocus();//将光标移到用户名框内
    }
}

void login::on_pushButton_clicked()
{
    close();
}

void login::on_pushButton_2_clicked()
{
    showMinimized();
}

void login::on_pushButton_4_clicked()
{
    regist a;
    a.exec();
}

void login::on_pushButton_5_clicked()
{
    pwback a;
    a.exec();
}

void login::on_lineEdit_editingFinished()
{
    QString idd=ui->lineEdit->text();
    QSqlDatabase db=QSqlDatabase::database("sqlite1");
    QSqlQuery query(db);
    query.exec(QString("select touxiang from userdata where user_id='%1'").arg(idd));
    QString toux;
    if(query.next())
    {
        toux=query.value(0).toString();
    }
    QPixmap img1;
        img1.load(toux);

        //100,100为QLabel的宽高
        QPixmap pixMap= img1.scaled(90,90, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        //50为圆形的半径
        pixMap =  PixmapToRound(pixMap, 45);

        ui->label_7->setPixmap(pixMap);
}
