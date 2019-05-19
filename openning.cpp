#include "openning.h"
#include "ui_openning.h"
#include <newpass.h>
#include "backend.h"
#include "mainwindow.h"
#include <QDesktopWidget>
#include <QStyle>

Openning::Openning(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Openning)
{
    ui->setupUi(this);

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
}

Openning::~Openning()
{
    delete ui;
}

void Openning::on_pushButton_clicked()
{
    if (Backend::checkNewPassword(ui->lineEdit_mk->text(), ui->lineEdit_sk->text())) {
        NewPass * newPass = new NewPass();
        newPass->show();
        this->close();
        return;
    }

    if (Backend::checkLogin(ui->lineEdit_mk->text(), ui->lineEdit_sk->text())) {
        MainWindow * mainWindow = new MainWindow;
        mainWindow->show();
        this->close();
        return;
    }
}
