#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QApplication>
#include <QStyleOptionTab>
#include <QStylePainter>
#include <QTabBar>
#include <QTabWidget>


class TabBar: public QTabBar
{
public:
    QSize tabSizeHint(int index) const;
protected:
    void paintEvent(QPaintEvent *);
};

class tabwidget : public QTabWidget
{
public:

    tabwidget(QWidget *parent=nullptr);
};

#endif // TABWIDGET_H
