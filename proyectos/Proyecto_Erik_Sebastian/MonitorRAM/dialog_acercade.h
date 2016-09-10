#ifndef DIALOG_ACERCADE_H
#define DIALOG_ACERCADE_H

#include <QDialog>

namespace Ui {
class Dialog_AcercaDe;
}

class Dialog_AcercaDe : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_AcercaDe(QWidget *parent = 0);
    ~Dialog_AcercaDe();

private:
    Ui::Dialog_AcercaDe *ui;
};

#endif // DIALOG_ACERCADE_H
