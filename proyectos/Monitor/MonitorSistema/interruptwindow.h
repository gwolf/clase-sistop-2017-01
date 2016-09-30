#ifndef INTERRUPTWINDOW_H
#define INTERRUPTWINDOW_H

#include <QDialog>
#include <QMutex>
#include <QTimer>
#include <QPushButton>
#include "interruptsthread.h"

namespace Ui {
class InterruptWindow;
}

class InterruptWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InterruptWindow(QWidget *parent = 0, QPushButton *button = 0);
    ~InterruptWindow();

private:
    Ui::InterruptWindow *ui;
    QPushButton *lockButton;
    QMutex *mutex;
    QTimer *timer;

private slots:
    void createThread();
    void onFinishedReading(QString);
};

#endif // INTERRUPTWINDOW_H
