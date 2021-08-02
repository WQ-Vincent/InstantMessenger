#ifndef LOGINLOSE_H
#define LOGINLOSE_H

#include <QDialog>

namespace Ui {
class loginlose;
}

class loginlose : public QDialog
{
    Q_OBJECT

public:
    explicit loginlose(QWidget *parent = nullptr);
    ~loginlose();

private slots:
    void on_pushButton_clicked();

private:
    Ui::loginlose *ui;
};

#endif // LOGINLOSE_H
