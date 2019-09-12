#include "testimagencomputador.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestImagenComputador w;
    w.show();

    return a.exec();
}
