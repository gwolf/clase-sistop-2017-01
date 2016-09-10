#include "dialog_acercade.h"
#include "ui_dialog_acercade.h"

Dialog_AcercaDe::Dialog_AcercaDe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_AcercaDe)
{
    ui->setupUi(this);
}

Dialog_AcercaDe::~Dialog_AcercaDe()
{
    delete ui;
}
