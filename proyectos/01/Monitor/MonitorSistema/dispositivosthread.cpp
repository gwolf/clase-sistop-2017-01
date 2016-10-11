#include "dispositivosthread.h"
#include <QFile>

DispositivosThread::DispositivosThread(QObject *parent, QMutex *mutex)
{
    this->mutex = mutex;
}

void DispositivosThread::run(){
    mutex->lock();

    QFile reader("/proc/mounts");
    reader.open(QFile::ReadOnly | QFile::Text);
    QString contents = reader.readAll();
    reader.close();

    emit finishedReading(contents);
}
