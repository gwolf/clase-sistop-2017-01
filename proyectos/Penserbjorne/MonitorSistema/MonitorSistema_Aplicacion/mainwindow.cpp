#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include "string"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::pruebaMainWindow(string command){
    QString qcommand = QString::fromStdString(command);
    QProcess *myProcess = new QProcess();
    QByteArray processOutput;
    myProcess->start(qcommand);
    myProcess->waitForReadyRead();
    processOutput = myProcess->readAll();
    ui->plainTextEditProc->appendPlainText(QString::fromStdString(processOutput.toStdString()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
