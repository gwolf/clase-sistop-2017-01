/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase que servira como un pequeño interprete de comandos para el sistema
*/

#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include "Draw.h"
#include "Colors.h"
#include "DummyFileSystem.h"
#include <string>

using namespace std;

class CommandLine
{
    public:
        CommandLine();
        virtual ~CommandLine();
        //*****************Inicio comandos por parte de CMD*****************
        // Limpia el buffer de entrada
        void cleanBuffer();
        // Emitie mensajes de error
        void msgError(string msg);
        // Valida que exista un usuario en la sesion
        bool validateUser();
        // Muestra la informacion de un commando generico
        void genericCommand(string header, string optionalHeader,string fileContent);
        // Obtiene el comando introducido y lo ejecuta
        int getAndExecCommand(string command);
        // Interprete de comandos
        void interpreter();
        // Punto de acceso al programa
        void run();
        //*****************Fin comandos por parte de CMD*****************
        //****************Inicio comandos por parte de DFS***************
        // Permite crear un disco
        void mkDisk(string nameDisk, long int sizeDisk);
        void lsDisk();
        //*****************Fin comandos por parte de DFS*****************
    protected:
    private:
      // Encargado de dibujar en el sistema|
      Draw artist;
      // Para poner colores en la terminal :v
      Colors colors;
      // Usuario para la sesion
      string user;
      // Simula el sistema de ficheros
      DummyFileSystem dfs;
};

#endif // COMMANDLINE_H
