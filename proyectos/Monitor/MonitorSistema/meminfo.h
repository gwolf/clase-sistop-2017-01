#ifndef MEMINFO_H
#define MEMINFO_H

#include <QDialog>
#include <QTimer>
#include <QMutex>
#include <QFile>
#include <QPushButton>

#include "readerthread.h"

namespace Ui {
class MemInfo;
}

class MemInfo : public QDialog
{
    Q_OBJECT

public:
    explicit MemInfo(QWidget *parent = 0, QPushButton *button = 0);
    ~MemInfo();

private:
    Ui::MemInfo *ui;
    QTimer *timer;
    QMutex *mutex;
    QPushButton *lockButton;

public slots:
    void createThread();
    void onFinishedReading(QString);
};

#endif // MEMINFO_H
