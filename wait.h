#ifndef WAIT_H
#define WAIT_H

#include <QDialog>

namespace Ui {
class Wait;
}

class Wait : public QDialog
{
    Q_OBJECT

public:
    explicit Wait(QWidget *parent = nullptr);
    ~Wait();

private:
    Ui::Wait *ui;
};

#endif // WAIT_H
