#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wait.h"
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBox_autoUnlock_stateChanged(int arg1);

    void on_checkBox_autoOpen_stateChanged(int arg1);

    void on_checkBox_autoClose_stateChanged(int arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void tray_slot_exit();
    void tray_slot_show();
    void tray_slot_LU();
    void tray_slot_open();

    void lock();
    void unlock();
    void openFolder();

protected:
    void changeEvent(QEvent* e) override;

private:
    Ui::MainWindow *ui;
    bool _maskUpdateSettings;
    void updateSettings();
    void updateState();
    QString rootAdr;

    void tray_setup();

    Wait * _wait;
    void wait();
    void unwait();

    QAction * trayLU;
    QAction * trayOpen;
};

#endif // MAINWINDOW_H
