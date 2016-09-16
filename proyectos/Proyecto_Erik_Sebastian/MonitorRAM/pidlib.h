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
//http://www.cyberciti.biz/faq/show-all-running-processes-in-linux/
#ifndef PIDLIB_H
#define PIDLIB_H

#include "process.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using std::vector;
using std::string;
using std::endl;
using std::getline;
using std::ofstream;
using std::ifstream;
using std::cout;

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

    bool parseSysInfo_CPP(vector<string> *pCP, size_t *lines)
    {
        if(system("ps aux > procesos2.txt"))
        {
            return false;
        }

        string cadena;
        ifstream arch2{ "procesos2.txt" };

        *lines = 0;

        while(!arch2.eof())
        {
            cadena.clear();
            getline(arch2, cadena);
            pCP->push_back(cadena);
            ++*lines;
        }

        pCP->erase(pCP->begin());
        pCP->shrink_to_fit();

        arch2.close();

        return true;
    }

    bool set_PIDs(vector<Process> *pvP, vector<string> *pC, size_t *lines)
    {
        unsigned int num{};
        size_t h{};
        size_t dh{};

        if(pvP->size() < *lines)
        {
            return false;
        }

        for(int i{}; i < (*lines) - 1; ++i)
        {
            h = pC->at(i).find_first_of("123456789");
            dh = 0;

            for(int w{ h }; w < h + 5; ++w)
            {
                if(pC->at(i).at(w) == ' ')
                {
                    break;
                }
                else
                {
                    ++dh;
                }
            }

            string tmp{ pC->at(i).substr(h, dh) };
            num = atoi(tmp.c_str());

            pvP->at(i).set_PID(num);
        }
        return true;
    }

    bool set_RAMPerc(vector<Process> *pvP, vector<string> *pC, size_t *line)
    {
        size_t h{};
        size_t dh{};
        const string delimitantes{ "." };
        const string delimitantes2{ " " };


        if(pvP->size() < *line)
        {
            return false;
        }

        for(int i{}; i < (*line) - 1; ++i)
        {
            h = pC->at(i).find_first_of(delimitantes);
            ++h;
            h = pC->at(i).find_first_of(delimitantes, h);

            --h;
            --h;

            dh = pC->at(i).find_first_of(delimitantes2, h + 1);
            dh = dh -h;
            string tmp{ pC->at(i).substr(h, dh) };

            pvP->at(i).set_RAMPerc(atof(tmp.c_str()));
        }

        return true;
    }

    bool set_Execs(vector<Process> *pvP, vector<string> *pC, size_t *line)
    {
        size_t h{};
        size_t dh{};
        size_t espacios{};
        bool space{ false };

        const string delimitantes{ "abcdefghijklmnopqrstuvwxyz/[(ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
        const string delim{ " " };

        if(pvP->size() < *line)
        {
            return false;
        }

        for(int i{}; i < (*line) - 1; ++i)
        {
            espacios = 0;

            for(int g{};; ++g)
            {
                if((pC->at(i).at(g) == ' ') && !space)
                {
                    space = true;
                    h = g;
                    ++espacios;
                }
                else if(space && (espacios == 10))
                {
                    h = pC->at(g).find_first_of(delimitantes, h);
                    break;
                }
                else if(space && (pC->at(i).at(g) == ' '))
                {
                    continue;
                }
                else if(pC->at(i).at(g) != ' ')
                {
                    space = false;
                }
            }

            dh = pC->at(i).length() - h;

            pvP->at(i).set_Exec(pC->at(i).substr(h, dh));
        }

        return true;
    }

    bool set_User(vector<Process> *pvP, vector<string> *pC, size_t *line)
    {
        size_t dh{};
        const string delimitante{ " " };

        if(pvP->size() < *line)
        {
            return false;
        }

        for(int i{}; i < (*line) - 1; ++i)
        {
            dh = pC->at(i).find_first_of(delimitante);

            pvP->at(i).set_User(pC->at(i).substr(0, dh));
        }

        return true;
    }

    //Funcion para encapsular todas las funciones superiores y correrlas en hilos
    bool getProcessesInfo(vector<Process> *m_vP, vector<string> *m_vsC, size_t *m_line)
    {
        if(!parseSysInfo_CPP(m_vsC, m_line))
        {
            return false;
        }

        --(*m_line);
        m_vP->reserve(*m_line);

        if(!set_PIDs(m_vP, m_vsC, m_line))
        {
            return false;
        }

        if(!set_Execs(m_vP, m_vsC, m_line))
        {
            return false;
        }

        if(!set_RAMPerc(m_vP, m_vsC, m_line))
        {
            return false;
        }

        if(!set_User(m_vP, m_vsC, m_line))
        {
            return false;
        }

        return true;
    }
}

#endif // PIDLIB_H
