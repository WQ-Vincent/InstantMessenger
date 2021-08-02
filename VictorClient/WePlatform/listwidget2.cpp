#include "listwidget2.h"
#include "mainwindow.h"

listwidget2::listwidget2(QWidget *parent):QListWidget(parent)
{
}
void listwidget2::contextMenuEvent ( QContextMenuEvent * event )
{
    QListWidgetItem *item=this->itemAt(event->pos());
    QWidget* pwig = this->itemWidget(item);
    QList<QLineEdit*> linedList = pwig->findChildren<QLineEdit*>();
    foreach(QLineEdit *lined, linedList)
    {
        if(!lined->text().isEmpty())
        {
            frdid=lined->text();
        }
    }
    QMenu* popMenu = new QMenu(this);
    popMenu->setStyleSheet("QMenu{color: rbg(80,80,80)}"
                           "QMenu::item:selected {background-color:rgb(128, 185, 240);color: rgb(245,245,245);}"
                           "QMenu::item{font-size: 9pt;"
                           "border: 0px solid rgb(140, 195, 245); background-color:rgb(232, 240, 255);"
                           "padding:5px 40px;" /*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/
                           "}");/*设置菜单项的外边距*/

    QFont font("微软雅黑",10,50);
    popMenu->setFont(font);
    if(this->itemAt(event->pos()))
    {
        QAction *action1=new QAction("置顶", this);
        QAction *action2=new QAction("删除聊天", this);
        popMenu->addAction(action1);
        popMenu->addAction(action2);

        connect(action1, SIGNAL(triggered()), this, SLOT(actionone()));
        connect(action2, SIGNAL(triggered()), this, SLOT(actiontwo()));
    }
    popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
}

void listwidget2::mousePressEvent(QMouseEvent * event)
{
    if(this->itemAt(event->pos()))
    {
        QListWidgetItem *item=this->itemAt(event->pos());
        item->setSelected(true);
        QWidget* pwig = this->itemWidget(item);
        QList<QLineEdit*> linedList = pwig->findChildren<QLineEdit*>();
        foreach(QLineEdit *lined, linedList)
        {
            if(!lined->text().isEmpty())
            {
                frdid=lined->text();
            }
        }
        action3->clicked();
    }
}

void listwidget2::actionone()
{
    action1->clicked();
}

void listwidget2::actiontwo()
{
    action2->clicked();
}
