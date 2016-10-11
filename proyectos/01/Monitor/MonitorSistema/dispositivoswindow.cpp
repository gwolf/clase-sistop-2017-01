#include "dispositivoswindow.h"
#include "ui_dispositivoswindow.h"
#include "dispositivosthread.h"

DispositivosWindow::DispositivosWindow(QWidget *parent, QPushButton *button) :
    QDialog(parent),
    ui(new Ui::DispositivosWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    lockButton = button;
    mutex = new QMutex();
    timer = new QTimer(this);

    createThread();
    connect(timer, SIGNAL(timeout()), this, SLOT(createThread()));
    timer->start(1500);
}

void DispositivosWindow::createThread(){
    DispositivosThread *hilo = new DispositivosThread(0,mutex);
    hilo->start();

    connect(hilo,SIGNAL(finishedReading(QString)),this,SLOT(onFinishedReading(QString)));
}

void DispositivosWindow::onFinishedReading(QString contents){
    ui->plainTextEdit->setPlainText(contents);
    mutex->unlock();
}

DispositivosWindow::~DispositivosWindow()
{
    lockButton->setEnabled(true);
    delete ui;
}
