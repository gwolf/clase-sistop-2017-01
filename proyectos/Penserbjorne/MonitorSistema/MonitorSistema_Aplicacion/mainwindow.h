#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QThread>
#include <QMutex>

#include "string.h"
#include "consultar_info.h"
#include "monitor_sistema.h"

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
public slots:
    void cargar_informacion_sistema();
    void cargar_informacion_memoria();
    void cargar_informacion_stat();

private:
    Ui::MainWindow *ui;
    string comando;                     //  Usada para enviar comandos al sistema
    consultar_info *consultador_info;   //  Objeto que consulta informacion al sistema
    QMutex mutex;
};

#endif // MAINWINDOW_H
