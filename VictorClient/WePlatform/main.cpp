#include "mainwindow.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataBase d;
    d.createConnection();
    d.createTable1();
    d.createTable2();
    d.createTable3();
    d.createTable4();
    d.createTable6();
    MainWindow w;
    w.show();
    if(w.ifopen==false)w.close(); 
    MainWindow g;
    g.show();
    if(g.ifopen==false)g.close();
    return a.exec();  //程序一直执行，直到主窗口关闭
}
