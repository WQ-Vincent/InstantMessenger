#include "setting.h"
#include "mainwindow.h"
#include "ui_setting.h"
#include "changepw.h"

setting::setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting)
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

    QButtonGroup* pButtonGroup = new QButtonGroup(this);
    pButtonGroup->addButton(ui->checkBox_4, 1);
    pButtonGroup->addButton(ui->checkBox_5, 2);
    pButtonGroup->addButton(ui->checkBox_6, 3);

    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    int jizhu=0;
    query.exec("select user_id,ifrem from loginuser");
    if(query.next())
    {
        id=query.value(0).toString();
        jizhu=query.value(1).toInt();
    }
    if(jizhu==1)
    {
        ui->checkBox->setCheckState(Qt::Checked);
        ui->label_9->hide();
        ui->label_8->show();
    }
    else
    {
        ui->label_8->hide();
        ui->label_9->show();
    }
    QString str=QString("select cansearch,canlookover from userdata where user_id='%1'").arg(id);
    query.exec(str);
    int search=1;
    int lookover=1;
    if(query.next())
    {
        search=query.value(0).toInt();
        lookover=query.value(1).toInt();
    }
    if(search==1)
    {
        ui->checkBox_2->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_3->setCheckState(Qt::Checked);
    }
    if(lookover==1)
    {
        ui->comboBox->setCurrentText("所有人可见");
    }
    else if(lookover==2)
    {
        ui->comboBox->setCurrentText("仅好友可见");
    }
    else if(lookover==3)
    {
        ui->comboBox->setCurrentText("仅自己可见");
    }
    ui->widget->hide();
    QString str2=QString("select addway,addquestion,addanswer from userdata where user_id='%1'").arg(id);
    query.exec(str2);
    int way=1;
    QString ques,answ;
    if(query.next())
    {
        way=query.value(0).toInt();
        ques=query.value(1).toString();
        answ=query.value(2).toString();
    }
    if(way==1)
    {
        ui->checkBox_4->setCheckState(Qt::Checked);
    }
    else if(way==2)
    {
        ui->checkBox_5->setCheckState(Qt::Checked);
    }
    else if(way==3)
    {
        ui->checkBox_6->setCheckState(Qt::Checked);
        ui->lineEdit_2->setText(ques);
        ui->lineEdit_3->setText(answ);
        ui->widget->show();
    }
}

setting::~setting()
{
    delete ui;
}

void setting::mousePressEvent(QMouseEvent *event)
{
    if(ui->label_3->geometry().contains(event->pos())||ui->label_2->geometry().contains(event->pos()))
    {
        m_pressed = true;
        m_movePos = event->globalPos() - pos();
    }

    return QDialog::mousePressEvent(event);
}
void setting::mouseMoveEvent(QMouseEvent *event)
{
    if(ui->label_3->geometry().contains(event->pos())||ui->label_2->geometry().contains(event->pos()))
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
void setting::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;

    return QDialog::mouseReleaseEvent(event);
}


void setting::on_pushButton_clicked()
{
     close();
}

void setting::on_pushButton_2_clicked()
{
    showMinimized();
}

void setting::on_checkBox_stateChanged(int arg1)
{
    int rem;
    if(arg1==2)
    {
        rem=1;
        ui->label_9->hide();
        ui->label_8->show();
    }
    else
    {
        rem=0;
        ui->label_8->hide();
        ui->label_9->show();
    }
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString str = QString("update loginuser set ifrem='%1' where user_id='%2'").arg(rem).arg(id);
    query.exec(str);
}

void setting::on_pushButton_3_clicked()
{
    changepw a;
    a.exec();
    if(a.ifchange)
    {
        accept();
    }
    else return;
}

void setting::on_checkBox_3_stateChanged(int arg1)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    if(arg1==2)
    {
        ui->checkBox_2->setCheckState(Qt::Unchecked);
        int search=0;
        QString str=QString("update userdata set cansearch='%1' where user_id='%2'").arg(search).arg(id);
        query.exec(str);
    }
    else if(arg1==0)
    {
        ui->checkBox_2->setCheckState(Qt::Checked);
        int search=1;
        QString str=QString("update userdata set cansearch='%1' where user_id='%2'").arg(search).arg(id);
        query.exec(str);
    }
}

void setting::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1==2)
    {
        ui->checkBox_3->setCheckState(Qt::Unchecked);
    }
    else if(arg1==0)
    {
        ui->checkBox_3->setCheckState(Qt::Checked);
    }
}

void setting::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1==2)
    {
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        int way=1;
        QString str=QString("update userdata set addway='%1' where user_id='%2'").arg(way).arg(id);
        query.exec(str);
    }
    else return;
}

void setting::on_checkBox_5_stateChanged(int arg1)
{
    if(arg1==2)
    {
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        int way=2;
        QString str=QString("update userdata set addway='%1' where user_id='%2'").arg(way).arg(id);
        query.exec(str);
    }
    else return;
}

void setting::on_checkBox_6_stateChanged(int arg1)
{
    if(arg1==2)
    {
        ui->widget->show();
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        int way=3;
        QString str=QString("update userdata set addway='%1' where user_id='%2'").arg(way).arg(id);
        query.exec(str);
    }
    else
    {
        ui->widget->hide();
        return;
    }
}

void setting::on_lineEdit_2_editingFinished()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString ques=ui->lineEdit_2->text();
    QString answ=ui->lineEdit_3->text();
    QString str=QString("update userdata set addquestion='%1',addanswer='%2' where user_id='%3'").arg(ques).arg(answ).arg(id);
    query.exec(str);
}

void setting::on_lineEdit_3_editingFinished()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString ques=ui->lineEdit_2->text();
    QString answ=ui->lineEdit_3->text();
    QString str=QString("update userdata set addquestion='%1',addanswer='%2' where user_id='%3'").arg(ques).arg(answ).arg(id);
    query.exec(str);
}

void setting::on_comboBox_activated(const QString &arg1)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    int lookover=1;
    if(arg1=="所有人可见")
        lookover=1;
    else if(arg1=="仅好友可见")
        lookover=2;
    else if(arg1=="仅自己可见")
        lookover=3;
    query.exec(QString("update userdata set canlookover='%1' where user_id='%2'").arg(lookover).arg(id));
}
