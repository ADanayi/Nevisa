#include "newpass.h"
#include "ui_newpass.h"
#include "backend.h"
#include <QDesktopWidget>
#include <QStyle>

NewPass::NewPass(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewPass)
{
    ui->setupUi(this);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
}

NewPass::~NewPass()
{
    delete ui;
}

void NewPass::on_pushButton_clicked()
{
    Backend::setPassword(ui->lineEdit_mk->text(), ui->lineEdit_sk->text());

    QApplication::exit(0);
}
