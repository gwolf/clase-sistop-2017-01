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
