#include "changepw.h"
#include "ui_changepw.h"
#include "mainwindow.h"

changepw::changepw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changepw)
{
    ui->setupUi(this);

    ifchange=0;
    ui->lineEdit->setPlaceholderText("旧密码");
    ui->lineEdit_2->setPlaceholderText("新密码");
    ui->lineEdit_3->setPlaceholderText("再次填写新密码");
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();

    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString str=QString("select user_id,user_password from loginuser");
    query.exec(str);
    QString id;
    if(query.next())
    {
        id=query.value(0).toString();
        truepwd=query.value(1).toString();
    }
    ui->label_5->setText(id);
}

changepw::~changepw()
{
    delete ui;
}

void changepw::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    m_movePos = event->globalPos() - pos();

    return QDialog::mousePressEvent(event);
}
void changepw::mouseMoveEvent(QMouseEvent *event)
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
void changepw::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;

    return QDialog::mouseReleaseEvent(event);
}


void changepw::on_pushButton_clicked()
{
    QString id=ui->label_5->text();
    QString pwd=ui->lineEdit_2->text();
    int suc=1;
    for(int i=0;i<3;i++)
    {
        if(ifright[i]==0)suc=0;
    }
    if(suc==0)return;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString str=QString("update user_inform set user_password='%1' where user_id='%2'").arg(pwd).arg(id);
    bool a=query.exec(str);
    QString str1=QString("update loginuser set user_password='%1' where user_id='%2'").arg(pwd).arg(id);
    bool b=query.exec(str1);
    if(a&&b)
    {
        ifchange=1;
        QMessageBox::information(this,"修改成功","修改成功，请重新登录");
        close();
    }
    else
    {
        ifchange=0;
        QMessageBox::critical(this,"操作失败","修改失败，请检查输入格式");
    }
}

void changepw::on_lineEdit_editingFinished()
{
    QString pwd = ui->lineEdit->text();
    if(pwd!=truepwd)
    {
        ifright[0]=0;
        ui->label_6->show();
        ui->lineEdit->clear();
        return;
    }
    else
    {
        ifright[0]=1;
        ui->label_6->hide();
    }
}

void changepw::on_lineEdit_2_editingFinished()
{
    QString newpwd = ui->lineEdit_2->text();
    if(newpwd.isEmpty())
    {
        ifright[1]=0;
        ui->label_7->show();
        return;
    }
    else
    {
        ifright[1]=1;
        ui->label_7->hide();
    }
}

void changepw::on_lineEdit_3_editingFinished()
{
    QString newpwd = ui->lineEdit_2->text();
    QString newpwd2 = ui->lineEdit_3->text();
    if(newpwd!=newpwd2)
    {
        ifright[2]=0;
        ui->label_8->show();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        return;
    }
    else
    {
        ifright[2]=1;
        ui->label_8->hide();
    }
}

