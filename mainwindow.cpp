#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backend.h"
#include <QFileDialog>
#include <QDir>
#include <QStyle>
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));

    _wait = new Wait(this);
    _wait->hide();

    wait();
    Backend::isOpened();
    unwait();

    _maskUpdateSettings = true;
    Settings s = Backend::readSettings();
    ui->checkBox_autoUnlock->setChecked(s.autoUnlock);
    ui->checkBox_autoOpen->setChecked(s.autoOpen);
    ui->checkBox_autoClose->setChecked(s.autoClose);
    rootAdr = s.rootAdr;

    ui->label_rootAdr->setText(s.rootAdr);
    _maskUpdateSettings = false;

    tray_setup();
    updateState();

    if (s.autoOpen && s.autoUnlock) {
        QTimer::singleShot(250, this, SLOT(hide()));
    }
}

void MainWindow::lock() {
    wait();
    Backend::lock();
    updateState();
    unwait();
}

void MainWindow::unlock() {
    wait();
    Backend::unlock();
    if (Backend::readSettings().autoOpen) {
        Backend::openFolder();
    }
    updateState();
    unwait();
}

void MainWindow::openFolder() {
    wait();
    if (Backend::isUnlocked())
        Backend::openFolder();
    unwait();
}

void MainWindow::wait() {
    this->setEnabled(false);
    _wait->show();
    QApplication::processEvents(QEventLoop::AllEvents);
}

void MainWindow::unwait() {
    _wait->hide();
    this->setEnabled(true);
    QApplication::processEvents(QEventLoop::AllEvents);
}

void MainWindow::tray_setup() {
    QIcon icon(":/icons/icon.png");
    QSystemTrayIcon * trayIcon = new QSystemTrayIcon(qApp);
    QMenu * trayIconMenu = new QMenu;
    trayIcon->setIcon(icon);
    trayIcon->show();

    QAction * trayShow = new QAction("Show Window", trayIconMenu);
    trayIconMenu->addAction(trayShow);
    connect(trayShow, SIGNAL(triggered()), this, SLOT(tray_slot_show()));

    QAction * trayExit = new QAction("Exit", trayIconMenu);
    trayIconMenu->addAction(trayExit);
    connect(trayExit, SIGNAL(triggered()), this, SLOT(tray_slot_exit()));

    trayLU = new QAction("Lock/Unlock", trayIconMenu);
    if (Backend::isUnlocked())
        trayLU->setText("Lock");
    else {
        trayLU->setText("Unlock");
    }
    trayIconMenu->addAction(trayLU);
    connect(trayLU, SIGNAL(triggered()), this, SLOT(tray_slot_LU()));

    trayOpen = new QAction("Open folder", trayIconMenu);
    trayIconMenu->addAction(trayOpen);
    connect(trayOpen, SIGNAL(triggered()), this, SLOT(tray_slot_open()));

    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();
}

void MainWindow::tray_slot_LU() {
    Backend::isUnlocked() ? lock() : unlock();
}

void MainWindow::tray_slot_open() {
    if (Backend::isUnlocked()) Backend::openFolder();
}

void MainWindow::changeEvent(QEvent* e)
{
    switch (e->type())
    {
        case QEvent::LanguageChange:
            this->ui->retranslateUi(this);
            break;
        case QEvent::WindowStateChange:
            {
                if (this->windowState() & Qt::WindowMinimized)
                {
                    QTimer::singleShot(250, this, SLOT(hide()));
                }

                break;
            }
        default:
            break;
    }

    QMainWindow::changeEvent(e);
}

void MainWindow::tray_slot_exit() {
    this->close();
}

void MainWindow::tray_slot_show() {
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSettings() {
    if (_maskUpdateSettings)
        return;

    bool autoUnlock = ui->checkBox_autoUnlock->isChecked();
    bool autoOpen = ui->checkBox_autoOpen->isChecked();
    bool autoClose = ui->checkBox_autoClose->isChecked();

    Settings sets(autoUnlock, autoOpen, autoClose, rootAdr);
    Backend::saveSettings(sets);

    ui->label_rootAdr->setText(sets.rootAdr);
}

void MainWindow::on_checkBox_autoUnlock_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    updateSettings();
}

void MainWindow::on_checkBox_autoOpen_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    updateSettings();
}

void MainWindow::on_checkBox_autoClose_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    updateSettings();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString Root = QFileDialog::getExistingDirectory(this, ("Select Your Diaries Folder!"), QDir::currentPath());
    if (Root == "")
        return;
    this->rootAdr = Root;
    updateSettings();
}

void MainWindow::on_pushButton_clicked()
{
    lock();
}

void MainWindow::on_pushButton_2_clicked()
{
    unlock();
}

void MainWindow::on_pushButton_3_clicked()
{
    openFolder();
}

void MainWindow::updateState() {
    if (Backend::isUnlocked()) {
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
        trayLU->setText("Lock");
        trayOpen->setVisible(true);
    }
    else {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(false);
        trayLU->setText("Unlock");
        trayOpen->setVisible(false);
    }
}
