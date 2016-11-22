/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase que servira como base para el sistema de ficheros
*/

#include "DummyFileSystem.h"
#include "Disk.h"
#include <iostream>
#include <ctime>
#include <string>
#include <stdio.h>  // Mas rapido que fstream :3

using namespace std;

DummyFileSystem::DummyFileSystem(){
    //ctor
}

DummyFileSystem::~DummyFileSystem(){
    //dtor
}

bool DummyFileSystem::mkDisk(string diskName, long int diskSize){
  Disk disk;

  disk.name = diskName;
  disk.size = diskSize;

  FILE* fileDisk;
  string fileDiskName = diskName + ".dsk";
  fileDisk = fopen( fileDiskName.c_str(), "wb");

  if(fileDisk){
    if(fwrite(&fileDisk, sizeof(Disk), 1, fileDisk)){
      fclose(fileDisk);
      cout<<this->colors.FGRN("\tDisco creado")<<endl;
      cout<<this->colors.FYEL("\tID: ")<<disk.idDisk<<endl;
      cout<<this->colors.FYEL("\tName: ")<<disk.name<<endl;
      cout<<this->colors.FYEL("\tSize: ")<<disk.size<<" MB"<<endl;
      return true;
    }
    fclose(fileDisk);
    return false;
  }else{
    return false;
  }
}
