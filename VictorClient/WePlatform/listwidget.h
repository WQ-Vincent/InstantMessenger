#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>
#include <mainwindow.h>
#include <QPushButton>

class alistwidget : public QListWidget
{
    Q_OBJECT
public:
    explicit alistwidget(QWidget *parent=nullptr);
    QString frdid;
    QPushButton *action1=new QPushButton;
    QPushButton *action2=new QPushButton;
    QPushButton *action3=new QPushButton;
public slots:
    void actionone();
    void actiontwo();
private slots:
    void contextMenuEvent ( QContextMenuEvent * event );
    void mousePressEvent (QMouseEvent * event );
};

#endif // LISTWIDGET_H
