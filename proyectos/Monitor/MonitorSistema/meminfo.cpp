#include "meminfo.h"
#include "ui_meminfo.h"

MemInfo::MemInfo(QWidget *parent, QPushButton *button) :
    QDialog(parent),
    ui(new Ui::MemInfo)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    mutex = new QMutex();
    timer = new QTimer(this);
    lockButton = button;

    //  Obtiene el contenido de /proc/meminfo antes de cargar
    //  la ventana.
    createThread();

    //  Inicializa un temporizador que crea hilos cada 1.5 segundos
    //  para obtener el contenido de meminfo.
    connect(timer, SIGNAL(timeout()), this, SLOT(createThread()));
    timer->start(1500);
}

void MemInfo::createThread()
{
    ReaderThread *newThread = new ReaderThread(this, mutex);
    newThread->start();

    connect(newThread, SIGNAL(finishedReading(QString)), this, SLOT(onFinishedReading(QString)));
}

void MemInfo::onFinishedReading(QString contents)
{
    //  Al recibir la señal finishedReading desde cualquier hilo,
    //  actualiza el contenido del plainText y libera el mutex.
    ui->plainTextEdit->setPlainText(contents);
    mutex->unlock();
}

MemInfo::~MemInfo()
{
    lockButton->setEnabled(true);

    delete ui;
    delete mutex;
}
