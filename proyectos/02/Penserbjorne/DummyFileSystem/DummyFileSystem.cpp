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
#include <cstdio>  // Mas rapido que fstream :3
#include <algorithm>

#define DISKTABLE "disktable.tbl"
#define DISKEXT ".dsk"

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

// Permite crear un directorio
void DummyFileSystem::mkDir(string path){
  vector<string> splitPath;  // Aqui guardaremos la ruta ya separada
  string delimiter = "/"; // Las rutas se separan por diagonales
  string token;
  size_t pos = 0;

  FILE* fileDisk;
  int i,j;
  // Obtenemos los directorios
  while ((pos = path.find(delimiter)) != string::npos) {
      token = path.substr(0, pos);
      splitPath.insert(splitPath.end(), token);
      path.erase(0, pos + delimiter.length());
  }
  splitPath.insert(splitPath.end(), path);

  splitPath[0] += DISKEXT;
  // corroboramos si el archivo del disco existe
  fileDisk = fopen( splitPath[0].c_str(), "r");
  if(fileDisk){
    // Existe!!! lo cerramos y abrimos a modos escritura
    fclose(fileDisk);
    fileDisk = fopen( splitPath[0].c_str(), "a");

    // Escribimos los directorios
    for(i = 1; i < splitPath.size(); i++){
      for( j = 1; j < i+1; j++){  // Tabulamos para que se vea mejor
        fprintf(fileDisk, "\t");
      }
      splitPath[i] = this->colors.FCYN(splitPath[i]);
      fprintf(fileDisk, "%s /\n", splitPath[i].c_str());  // Escribimos el directorio
    }

    fclose(fileDisk);
  }else{
    string msg = "No se pudo abrir el disco " + this->colors.BYEL(splitPath[0]) + ". ¿Si existe?";
    this->msgError(msg);
  }
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

    fileDiskName = diskName + DISKEXT;
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
    this->msgError("No se puede abrir la tabla de discos. Prueba añadiendo un disco.");
    return false;
  }
}

// Permite listar los discos existentes
void DummyFileSystem::lsDisk(){
  int countDisk;
  FILE* fileDiskTable;
  char caracter;

  fileDiskTable = fopen(DISKTABLE, "r"); // Abrimos la tabla de discos exitentes

  if(fileDiskTable){  // Abrimos la tabla de discos
      cout<<endl;
      countDisk = 0;
      while(!feof(fileDiskTable)){  // Leemos los registros de la tabla
        caracter = fgetc(fileDiskTable);
        if(caracter != EOF){
          cout<<caracter;
        }
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

// Permite listar los discos existentes
void DummyFileSystem::lsDisk(string diskName){
  FILE* fileDisk;
  char caracter;

  diskName += DISKEXT;
  fileDisk = fopen(diskName.c_str(), "r"); // Abrimos la tabla de discos exitentes

  if(fileDisk){  // Abrimos la tabla de discos
      cout<<endl;
      while(!feof(fileDisk)){  // Leemos los registros de la tabla
        caracter = fgetc(fileDisk);
        if(caracter != EOF){
          cout<<caracter;
        }
      }
      cout<<endl;
      fclose(fileDisk);
  }else{
    // No se pudo abrir la tabla de discos
    string msg = "No se pudo abrir el disco " + this->colors.BYEL(diskName) + ". ¿Si existe?";
    this->msgError(msg);
  }
}
