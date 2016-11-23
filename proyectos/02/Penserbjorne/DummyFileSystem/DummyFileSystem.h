/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase que servira como base para el sistema de ficheros
*/

#ifndef DUMMYFILESYSTEM_H
#define DUMMYFILESYSTEM_H

#include <string>
#include "Colors.h"

using namespace std;

class DummyFileSystem
{
    public:
        DummyFileSystem();
        virtual ~DummyFileSystem();

        // Emitie mensajes de error
        void msgError(string msg);
        // Permite crear un fichero
        void mkFile(string content);
        // Permite crear un directorio
        void mkDir(string path);
        // Permite crear un disco
        bool mkDisk(string diskName, long int diskSize, string user);
        // Permite listar los discos existentes
        void lsDisk();
        // Permite listar el contenido de un disco
        void lsDisk(string diskName);

    protected:
    private:
      Colors colors;
};

#endif // DUMMYFILESYSTEM_H
