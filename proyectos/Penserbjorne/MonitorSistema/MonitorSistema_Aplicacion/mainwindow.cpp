#include <QThread>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "consultar_info.h"
#include "struct_cpuinfo.h"

// Comandos que enviaremos para leer informacion
#define VERSION_SIGNATURE "cat /proc/version_signature"
#define OS_VERSION "cat /proc/version"
#define CPUINFO "cat /proc/cpuinfo"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    consultador_info = new consultar_info();
    monitor = new monitor_sistema();

    //  Creamos hilo para carga la informacion del sistema que se muestra en la primera pantalla
    QThread *thread = new QThread();    //  Hilo principal
    monitor->moveToThread(thread);      //  Objeto que se encargara de disparar la señal para inciar el hilo

    //  Conectamos el hilo, el objeto, y las señales
    connect(monitor, SIGNAL(solicito_informacion_del_sistema()),this, SLOT(cargar_informacion_sistema()) );
    connect(thread, SIGNAL(destroyed()), monitor, SLOT(deleteLater()));

    // Iniciamos el hilo y activamos la señal
    thread->start();
    monitor->quiero_informacion_del_sistema();
}

//  Funcion que carga la informacion del sistema
void MainWindow::cargar_informacion_sistema(){
    // Esta funcion no implementa bloqueos ya que nadie mas accede a estos objetos

    QByteArray resultado_comando;   // Aqui se almacenaran los resultados de los comandos

    // Leemos "/proc/version_signature" y lo imprimimos en un label
    resultado_comando = consultador_info->ejecutar_comando(VERSION_SIGNATURE);
    ui->txt_distribucion->appendPlainText(QString::fromStdString(resultado_comando.toStdString()));

    // Leemos "/proc/version" y lo imprimimos en un label
    resultado_comando = consultador_info->ejecutar_comando(OS_VERSION);
    ui->txt_versionKernel->appendPlainText(QString::fromStdString(resultado_comando.toStdString()));

    // Leemos "/proc/cpuinfo" y lo mostramos en una tabla
    resultado_comando = consultador_info->ejecutar_comando(CPUINFO);

    // Aqui creamos las cabeceras de la tabla para las columnas
    QStandardItemModel *model = new QStandardItemModel(0,12,this);
    for(int contador = 0; contador < num_props_cpuinfo; contador++){
        model->setHorizontalHeaderItem(contador, new QStandardItem(QString(consultador_info->propiedades_cpuinfo[contador].c_str())));
    }

    // Asignamos la cabeceras a la tabla
    ui->table_cpuinfo->setModel(model);

    // Procesamos la informacion obtenida al leer "/proc/cpuinfo"
    vector<struct_CPUINFO> cores = consultador_info->procesar_cpuinfo(resultado_comando);

    // Insertamos la informacion procesada en la tabla
    int fila = 0;
    foreach (struct_CPUINFO cpuinfo, cores) {
        for(int columna = 0; columna < num_props_cpuinfo; columna++){
            QStandardItem *valorCelda = new QStandardItem(QString(cpuinfo.obtenerValor(columna).c_str()));
            valorCelda->setFlags(valorCelda->flags() ^ Qt::ItemIsEditable);
            model->setItem(fila,columna,valorCelda);
        }
        fila++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
