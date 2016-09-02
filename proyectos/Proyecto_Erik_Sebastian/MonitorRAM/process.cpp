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

#include "process.h"
#include "colib.h"
#include <unistd.h>

//Constructor sin parametros
Process::Process()
{

}

Process::~Process()
{

}

//Constructor con parametros
Process::Process(int m_P, int m_C, float m_MP)
{

}

//Funcion que asigna el valor del PID
FORCEINLINE void Process::set_PID(int P)
{
    m_PID = P;
}

//Funcion para obtener la cantidad que utiliza de RAM
bool Process::get_RAM()
{

}

//Funcion para obtener el contenido de la memoria del proceso
bool Process::get_RAMContents()
{

}

//Funcion que define el color para identificarlo
bool Process::set_Color(int val)
{

}
