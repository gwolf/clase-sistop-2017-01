#ifndef DISPOSITIVOSTHREAD_H
#define DISPOSITIVOSTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QMutex>

class DispositivosThread : public QThread
{
    Q_OBJECT

public:
    explicit DispositivosThread(QObject *parent = 0, QMutex *mutex = 0);
    void run();
    QMutex *mutex;

signals:
    void finishedReading(QString);
};

#endif // DISPOSITIVOSTHREAD_H
