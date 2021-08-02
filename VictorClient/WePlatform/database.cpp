#include "database.h"


//建立一个数据库连接
bool DataBase::createConnection()
{
    //以后就可以用"sqlite1"与数据库进行连接了
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
    db.setDatabaseName(".//qtDb.db");
    if( !db.open())
    {
        qDebug() << "无法建立数据库连接";
        return false;
    }
    return true;
}

//创建数据库表
bool DataBase::createTable1()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table user_inform("
                              "user_id char(11),"
                              "user_password char(11),"
                              "phonenumber int(11))");
    if(success)
    {
        qDebug() << QObject::tr("数据库表1创建成功！");
        return true;
    }
    else
    {
        return false;
    }
}

bool DataBase::createTable2()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table userdata("
                              "user_id char(11),"
                              "user_name char(11),"
                              "user_sex int,"
                              "year char(10),month char(8),date char(8),"
                              "phonenumber char(11),"
                              "user_state char(20),"
                              "user_city char(20),"
                              "signature char(40),"
                              "cansearch int,"
                              "canlookover int,"
                              "addway int,"
                              "addquestion char(30),"
                              "addanswer char(30),"
                              "touxiang char(20))");
    if(success)
    {
        qDebug() << QObject::tr("数据库表2创建成功！");
        return true;
    }
    else
    {

        return false;
    }
}

bool DataBase::createTable3()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table loginuser("
                              "user_id char(11),"
                              "user_password char(11),"
                              "ifrem int)");
    if(success)
    {
        qDebug() << QObject::tr("数据库表3创建成功！");
        return true;
    }
    else
    {

        return false;
    }
}

bool DataBase::createTable4()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table userfriend("
                              "user_id char(11),"
                              "user_friend char(500))");
    if(success)
    {
        qDebug() << QObject::tr("数据库表4创建成功！");
        return true;
    }
    else
    {

        return false;
    }
}

/*bool DataBase::createTable5()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table message("
                              "user_id char(11),"
                              "frdmessa char(50),"
                              "talkmessa char(100))");
    if(success)
    {
        qDebug() << QObject::tr("数据库表5创建成功！");
        return true;
    }
    else
    {
        qDebug()<<query.exec("drop table message");
        return false;
    }
}*/

bool DataBase::createTable6()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table talklist("
                              "user_id char(11),"
                              "user_friend char(500))");
    if(success)
    {
        qDebug() << QObject::tr("数据库表6创建成功！");
        return true;
    }
    else
    {
        return false;
    }
}

