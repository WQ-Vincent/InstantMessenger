#ifndef LISTWIDGET2_H
#define LISTWIDGET2_H

#include <QListWidget>
#include <mainwindow.h>
#include <QPushButton>

class listwidget2 : public QListWidget
{
    Q_OBJECT
public:
    explicit listwidget2(QWidget *parent=nullptr);
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

#endif // LISTWIDGET2_H
