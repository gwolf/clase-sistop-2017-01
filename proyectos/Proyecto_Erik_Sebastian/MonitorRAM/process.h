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
    //Constructor que solo toma m_P como argumento.
    Process(unsigned int m_P);
    //Constructor que toma parametros para asignar.
    Process(int m_P, int m_C, float m_MP);
    //Funcion para asignar el PID
    void set_PID(unsigned int P);
    //Fundion para establecer el ejecutable
    void set_Exec(string name);
    //Funcion para asignar porcentaje RAM
    void set_RAMPerc(double perc);
    //Funcion para establecer el usuario del PID
    void set_User(string name);

private:
    //Numero del PID
    unsigned int m_PID;
    //Color que tomara visualmente almazenado en un entero
    int m_Color;
    //Variable para guardar la cantidad de RAM en Bytes
    unsigned long m_MemQuant;
    //Porcentaje de RAM que utiliza este proceso
    double m_MemPerc;
    //Cadena de caracteres que contiene el path del ejecutable
    string m_PATH;
    //Variable para guardar el usuario del PID
    string m_user;
};

#endif // PROCESS_H
