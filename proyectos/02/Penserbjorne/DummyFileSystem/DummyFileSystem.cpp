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

#define DISKTABLE "disktable.tbl"

using namespace std;

DummyFileSystem::DummyFileSystem(){
    //ctor
}

DummyFileSystem::~DummyFileSystem(){
    //dtor
}

// Permite crear un disco
bool DummyFileSystem::mkDisk(string diskName, long int diskSize, string user){
  Disk disk;
  FILE* fileDiskTable;
  FILE* fileDisk;
  string fileDiskName;

  fileDiskTable = fopen(DISKTABLE, "wb"); // Abrimos la tabla de discos exitentes

  if(fileDiskTable){  // Abrimos la tabla de discos
    // Asignamos datos del disco
    disk.name = diskName;
    disk.size = diskSize;
    disk.user = user;

    fileDiskName = diskName + ".dsk";
    fileDisk = fopen( fileDiskName.c_str(), "wb");

    if(fileDisk){ // Abrimos el disco
      if(fwrite(&disk, sizeof(Disk), 1, fileDisk)){ // Escribimos en el
        if(fwrite(&disk, sizeof(Disk), 1, fileDiskTable)){  // Registramos el disco en la tabla de discos
          fclose(fileDisk);
          fclose(fileDiskTable);
          cout<<this->colors.FGRN("\tDisco creado")<<endl;
          cout<<this->colors.FYEL("\tID: ")<<disk.idDisk<<endl;
          cout<<this->colors.FYEL("\tName: ")<<disk.name<<endl;
          cout<<this->colors.FYEL("\tSize: ")<<disk.size<<" MB"<<endl;
          return true;
        }
        // No se pudo registrar el disco en la tabla
        fclose(fileDisk);
        fclose(fileDiskTable);
        // Eliminamos el disco
        remove(fileDiskName.c_str());
        return false;
      }
      // No se pudo escribir en el disco
      fclose(fileDisk);
      fclose(fileDiskTable);
      // Eliminamos el disco
      remove(fileDiskName.c_str());
      return false;
    }else{
      // No se pudo crear el disco
      fclose(fileDiskTable);
      return false;
    }
  }else{
    // No se pudo abrir la tabla de discos
    return false;
  }
}
