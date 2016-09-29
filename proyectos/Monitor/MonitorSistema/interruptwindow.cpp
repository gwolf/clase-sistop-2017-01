#include "interruptwindow.h"
#include "ui_interruptwindow.h"

InterruptWindow::InterruptWindow(QWidget *parent, QPushButton *button) :
    QDialog(parent),
    ui(new Ui::InterruptWindow)
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

void InterruptWindow::createThread(){
    InterruptsThread *hilo = new InterruptsThread(this,mutex);
    hilo->start();

    connect(hilo,SIGNAL(finishedReading(QString)),this,SLOT(onFinishedReading(QString)));
}

void InterruptWindow::onFinishedReading(QString contents){
    ui->plainTextEdit->setPlainText(contents);
    mutex->unlock();
}

InterruptWindow::~InterruptWindow()
{
    lockButton->setEnabled(true);
    delete ui;
}
