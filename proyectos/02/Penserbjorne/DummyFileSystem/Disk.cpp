/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase base para simular un disco
*/

#include "Disk.h"
#include <ctime>

Disk::Disk(){
    //ctor
    this->header = "DFS_DSk";
    this->idDisk = time(0);
    this->dateCreation = ctime(&this->idDisk);
    this->isMounted = false;
}

Disk::~Disk(){
    //dtor
}
