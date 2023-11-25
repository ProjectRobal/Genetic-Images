#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "crossover.h"
#include "genimage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Crossover<uint8_t> cross(0,255);

    GenImage gen("./tmp1.jpg",800,600);

    cross.fill(gen.getData(),800*600*3);
    cross.mutate(gen);

    gen.save_image();

    w.show();
    return a.exec();
}
