/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase base para simular un disco
*/

#ifndef DISK_H
#define DISK_H

#include <ctime>
#include <string>

using namespace std;

class Disk
{
    public:
        time_t idDisk;
        char* dateCreation;
        string name;
        long int size;
        string user;
        bool idMounted;

        Disk();
        virtual ~Disk();
    protected:
    private:
      string header;
};

#endif // DISK_H
