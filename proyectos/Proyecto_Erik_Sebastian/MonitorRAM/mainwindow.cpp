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
#include <iostream>

using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTree(std::vector<Process> *data)
{
    QTreeWidgetItem *tmp= new QTreeWidgetItem(ui->treeWidget);

    for(size_t i{}; i < data->size(); ++i)
    {
        QString va1 = QString::fromStdString(data->at(i).get_PID());
        QString va2 = QString::fromStdString(data->at(i).get_user());
        QString va3 = QString::fromStdString(data->at(i).get_Mem());
        QString va4 = QString::fromStdString(data->at(i).get_Exec());

        cout << "\t" << data->at(i).get_PID() << "\t" << data->at(i).get_user() << "\t" << data->at(i).get_Mem() << "\t" << data->at(i).get_Exec() << endl;

        tmp->setText(0, va1);
        tmp->setText(1, va2);
        tmp->setText(2, va3);
        tmp->setText(3, va4);
        ui->treeWidget->insertTopLevelItem(1, tmp);
    }

//    QString val1 = "PID goes here";
//    QString val2 = "User goes here";
//    QString val3 = "RAM percentage goes here";
//    QString val4 = "Executable path goes here";
//    tmp->setText(0, val1);
//    tmp->setText(1, val2);
//    tmp->setText(2, val3);
//    tmp->setText(3, val4);
//    ui->treeWidget->insertTopLevelItem(1, tmp);
    sleep(1);
    system("clear");
    ui->treeWidget->clear();
}

void MainWindow::on_actionAcerca_De_triggered()
{   //Cuando se da click en el el menu de acerca de mostramos la ventana de acerca de
    Dialog_AcercaDe ayuda1;
    ayuda1.setModal(true);
    ayuda1.exec();
}

