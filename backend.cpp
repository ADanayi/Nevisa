#include "backend.h"
#include <QSettings>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QProcess>
#include <QApplication>

Backend::Backend(QObject *parent) : QObject(parent)
{

}

bool Backend::checkLogin(QString mk, QString sk) {
    QSettings sets("Taeb", "Diaries");
    if (sets.value("mk").toString() == mk) {
        if (sets.value("sk").toString() == sk ) {
            return true;
        }
    }
    return false;
};

bool Backend::checkNewPassword(QString mk, QString sk) {
    QSettings sets("Taeb", "Diaries");
    if (mk == "NewPassword") {
        if (sk == "np") {
            return true;
        }
    }
    return false;
};

void Backend::setPassword(QString mk, QString sk) {
    QSettings sets("Taeb", "Diaries");

    sets.setValue("mk", mk);
    sets.setValue("sk", sk);
}

Settings Backend::readSettings() {
    QSettings sets("Taeb", "Diaries");

    bool autoUnlock = sets.value("autoUnlock").toString() == "yes";
    bool autoOpen = sets.value("autoOpen").toString() == "yes";
    bool autoClose = sets.value("autoClose").toString() == "yes";
    QString rootAdr = sets.value("rootAdr").toString();

    Settings ret(autoUnlock, autoOpen, autoClose, rootAdr);

    return ret;
}

void Backend::saveSettings(Settings & s) {
    QSettings sets("Taeb", "Diaries");

    if (s.autoUnlock)
        sets.setValue("autoUnlock", "yes");
    else
        sets.setValue("autoUnlock", "no");

    if (s.autoOpen)
        sets.setValue("autoOpen", "yes");
    else
        sets.setValue("autoOpen", "no");

    if (s.autoClose)
        sets.setValue("autoClose", "yes");
    else
        sets.setValue("autoClose", "no");

    sets.setValue("rootAdr", s.rootAdr);
}

bool fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

bool Backend::isUnlocked() {
    Settings s = readSettings();
    QString rootAdr = s.rootAdr;

    QDir pathDir(rootAdr);
    bool rootExists = pathDir.exists();

    pathDir.cdUp();

    QString dFileAdr = pathDir.absoluteFilePath("data.nvs");

    bool dFileExists = fileExists(dFileAdr);

    return (!dFileExists) && (rootExists);
}

void Backend::lock() {
    QSettings sets("Taeb", "Diaries");
    Settings s = readSettings();
    QString rootAdr = s.rootAdr;
    QDir pathDir(rootAdr);
    QString name = pathDir.dirName();
    pathDir.cdUp();
    QString uAdr = pathDir.absolutePath();
    QString dFileAdr = pathDir.absoluteFilePath("data.nvs");

    QString command = "zip -P \"";
    command += sets.value("sk").toString();
    command += "\" -r ";
    command += "data.nvs";//dFileAdr;
    command += " ";
    command += name;//command += rootAdr;

    QString cdCommand = "cd ";
    cdCommand += uAdr;
    QString dcommand = "rm -rf ";
    dcommand += name;

    QString commands = cdCommand;
    commands += '\n';
    commands += command;
    commands += '\n';
    commands += dcommand;

//    QProcess process;
//    process.start(commands);
//    while (!process.waitForFinished()) {
//        QApplication::processEvents(QEventLoop::AllEvents);
//    }
    system(commands.toUtf8());
}

void Backend::unlock() {
    QSettings sets("Taeb", "Diaries");
    Settings s = readSettings();
    QString rootAdr = s.rootAdr;
    QDir pathDir(rootAdr);
    QString name = pathDir.dirName();
    pathDir.cdUp();
    QString uAdr = pathDir.absolutePath();
    QString dFileAdr = pathDir.absoluteFilePath("data.nvs");

    QString command = "unzip -P \"";
    command += sets.value("sk").toString();
    command += "\" ";
    command += "data.nvs";//dFileAdr;

    QString cdCommand = "cd \"";
    cdCommand += uAdr;
    cdCommand += "\"";
    QString dcommand = "rm ";
    dcommand += "data.nvs";

    QString commands = cdCommand;
    commands += '\n';
    commands += command;
    commands += '\n';
    commands += dcommand;

    system(commands.toUtf8());
}

void Backend::openFolder() {
    Settings s = readSettings();
    QString rootAdr = s.rootAdr;

    QString command = "nautilus ";
    command += rootAdr;

    QProcess * p = new QProcess;
    p->start(command);
}

void Backend::isOpened() {
    Settings s = readSettings();
    QString rootAdr = s.rootAdr;

    if (s.autoUnlock) unlock();
    if (s.autoOpen) openFolder();
}

void Backend::isClosing() {
    Settings s = readSettings();
    QString rootAdr = s.rootAdr;

    if (s.autoClose) lock();
}
