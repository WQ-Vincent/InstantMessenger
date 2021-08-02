#ifndef ADDFRD_H
#define ADDFRD_H

#include <QDialog>

namespace Ui {
class addfrd;
}

class addfrd : public QDialog
{
    Q_OBJECT

public:
    explicit addfrd(QWidget *parent = nullptr);
    ~addfrd();

private slots:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void addwin(QString frdid);

    void on_pushButton_5_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_23_clicked();

private:
    Ui::addfrd *ui;

    bool     m_pressed;
    QPoint   m_movePos;
    int pagenum;
};

#endif // ADDFRD_H
