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
    timer = new QTimer(this);  //Lanza hilos cada 1.5 segundos (actualizacion de datos)

    createThread();

    connect(timer, SIGNAL(timeout()), this, SLOT(createThread()));
    timer->start(1500);
}

void InterruptWindow::createThread(){
    InterruptsThread *hilo = new InterruptsThread(this,mutex);
    hilo->start();
    //Se conecta una señal que emite el hilo al terminar, y se cacha en un SLOT (entrada) del metodo mencionado:
    connect(hilo,SIGNAL(finishedReading(QString)),this,SLOT(onFinishedReading(QString)));
}
//una vez que el SLOT activa el metodo sigueinte, se actualiza el cuadro de texto de la informacion con la cadena que devuelve el hilo:
void InterruptWindow::onFinishedReading(QString contents){
    ui->plainTextEdit->setPlainText(contents);
    //el mutex es liberado para que otro hilo pueda actualizar la informacion del cuadro:
    mutex->unlock();
}

InterruptWindow::~InterruptWindow()
{
    lockButton->setEnabled(true);
    delete ui;
}
