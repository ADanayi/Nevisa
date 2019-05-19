#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "settings.h"

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    Q_INVOKABLE static bool checkLogin(QString mk, QString sk);
    Q_INVOKABLE static bool checkNewPassword(QString mk, QString sk);
    Q_INVOKABLE static void setPassword(QString mk, QString sk);

    Q_INVOKABLE static Settings readSettings();
    Q_INVOKABLE static void saveSettings(Settings & s);

    Q_INVOKABLE static bool isUnlocked();
    Q_INVOKABLE static void lock();
    Q_INVOKABLE static void unlock();
    Q_INVOKABLE static void openFolder();

    Q_INVOKABLE static void isOpened();
    Q_INVOKABLE static void isClosing();

signals:

public slots:
};

#endif // BACKEND_H
