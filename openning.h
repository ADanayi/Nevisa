#ifndef OPENNING_H
#define OPENNING_H

#include <QMainWindow>

namespace Ui {
class Openning;
}

class Openning : public QMainWindow
{
    Q_OBJECT

public:
    explicit Openning(QWidget *parent = nullptr);
    ~Openning();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Openning *ui;
};

#endif // MAINWINDOW_H
