#ifndef INFORMATION_H
#define INFORMATION_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Information;
}

class Information : public QDialog
{
    Q_OBJECT

public:
    explicit Information(QWidget *parent = 0);
    ~Information();

private slots:
    void on_creditsButton_clicked();

private:
    Ui::Information *ui;
};

#endif // INFORMATION_H
