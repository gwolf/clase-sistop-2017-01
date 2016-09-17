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

Fuentes de informacion:
http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
http://www.cyberciti.biz/faq/show-all-running-processes-in-linux/
*********************************************************************/
#ifndef PIDLIB_H
#define PIDLIB_H

#include "process.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <atomic>

using std::vector;
using std::string;
using std::endl;
using std::getline;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::atomic;

namespace PIDLIB
{
    //Funcion que consigue los procesos en ejecucion estilo C
    void parseSysInfo(vector<string> *pCP)
    {
        ofstream archTest{ "procesos.txt" };        //archivo para guardar resultados, solo para comprobar resultados
        char buffer[256];                           //buffer de caracteres para guardar cada linea
        string resultado;                           //cadena C++ para guardar el buffer
        FILE *salida1 = popen("ps aux", "r");       //ejecutar ps aux en modo lectura

        if(!salida1)                                //si la ejecucion de ps aux no fue exitosa
        {
            throw std::runtime_error("popen() fallo!");     //mandar error
        }

        while(!feof(salida1))                       //mientras no llegamos al fin del resultado de ps aux
        {
            resultado.clear();                      //asegurarnos de que resultado este vacio

            if(fgets(buffer, 256, salida1) != NULL) //escribir un renglon de maximo 256 caracteres al buffer
            {
                for(int i{ 0 }; i < 256; ++i)       //mientras que no lleguemos al caracter 256 del buffer...
                {
                    if(buffer[i] == '\n')           //... comparar si es fin de linea
                    {
                        break;                      //si lo es terminar...
                    }

                    resultado += buffer[i];         //..si el caracter no es din de linea agregarlo a resultado
                }

                pCP->push_back(resultado);          //guardar resultado en el vector de cadenas

                archTest << resultado << endl;      //escribir la linea en el archivo
            }
        }

        archTest.close();                           //cerrar archivo
    }

    //funcion que optiene los procesos en ejecucion estilo C++
    //Opte por usar esta funcion ya que no me gusto combinar tanto C con C++
    //A pesar de que esta funcion tambien utiliza C pero mucho menos, solo system()
    bool parseSysInfo_CPP(vector<string> *pCP, size_t *lines)
    {
        if(system("ps aux > procesos2.txt"))        //ejecutar "ps aux > procesos2.txt" mediante system()
        {                                           //utilizando pipes de shell para guardar los resultados en procesos 2.txt
            return false;                           //si fallo terminar funcion
        }

        string cadena;                              //cadena C++ para guardar los renglones del archivo
        ifstream arch2{ "procesos2.txt" };          //abrir el archivo

        *lines = 0;                                 //asegurarnos de que lines es cero

        while(!arch2.eof())                         //mientras no es fin de archivo...
        {
            cadena.clear();                         //asegurarnos de que la cadena este vacia
            getline(arch2, cadena);                 //leer un renglon de arch2 y guardarlo en cadena
            pCP->push_back(cadena);                 //guardar cadena en el vector de cadenas
            ++*lines;                               //incrementar lines
        }

        pCP->erase(pCP->begin());                   //borrar el primer elemento del vector ya que este contiene titulos de las columnas, resultado de ps aux
        pCP->shrink_to_fit();                       //redimenzionar para tomar en cuenta el elemento ya borrado

        arch2.close();                              //cerrar el archivo arch2

        return true;
    }

    //Funcion que ingresa los PIDs del vector de cadenas al vector de Process
    bool set_PIDs(vector<Process> *pvP, vector<string> *pC, size_t *lines)
    {
        unsigned int num{};                                 //variable en donde se va a guardar el PID
        size_t h{};                                         //variable de ubicacion en la cadena de donde se encuentra el primer digito de PID
        size_t dh{};                                        //variable de longitud del PID en la cadena antes de llegar a un espacio

        for(int i{}; i < (*lines) - 1; ++i)                 //ciclo que recorre todo el vector de cadenas, cada cadena es un renglon
        {
            h = pC->at(i).find_first_of("123456789");       //igualar a h con el indice de la cadena donde se encuentra el primer numero
            dh = 0;                                         //asegurarnos de que dh es cero al empezar el ciclo

            for(int w{ h }; w < h + 5; ++w)                 //ciclo para encontrar el primero espacio despues del indice h de la cadena
            {
                if(pC->at(i).at(w) == ' ')                  //si es espacio...
                {
                    break;                                  //terminar el ciclo
                }
                else
                {
                    ++dh;                                   //en caso contrario incrementar dh
                }
            }

            string tmp{ pC->at(i).substr(h, dh) };          //cadena tmp que guarda el PID, se extrae la cadena que empieza en h y termina en h + dh
            num = atoi(tmp.c_str());                        //conseguir la cadena tipo C de tmp y con atoi guardarla en num

            Process ptmp(num);                              //constructor de clase Process que toma como parametro el PID

            pvP->push_back(ptmp);                           //guardar la clase en el vector de Process
        }
        return true;
    }

    //funcion para asignar el porcentaje de ram de cada PID
    bool set_RAMPerc(vector<Process> *pvP, vector<string> *pC, size_t *line)
    {
        size_t h{};                             //variable de indice de la cadena
        size_t dh{};                            //variable de indice de diferencia entre h y el final del numero
        const string delimitantes{ "." };       //cadena constante delimitantes que contiene un punto .
        const string delimitantes2{ " " };      //cadena constante delimitantes2 que contiene un espacio

        for(int i{}; i < (*line) - 1; ++i)      //ciclo que recorre todo el vector de cadenas
        {
            h = pC->at(i).find_first_of(delimitantes);  //encontrar el primer punto y guardarlo en h
            ++h;                                        //incrementar h ya que despues del punto hay un digito y de esta manera al volver a buscar un punto ya no repetimos el que ya encontramos
            h = pC->at(i).find_first_of(delimitantes, h);   //volver a buscar un punto pero ahora despues del que ya encontramos

            --h;            //decrementar h dos vezes ya que antes del punto puede tener hasta dos digitos por ejemplo 55.0, no llega hasta tres digitos porque...
            --h;            //... si no ya seria 100.0%

            dh = pC->at(i).find_first_of(delimitantes2, h + 1);    //ahora encontrar el primer espacio despues del indice h
            dh = dh -h;                                            //calcular la diferencia y guardarla en dh
            string tmp{ pC->at(i).substr(h, dh) };                  //cadena tmp que guarda la subcadena de los indices h + dh

            pvP->at(i).set_RAMPerc(atof(tmp.c_str()));              //convertir a flotante la cadena tipo C y guardarla en la clase mediante su miembro y guardarlo en el vector de Process
        }

        return true;
    }

    //Funcion que asigna los ejecutables de cada PID
    bool set_Execs(vector<Process> *pvP, vector<string> *pC, size_t *line)
    {
        size_t h{};                             //indice h de la cadena
        size_t dh{};                            //diferencia de indices de la cadena
        size_t espacios{};                      //contador de espacios
        bool space{ false };                    //bandera de si hay espacios

        const string delimitantes{ "abcdefghijklmnopqrstuvwxyz/[(ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };   //el path del ejecutable puede empezar con cualquiera de estos caracteres

        for(int i{}; i < (*line) - 1; ++i)      //ciclo que recorre el vector de cadenas
        {
            espacios = 0;                       //inicializar el contador de espacios cada ciclo a cero

            for(int g{};; ++g)                  //ciclo que recorre la cadena misma, osea cada renglon
            {
                if((pC->at(i).at(g) == ' ') && !space)      //si encontramos un espacio pero no hemos encontrado espacios antes...
                {
                    space = true;                           //... ya encontramos un espacio
                    h = g;                                  //el indice h es el indice g
                    ++espacios;                             //incrementar contador
                }
                else if(space && (espacios == 10))          //si ya encontramos un espacio antes y han sido 10, asi sale el output de ps aux
                {
                    h = pC->at(g).find_first_of(delimitantes, h);   //... ahora si podemos encontrar el primer caracter de delimitantes
                    break;                                          //terminat el ciclo interno
                }
                else if(space && (pC->at(i).at(g) == ' '))      //si hemos encontrado un espacio antes y el siguiente caracter es un espacio, osea varios espacios juntos...
                {
                    continue;                                   //solo continuamos a la siguiente iteracion, como la bandera es verdadera no se cuentan los espacios que estan juntos
                }
                else if(pC->at(i).at(g) != ' ')                 //si ninguna de esas condiciones se cuplieron, no hay espacio...
                {
                    space = false;                              //... apagamos la bandera
                }
            }

            dh = pC->at(i).length() - h;    //como ps aux escribe el ejecutable al final dh es igual a la diferencia del indice h y el final de la cadena

            pvP->at(i).set_Exec(pC->at(i).substr(h, dh));   //guardar la cadena con los indices h + dh mediante el miembro de la clase set_Exec y guardarlo en el vector de Process
        }

        return true;
    }

    //Funcion que asigna los usuarios de los PIDs
    bool set_User(vector<Process> *pvP, vector<string> *pC, size_t *line)
    {
        size_t dh{};                        //aqui solo se necesita un indice final ya que ps aux saca los usuarios al principio
        const string delimitante{ " " };    //delimitante de un espacio

        for(int i{}; i < (*line) - 1; ++i)  //ciclo que recorre el vector de cadenas
        {
            dh = pC->at(i).find_first_of(delimitante);  //cuando encontremos el primer espacio ese es el usuario

            pvP->at(i).set_User(pC->at(i).substr(0, dh));   //lo guardamos mediante set_User en la clase y posteriormente en el vector de Process
        }

        return true;
    }

    //funcion que actualiza el QTreeWidget
    void update_Qtree()
    {

    }

    //Funcion para encapsular todas las funciones superiores y correrlas en un hilo
    bool getProcessesInfo(vector<Process> *m_vP, vector<string> *m_vsC, size_t *m_line, atomic<bool> *flag)
    {
        while(*flag)    //flag es la bandera de si existe la GUI, mientras existe hacer todas las funciones superiores
        {
            if(!parseSysInfo_CPP(m_vsC, m_line))    //ejecutando ps aux y guardandolo en un archivo de texto
            {
                return false;
            }

            --(*m_line);    //decrementamos las lineas ya que removimos el primer elemento del vector de cadenas
            m_vP->reserve(*m_line); //reservando la memoria para el vector de Process

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

            m_vP->shrink_to_fit();  //asegurandonos de que no haya basura en el vector, que no haya demas informacion

            //Aqui poner funcion que mande la informacion a QTree...
            //void update_Qtree()...

            //limpiando los vectores para el siguiente ciclo
            m_vP->clear();
            m_vP->shrink_to_fit();
            m_vsC->clear();
            m_vsC->shrink_to_fit();
        }

        cout << endl <<"Finished calculationg on thread..." << endl;

        return true;
    }
}

#endif // PIDLIB_H
