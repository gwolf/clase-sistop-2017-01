#include <QThread>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "consultar_info.h"
#include "struct_cpuinfo.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    consultador_info = new consultar_info();
    monitor = new monitor_sistema();

    QThread *thread = new QThread();
    monitor->moveToThread(thread);
    connect(monitor, SIGNAL(solicito_informacion_del_sistema()),this, SLOT(cargar_informacion_sistema()) );
    connect(thread, SIGNAL(destroyed()), monitor, SLOT(deleteLater()));
    thread->start();
    monitor->quiero_informacion_del_sistema();
}

void MainWindow::cargar_informacion_sistema(){
    QByteArray resultado_comando;
    resultado_comando = consultador_info->ejecutar_comando("cat /proc/version_signature");
    ui->txt_distribucion->appendPlainText(QString::fromStdString(resultado_comando.toStdString()));
    resultado_comando = consultador_info->ejecutar_comando("cat /proc/version");
    ui->txt_versionKernel->appendPlainText(QString::fromStdString(resultado_comando.toStdString()));

    resultado_comando = consultador_info->ejecutar_comando("cat /proc/cpuinfo");

    QStandardItemModel *model = new QStandardItemModel(0,12,this);
    for(int contador = 0; contador < num_props_cpuinfo; contador++){
        model->setHorizontalHeaderItem(contador, new QStandardItem(QString(consultador_info->propiedades_cpuinfo[contador].c_str())));
    }

    ui->table_cpuinfo->setModel(model);

    vector<struct_CPUINFO> cores = consultador_info->consultar_cpuinfo(resultado_comando);

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
