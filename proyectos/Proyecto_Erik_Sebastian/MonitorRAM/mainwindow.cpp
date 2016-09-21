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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::get_PUi()
{
    return ui;
}

void MainWindow::on_actionAcerca_De_triggered()
{   //Cuando se da click en el el menu de acerca de mostramos la ventana de acerca de
    Dialog_AcercaDe ayuda1;
    ayuda1.setModal(true);
    ayuda1.exec();
}

