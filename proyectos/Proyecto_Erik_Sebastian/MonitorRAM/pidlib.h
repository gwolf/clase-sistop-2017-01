/**********************************************************************
Funcion para conseguir numero de proceso
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
//http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
#ifndef PIDLIB_H
#define PIDLIB_H

#include "process.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;
using std::endl;
using std::getline;
using std::ofstream;
using std::ifstream;

namespace PIDLIB
{
    void parseSysInfo(vector<string> *pCP)
    {
        ofstream archTest{ "procesos.txt" };
        char buffer[256];
        string resultado;
        FILE *salida1 = popen("ps aux", "r");

        if(!salida1)
        {
            throw std::runtime_error("popen() fallo!");
        }

        while(!feof(salida1))
        {
            resultado.clear();

            if(fgets(buffer, 256, salida1) != NULL)
            {
                for(int i{ 0 }; i < 256; ++i)
                {
                    if(buffer[i] == '\n')
                    {
                        break;
                    }

                    resultado += buffer[i];
                }

                pCP->push_back(resultado);

                archTest << resultado << endl;
            }
        }

        archTest.close();
    }

    bool parseSysInfo_CPP(vector<string> *pCP)
    {
        if(system("ps aux > procesos2.txt"))
        {
            return false;
        }

        string cadena;
        ifstream arch2{ "procesos2.txt" };

        while(!arch2.eof())
        {
            cadena.clear();
            getline(arch2, cadena, '\n');
            pCP->push_back(cadena);
        }

        arch2.close();
    }

    bool get_PIDs(vector<Process> *pvP)
    {

    }
}

#endif // PIDLIB_H
