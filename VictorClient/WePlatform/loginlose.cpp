#include "loginlose.h"
#include "ui_loginlose.h"
#include "pwback.h"

loginlose::loginlose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginlose)
{
    ui->setupUi(this);
}

loginlose::~loginlose()
{
    delete ui;
}

void loginlose::on_pushButton_clicked()
{
    pwback a;
    a.exec();
}
