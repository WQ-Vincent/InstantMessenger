#include "pwback.h"
#include "ui_pwback.h"
#include "mainwindow.h"

pwback::pwback(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pwback)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText(" 用户名");
    ui->lineEdit_2->setPlaceholderText(" 手机号码");
}

pwback::~pwback()
{
    delete ui;
}

void pwback::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    m_movePos = event->globalPos() - pos();

    return QDialog::mousePressEvent(event);
}
void pwback::mouseMoveEvent(QMouseEvent *event)
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
void pwback::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;

    return QDialog::mouseReleaseEvent(event);
}
