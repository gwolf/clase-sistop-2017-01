#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap monitorIcon = QPixmap(":/Iconos/Images/mainWindowIcon.png");
    ui->imageLabel->setPixmap(monitorIcon);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//  Muestra una ventana con información acerca
//  del equipo.
void MainWindow::on_actionAcerca_de_triggered()
{
    Information acercaDe;
    acercaDe.setModal(true);
    acercaDe.exec();
}
