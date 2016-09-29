#include "interruptsthread.h"

InterruptsThread::InterruptsThread(QObject *parent,QMutex *mutex):
    QThread(parent)
{
    this->mutex = mutex;
}

void InterruptsThread::run(){
    mutex->lock();

    QFile reader("/proc/interrupts");
    reader.open(QFile::ReadOnly | QFile::Text);
    QString contents = reader.readAll();
    reader.close();

    emit finishedReading(contents);
}
