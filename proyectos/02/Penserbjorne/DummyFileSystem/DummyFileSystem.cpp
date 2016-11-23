/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase que servira como base para el sistema de ficheros
*/

#include "DummyFileSystem.h"
#include "Disk.h"
#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include <stdio.h>  // Mas rapido que fstream :3

#define DISKTABLE "disktable.tbl"

using namespace std;

DummyFileSystem::DummyFileSystem(){
    //ctor
}

DummyFileSystem::~DummyFileSystem(){
    //dtor
}

// Emitie mensajes de error
void DummyFileSystem::msgError(string msg){
  msg = this->colors.FRED("\tError:\t") + msg + "\n";
  cout<<msg;
}

// Permite crear un disco
bool DummyFileSystem::mkDisk(string diskName, long int diskSize, string user){
  Disk disk;
  FILE* fileDiskTable;
  FILE* fileDisk;
  string fileDiskName;

  fileDiskTable = fopen(DISKTABLE, "a"); // Abrimos la tabla de discos exitentes

  if(fileDiskTable){  // Abrimos la tabla de discos
    // Asignamos datos del disco
    disk.name = diskName;
    disk.size = diskSize;
    disk.user = user;

    fileDiskName = diskName + ".dsk";
    fileDisk = fopen( fileDiskName.c_str(), "w");

    if(fileDisk){ // Abrimos el disco
      if(fprintf(fileDisk, "%s", disk.toString().c_str())){ // Escribimos en el
        if(fprintf(fileDiskTable, "%s",  disk.toString().c_str())){  // Registramos el disco en la tabla de discos
          fclose(fileDisk);
          fclose(fileDiskTable);
          cout<<this->colors.FGRN("\n\tDisco creado")<<endl<<endl<<disk.toString();
          return true;
        }
        // No se pudo registrar el disco en la tabla
        fclose(fileDisk);
        fclose(fileDiskTable);
        // Eliminamos el disco
        remove(fileDiskName.c_str());
        this->msgError("No se pudo registrar el disco.");
        return false;
      }
      // No se pudo escribir en el disco
      fclose(fileDisk);
      fclose(fileDiskTable);
      // Eliminamos el disco
      remove(fileDiskName.c_str());
      this->msgError("No se pudo escribir el disco.");
      return false;
    }else{
      // No se pudo crear el disco
      fclose(fileDiskTable);
      this->msgError("No se pudo crear el disco.");
      return false;
    }
  }else{
    // No se pudo abrir la tabla de discos
    this->msgError("No se puede abrir la tabla de discos.");
    return false;
  }
}

// Permite listar los discos existentes
void DummyFileSystem::lsDisk(){
  Disk disk;
  int countDisk;
  FILE* fileDiskTable;
  char caracter;

  fileDiskTable = fopen(DISKTABLE, "r"); // Abrimos la tabla de discos exitentes

  if(fileDiskTable){  // Abrimos la tabla de discos
      cout<<endl;
      countDisk = 0;
      while(!feof(fileDiskTable)){  // Leemos los registros de la tabla
        caracter = fgetc(fileDiskTable);
        cout<<caracter;
        if(caracter == '\n'){
          countDisk++;
        }
      }
      if(!countDisk){
        cout<<"\tNo hay discos para mostrar."<<endl;
      }
      fclose(fileDiskTable);
  }else{
    // No se pudo abrir la tabla de discos
    this->msgError("No se puede abrir la tabla de discos.");
  }
}
