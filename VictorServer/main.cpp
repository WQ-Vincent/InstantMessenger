#include "qtserver.h"

#include <QApplication>
#include <qtsingleapplication/qtsingleapplication.h>

int main(int argc, char *argv[])
{
    QtSingleApplication a("myapp_id",argc, argv);
    if(a.isRunning())   //判断实例是否已经运行
    {
    qDebug()<<"this is already running";
    a.sendMessage("raise_window_noop", 2000); //4s后激活前个实例
    return EXIT_SUCCESS;
    }
    QtServer w;
    a.setActivationWindow(&w,1);
    w.show();
    return a.exec();
}
