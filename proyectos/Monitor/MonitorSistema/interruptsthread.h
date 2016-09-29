#ifndef INTERRUPTSTHREAD_H
#define INTERRUPTSTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QFile>

class InterruptsThread : public QThread
{
    Q_OBJECT

public:
    explicit InterruptsThread(QObject *parent = 0, QMutex* mutex = 0);
    void run();
    QMutex *mutex;

signals:
    void finishedReading(QString);
    void createThread();
};

#endif // INTERRUPTSTHREAD_H
