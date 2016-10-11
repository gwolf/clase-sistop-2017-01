#ifndef DISPOSITIVOSWINDOW_H
#define DISPOSITIVOSWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QMutex>
#include <QTimer>

namespace Ui {
class DispositivosWindow;
}

class DispositivosWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DispositivosWindow(QWidget *parent = 0, QPushButton *button = 0);
    ~DispositivosWindow();

public slots:
    void onFinishedReading(QString);
    void createThread();

private:
    Ui::DispositivosWindow *ui;
    QPushButton *lockButton;
    QMutex *mutex;
    QTimer *timer;


};

#endif // DISPOSITIVOSWINDOW_H
