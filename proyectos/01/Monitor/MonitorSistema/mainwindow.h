#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include <QPushButton>
#include <QWidget>

#include "information.h"
#include "meminfo.h"
#include "interruptwindow.h"
#include "dispositivoswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAcerca_de_triggered();

    void on_memInfoButton_clicked();

    void on_interruptsButton_clicked();

    void on_mountsButton_clicked();

private:
    Ui::MainWindow *ui;
    MemInfo *memInfo;
    InterruptWindow *interrupt;
    DispositivosWindow *mounts;
};

#endif // MAINWINDOW_H
