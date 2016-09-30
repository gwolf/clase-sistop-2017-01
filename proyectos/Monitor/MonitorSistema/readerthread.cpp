#include "readerthread.h"

ReaderThread::ReaderThread(QObject *parent, QMutex *mutex) :
    QThread(parent)
{
    this->mutex = mutex;
}

void ReaderThread::run()
{
    //  Bloquea el mutex y lee el contenido del archivo.
    //  Una vez leído señaliza a la ventana para actualizar contenido.
    mutex->lock();

    QFile reader("/proc/meminfo");
    reader.open(QFile::ReadOnly | QFile::Text);
    QString contents = reader.readAll();
    reader.close();

    emit finishedReading(contents);
}
