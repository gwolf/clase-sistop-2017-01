//Esta clase es para creacion de hilos de 'interruptsthread'

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
    //lectura del archivo que proporsciona informacion del sistema, esta lectura es la que va a cambiar con cada hilo
    QString contents = reader.readAll();
    reader.close();
    //Se emite la señal, indica que el hilo ya termino su objetivo
    emit finishedReading(contents);
}
