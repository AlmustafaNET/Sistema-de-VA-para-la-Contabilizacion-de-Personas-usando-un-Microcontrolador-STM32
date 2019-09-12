#include "imagenpuertoserial.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImagenPuertoSerial w;
    w.show();

    return a.exec();
}
