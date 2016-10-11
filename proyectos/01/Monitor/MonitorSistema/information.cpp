#include "information.h"
#include "ui_information.h"

Information::Information(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Information)
{
    ui->setupUi(this);
    QPixmap icon(":/Iconos/Images/mainWindowIcon.png");
    ui->iconLabel->setPixmap(icon);
}

Information::~Information()
{
    delete ui;
}

void Information::on_creditsButton_clicked()
{
    QString autores = "<ul><li>Quiñones Rivera Josué Emanuel.</li><li>Vázquez Álvarez Ángel Eduardo</li></ul>";
    QMessageBox::information(this, "Créditos", autores, QMessageBox::Ok);
}
