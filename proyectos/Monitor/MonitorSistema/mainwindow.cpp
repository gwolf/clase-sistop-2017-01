#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>

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

void MainWindow::on_memInfoButton_clicked()
{
    ui->memInfoButton->setEnabled(false);
    memInfo = new MemInfo(0, ui->memInfoButton);
    memInfo->show();
}

void MainWindow::on_interruptsButton_clicked()
{
    ui->interruptsButton->setEnabled(false);
    interrupt = new InterruptWindow(0, ui->interruptsButton);
    interrupt->show();
}


void MainWindow::on_mountsButton_clicked()
{
    ui->mountsButton->setEnabled(false);
    mounts = new DispositivosWindow(0, ui->mountsButton);
    mounts->show();
}
