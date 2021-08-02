#ifndef DATABASE_H
#define DATABASE_H

#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>

class DataBase
{
public:
    bool createConnection();  //创建一个连接
    bool createTable1();       //创建数据库表
    bool createTable2();
    bool createTable3();
    bool createTable4();
    //bool createTable5();
    bool createTable6();
};

#endif // DATABASE_H
