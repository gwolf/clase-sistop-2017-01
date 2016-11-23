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

        // Permite crear un disco
        bool mkDisk(string diskName, long int diskSize, string user);
    protected:
    private:
      Colors colors;
};

#endif // DUMMYFILESYSTEM_H
