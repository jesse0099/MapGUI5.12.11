#include "MapGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapGUI w;
    w.show();
    return a.exec();
}
