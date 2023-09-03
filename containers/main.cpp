#include <QApplication>
#include "mainclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainClient mc;
    mc.show();

    return a.exec();
}

