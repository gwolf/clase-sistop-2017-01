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

#include "colib.h"

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
    //Constructor que toma parametros para asignar.
    Process(int m_P, int m_C, float m_MP);
    //Funcion para asignar el PID
    FORCEINLINE void set_PID(int P);
    //Funcion para obtener la cantidad de RAM que utiliza
    bool get_RAM();
    //Funcion para obtener los contenidos de la memoria
    bool get_RAMContents();
    //Funcion para asignar el color
    bool set_Color(int val);

private:
    //Numero del PID
    int m_PID;
    //Color que tomara visualmente almazenado en un entero
    int m_Color;
    //Variable para guardar la cantidad de RAM en Bytes
    unsigned long m_MemQuant;
    //Porcentaje de RAM que utiliza este proceso
    float m_MemPerc;
    //Cadena de caracteres que contiene el path del ejecutable
    string m_PATH;
    //Vector para guardar los contenidos de la memoria RAM de este proceso
    vector<unsigned short> m_contenidoRAM;
};

#endif // PROCESS_H
