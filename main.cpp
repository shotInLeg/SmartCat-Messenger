#include "smartcat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SmartCat w;
    w.show();

    return a.exec();
}
