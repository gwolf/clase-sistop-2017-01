#include <QThread>

#include "mainwindow.h"
#include "ui_mainwindow.h"

// Comandos que enviaremos para leer informacion
//---------- Sistema ----------
#define VERSION_SIGNATURE "cat /proc/version_signature"
#define OS_VERSION "cat /proc/version"
#define CPUINFO "cat /proc/cpuinfo"
//---------- Memoria ----------
#define MEMINFO "cat /proc/meminfo"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    consultador_info = new consultar_info();

    //---------- Sistema ----------
    //  Creamos hilo para carga la informacion de la pestaña sistema
    QThread *thread_sistema = new QThread(this);    //  Hilo principal de la pestaña sistema
    monitor_sistema *monitor_system = new monitor_sistema();      //  Objeto que se encargara de disparar la señal para inciar el hilo

    //  Conectamos el hilo, el objeto, y las señales
    connect(monitor_system, SIGNAL(solicito_informacion_del_sistema()),this, SLOT(cargar_informacion_sistema()) );
    connect(thread_sistema, SIGNAL(destroyed()), monitor_system, SLOT(deleteLater()));

    // Movemos el monitor al hilo
    monitor_system->moveToThread(thread_sistema);

    // Iniciamos el hilo y activamos la señal
    thread_sistema->start();
    monitor_system->quiero_informacion_del_sistema();
    //---------- Sistema ----------

    //---------- Memoria ----------
    //  Creamos hilo para carga la informacion de la pestaña memoria
    QThread *thread_memoria = new QThread(this);    //  Hilo principal de la memoria
    QTimer *temporizador_memoria = new QTimer();    // Temporizador para cargar info de la memoria
    monitor_sistema *monitor_memoria = new monitor_sistema();      //  Objeto que se encargara de disparar la señal para inciar el hilo

    //  Conectamos el temporizador, hilo, el objeto, y las señales
    connect(temporizador_memoria, SIGNAL(timeout()), monitor_memoria, SLOT(quiero_informacion_de_memoria()));
    connect(monitor_memoria, SIGNAL(solicito_informacion_de_memoria()),this, SLOT(cargar_informacion_memoria()) );
    connect(thread_memoria, SIGNAL(destroyed()), monitor_memoria, SLOT(deleteLater()));

    // Movemos el monitor al hilo
    monitor_memoria->moveToThread(thread_memoria);

    // Iniciamos el hilo y activamos la señal
    thread_memoria->start();
    temporizador_memoria->setInterval(1000);
    temporizador_memoria->start();
    //---------- Memoria ----------
}

//  Funcion que carga la informacion del sistema
void MainWindow::cargar_informacion_sistema(){
    QByteArray resultado_comando;   // Aqui se almacenaran los resultados de los comandos

    // Leemos "/proc/version_signature" y lo imprimimos en un label
    resultado_comando = consultador_info->ejecutar_comando(VERSION_SIGNATURE);
    mutex.lock();
    ui->txt_distribucion->appendPlainText(QString::fromStdString(resultado_comando.toStdString()));
    mutex.unlock();

    // Leemos "/proc/version" y lo imprimimos en un label
    resultado_comando = consultador_info->ejecutar_comando(OS_VERSION);
    mutex.lock();
    ui->txt_versionKernel->appendPlainText(QString::fromStdString(resultado_comando.toStdString()));
    mutex.unlock();

    // Leemos "/proc/cpuinfo" y lo mostramos en una tabla
    resultado_comando = consultador_info->ejecutar_comando(CPUINFO);

    // Aqui creamos las cabeceras de la tabla para las columnas
    QStandardItemModel *model = new QStandardItemModel(0,12,this);
    for(int contador = 0; contador < num_props_cpuinfo; contador++){
        model->setHorizontalHeaderItem(contador, new QStandardItem(QString(consultador_info->propiedades_cpuinfo[contador].c_str())));
    }

    // Asignamos la cabeceras a la tabla
    mutex.lock();
    ui->table_cpuinfo->setModel(model);
    mutex.unlock();

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

void MainWindow::cargar_informacion_memoria(){
    // Esta funcion no implementa bloqueos ya que nadie mas accede a estos objetos

    QByteArray resultado_comando;   // Aqui se almacenaran los resultados de los comandos

    // Leemos "/proc/meminfo" y lo imprimimos en una caja de texto
    resultado_comando = consultador_info->ejecutar_comando(MEMINFO);

    // Procesamos la informacion obtenida al leer "/proc/meminfo"
    struct_MEMINFO meminfo = consultador_info->procesar_meminfo(resultado_comando);
    mutex.lock();
    ui->txt_memoria->setPlainText(QString::fromStdString(meminfo.toStdString()));
    mutex.unlock();
}

MainWindow::~MainWindow()
{
    delete ui;
}
