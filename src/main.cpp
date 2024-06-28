#include "FreeFTP.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FreeFTP w;
    w.show();
    return a.exec();
}
