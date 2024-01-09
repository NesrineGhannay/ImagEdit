#include "imagedit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImagEdit w;
    w.show();
    return a.exec();
}
