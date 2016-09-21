/**********************************************************************
Funcion principal del programa
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
#include "process.h"
#include "pidlib.h"
#include <QApplication>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <thread>
#include <atomic>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::thread;
using std::atomic;

int main(int argc, char *argv[])
{  
    vector<string> test2;                   //vector que contiene la informacion de la salida de ps aux
    vector<Process> proceso;                //vector de clase proceso que contiene la informacion ya categorizada
    size_t line{};                          //renglones de la salida de ps aux
    atomic<bool> banderaGUI{ false };       //semaforo que checa si existe la GUI

    QApplication a(argc, argv);             //entorno de Qt para la GUI
    MainWindow w;                           //ventana principal de Qt
    w.show();                               //mostrando la ventana principal

    banderaGUI = true;                      //y prendiendo el semaforo de que existe

    //Iniciando el hilo
    thread t(PIDLIB::getProcessesInfo, &proceso, &test2, &line, &banderaGUI);

    cout << endl << w.get_PUi() << endl;

    int ret{ a.exec() };                    //ciclo de aplicacion GUI implementado por Qt

    banderaGUI = false;                     //cuando salimos del ciclo, que se cierra la ventana apagar el semaforo

    t.join();                               //unir los dos hilos

    //limpiar los vectores, vaciarlos
    test2.clear();
    test2.shrink_to_fit();
    proceso.clear();
    proceso.shrink_to_fit();
    return ret;
}
