#ifndef INFORM_H
#define INFORM_H

#include <QDialog>

namespace Ui {
class inform;
}

class inform : public QDialog
{
    Q_OBJECT

public:
    explicit inform(QString id,QWidget *parent = nullptr);
    ~inform();

private slots:
    QPixmap PixmapToRound(const QPixmap &src, int radius);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_comboBox_2_activated(const QString &arg1);

    void on_lineEdit_editingFinished();

    void on_comboBox_5_activated(const QString &arg1);

    void on_comboBox_4_activated(const QString &arg1);


    void on_pushButton_30_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

private:
    Ui::inform *ui;

    bool     m_pressed;
    QPoint   m_movePos;
    QString nowid;
};

#endif // INFORM_H
