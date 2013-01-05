#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QDebug>
#include "testobject.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestObject object;

    MainWindow w;
    w.show();

    return a.exec();
}
