/**********************************************************************
Definiciones de las clases de Qt para la ventana principal
Copyright (C) 2016  Erik Sanabria esanabria136@gmail.com
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_acercade.h"
#include "process.h"
#include <QTreeWidgetItem>
#include <QString>
#include <vector>
#include <unistd.h>

using std::vector;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTree(vector<Process> *data)      //Funcion que actualiza la informacion que se muestra en la GUI
{
    for(size_t i{}; i < data->size(); ++i)              //Ciclo que recorre todos los elementos del vector de procesos
    {
        QTreeWidgetItem *tmp= new QTreeWidgetItem(ui->treeWidget);      //creando un nuevo elemento de árbol de Qt

        QString va1 = QString::fromStdString(data->at(i).get_PID());    //convirtiendo informacion a QString
        QString va2 = QString::fromStdString(data->at(i).get_user());
        QString va3 = QString::fromStdString(data->at(i).get_Mem());
        QString va4 = QString::fromStdString(data->at(i).get_Exec());

        tmp->setText(0, va1);                                           //asignando la informacion al elemento
        tmp->setText(1, va2);
        tmp->setText(2, va3);
        tmp->setText(3, va4);
        ui->treeWidget->addTopLevelItem(tmp);                           //ahora si mostrando la informacion
    }

    sleep(60);                                                          //dormir este hilo para apreciar la informacion
    ui->treeWidget->clear();                                            //borrar todos los datos para volver a escribir desde cero. Asi no tenemos que saber las diferencias
}

void MainWindow::on_actionAcerca_De_triggered()
{   //Cuando se da click en el el menu de acerca de mostramos la ventana de acerca de
    Dialog_AcercaDe ayuda1;
    ayuda1.setModal(true);
    ayuda1.exec();
}

