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
#include <unistd.h>

//Constructor sin parametros
Process::Process()
{

}

Process::~Process()
{
    m_contenidoRAM.clear();
    m_contenidoRAM.shrink_to_fit();
    m_PATH.clear();
    m_PATH.shrink_to_fit();
}

//Constructor que solo toma m_P como argumento.
Process::Process(unsigned int m_P)
{
    m_PID = m_P;
}

//Constructor con parametros
Process::Process(int m_P, int m_C, float m_MP)
{

}

//Funcion que asigna el valor del PID
void Process::set_PID(unsigned int P)
{
    m_PID = P;
}

//Fundion para establecer el ejecutable
void Process::set_Exec(string name)
{
    m_PATH = name;
}

//Funcion para asignar porcentaje RAM
void Process::set_RAMPerc(double perc)
{
    m_MemPerc = perc;
}
