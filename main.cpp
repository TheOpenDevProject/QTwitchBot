#include "mainwindow.h"
#include <QApplication>
#include "monitor.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Monitor streamMonitor;
    streamMonitor.show();

    return a.exec();
}
