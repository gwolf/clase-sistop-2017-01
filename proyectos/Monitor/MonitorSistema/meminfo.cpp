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

    readFile();
    connect(timer, SIGNAL(timeout()), this, SLOT(readFile()));
    timer->start(2000);
}

void MemInfo::readFile()
{
    mutex->lock();

    QFile lector("/proc/meminfo");
    lector.open(QFile::ReadOnly | QFile::Text);
    ui->plainTextEdit->setPlainText(lector.readAll());
    lector.close();

    mutex->unlock();
}

MemInfo::~MemInfo()
{
    lockButton->setEnabled(true);

    delete ui;
    delete mutex;
}
