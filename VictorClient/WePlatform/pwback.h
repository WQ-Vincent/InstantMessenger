#ifndef PWBACK_H
#define PWBACK_H

#include <QDialog>

namespace Ui {
class pwback;
}

class pwback : public QDialog
{
    Q_OBJECT

public:
    explicit pwback(QWidget *parent = nullptr);
    ~pwback();
private slots:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool     m_pressed;
    QPoint   m_movePos;
    Ui::pwback *ui;
};

#endif // PWBACK_H
