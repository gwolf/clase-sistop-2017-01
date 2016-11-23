/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase base para simular un disco
*/

#include "Disk.h"
#include <ctime>
#include <string>

using namespace std;

Disk::Disk(){
    //ctor
    this->header = "DFS_DSk";
    this->idDisk = time(0);
    this->dateCreation = ctime(&this->idDisk);
}

Disk::~Disk(){
    //dtor
}

string Disk::toString(){
  string values = "";
  values += this->colors.FYEL("\tID: ") + to_string(this->idDisk) + "\n";
  values += this->colors.FYEL("\tName: ") + this->name + "\n";
  values += this->colors.FYEL("\tSize: ") + to_string(this->size) + " MB" + "\n";
  values += this->colors.FYEL("\tCreator: ") + this->user + "\n";
  values += this->colors.FYEL("\tCreated: ") + this->dateCreation + "\n";
  return values;
}
