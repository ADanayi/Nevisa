#include "openning.h"
#include <QApplication>
#include <QIcon>
#include "backend.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon icon(":/icons/icon.png");
    a.setWindowIcon(icon);
    Openning w;
    w.show();

    int ret = a.exec();

    Backend::isClosing();
    return ret;
}
