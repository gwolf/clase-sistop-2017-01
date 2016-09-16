/**********************************************************************
Definicion de clase para guardar la informacion de los procesos
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

#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

//Clase que define una instancia de proceso
class Process
{
public:
    //Constructor default
    Process();
    //destructos default
    ~Process();
    //Constructor que solo toma PID como argumento.
    Process(unsigned int m_P);
    //Constructor que solo toma m_MemPerc como parametro.
    Process(double m_RP);
    //Constructor que solo toma exec como parametro
    Process(string path_exec);
    //Funcion para asignar el PID
    void set_PID(unsigned int P);
    //Fundion para establecer el ejecutable
    void set_Exec(string name);
    //Funcion para asignar porcentaje RAM
    void set_RAMPerc(double perc);
    //Funcion para establecer el usuario del PID
    void set_User(string name);

    unsigned int get_PID();
    string get_Exec();
    string get_user();
    double get_Mem();


private:
    //Numero del PID
    unsigned int m_PID;
    //Porcentaje de RAM que utiliza este proceso
    double m_MemPerc;
    //Cadena de caracteres que contiene el path del ejecutable
    string m_PATH;
    //Variable para guardar el usuario del PID
    string m_user;
};

#endif // PROCESS_H
