#ifndef NEWPASS_H
#define NEWPASS_H

#include <QMainWindow>

namespace Ui {
class NewPass;
}

class NewPass : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewPass(QWidget *parent = nullptr);
    ~NewPass();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NewPass *ui;
};

#endif // NEWPASS_H
