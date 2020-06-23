#include "showwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowWindow w;
    w.show();
    return a.exec();
}
