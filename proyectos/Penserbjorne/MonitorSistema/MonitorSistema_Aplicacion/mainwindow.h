#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QThread>

#include "string.h"
#include "consultar_info.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    string comando;
    consultar_info *consultador_info;
    QThread *informacionSistema;

    void cargar_informacion_sistema();
};

#endif // MAINWINDOW_H
