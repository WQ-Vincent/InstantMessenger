#include "mainwindow.h"
#include "regist.h"
#include "ui_regist.h"

regist::regist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regist)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText(" 用户名");
    ui->lineEdit_2->setPlaceholderText(" 密码");
    ui->lineEdit_3->setPlaceholderText(" 手机号码");
    ui->lineEdit_4->setPlaceholderText(" 再次输入密码");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->widget->hide();
}

regist::~regist()
{
    delete ui;
}

void regist::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    m_movePos = event->globalPos() - pos();

    return QDialog::mousePressEvent(event);
}
void regist::mouseMoveEvent(QMouseEvent *event)
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
void regist::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;

    return QDialog::mouseReleaseEvent(event);
}


void regist::on_pushButton_clicked()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int flr=1;
    for(int i=0;i<5;i++)
    {
        if(ifregist[i]==0)
        {
            flr=0;
            break;
        }
    }
    if(flr==0)return;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString name = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString password2 = ui->lineEdit_4->text();
    QString phone = ui->lineEdit_3->text();
    int sex=1;
    int search=1;
    int add=2;
    int lookover=1;
    QString toux=":/touxiang/Simpson.jpg";

    QString id;
    bool flagg=false;
    while(flagg==false)
    {
        flagg=true;
        int idnumber=qrand()%10000;
        id=QString::number(idnumber,10);
        query.exec("select user_id from user_infrom");
        while(query.next())
        {
            QString oldid=query.value(0).toString();
            if(id==oldid)
            {
                flagg=false;
                break;
            }
        }
    }

    QString str = QString("insert into user_inform(user_id, user_password, phonenumber) values('%1', '%2', '%3')").arg(id).arg(password).arg(phone);
    QString str2 = QString("insert into userdata(user_id,user_name,user_sex,phonenumber,cansearch,canlookover,addway,touxiang) values('%1','%2','%3','%4','%5','%6','%7','%8')").arg(id).arg(name).arg(sex).arg(phone).arg(search).arg(lookover).arg(add).arg(toux);
    QString str3 = QString("insert into userfriend(user_id) values('%1')").arg(id);
    QString str4 = QString("insert into talklist(user_id) values('%1')").arg(id);
    bool flag=query.exec(str);
    bool flag2=query.exec(str2);
    bool flag3=query.exec(str3);
    bool flag4=query.exec(str4);
    if(flag&&flag2&&flag3&&flag4)
    {
        ui->widget->show();
        ui->label_10->setText(id);
        ui->label_10->adjustSize();
        int a=ui->label_10->width();
        int b=ui->label_10->y();
        ui->label_10->move(260-a/2,b);
    }
    else QMessageBox::warning(this,"注册失败","请检查你的输入格式");
}

void regist::on_lineEdit_4_editingFinished()
{
    QString password = ui->lineEdit_2->text();
    QString password2 = ui->lineEdit_4->text();
    if(password!=password2)
    {
        ifregist[0]=0;
        ui->label_5->show();
        ui->lineEdit_2->clear();
        ui->lineEdit_4->clear();
        return;
    }
    else
    {
        ifregist[0]=1;
        ui->label_5->hide();
    }
}

void regist::on_lineEdit_2_editingFinished()
{
    QString password = ui->lineEdit_2->text();
    if(password.isEmpty())
    {
        ifregist[1]=0;
        ui->label_4->show();
        return;
    }
    else
    {
        ifregist[1]=1;
        ui->label_4->hide();
    }
}

void regist::on_lineEdit_editingFinished()
{
    QString name = ui->lineEdit->text();
    if(name.isEmpty())
    {
        ifregist[2]=0;
        ui->label_3->show();
        return;
    }
    else
    {
        ifregist[2]=1;
        ui->label_3->hide();
    }
}

void regist::on_lineEdit_3_editingFinished()
{
    QString phone = ui->lineEdit_3->text();
    if(phone.isEmpty())
    {
        ifregist[3]=0;
        ui->label_6->show();
        return;
    }
    else
    {
        ifregist[3]=1;
        ui->label_6->hide();
    }
    if(phone.length()!=11)
    {
        ifregist[4]=0;
        ui->label_7->show();
        return;
    }
    else
    {
        ifregist[4]=1;
        ui->label_7->hide();
    }
}

void regist::on_pushButton_2_clicked()
{
    close();
}
