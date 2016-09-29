#include "mainwindow.h"
#include <QApplication>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    string command = "cat /proc/cpuinfo";
    w.pruebaMainWindow(command);
    command = "cat /proc/devices";
    w.pruebaMainWindow(command);
    command = "cat /proc/meminfo";
    w.pruebaMainWindow(command);
    command = "cat /proc/version";
    w.pruebaMainWindow(command);

    return a.exec();
}
