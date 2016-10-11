#ifndef READERTHREAD_H
#define READERTHREAD_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QFile>

class ReaderThread : public QThread
{
    Q_OBJECT

public:
    explicit ReaderThread(QObject *parent = 0, QMutex* mutex = 0);
    void run();
    QMutex *mutex;

signals:
    void finishedReading(QString);

public slots:

private:

};



#endif // READERTHREAD_H
