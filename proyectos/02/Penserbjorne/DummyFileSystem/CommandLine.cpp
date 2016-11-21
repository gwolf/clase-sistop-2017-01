/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase que servira como un pequeño interprete de comandos para el sistema
*/

#include "CommandLine.h"
#include "Colors.h"
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

enum commands{
  NO_COMMAND = -1,
  EXIT
};

CommandLine::CommandLine(){
    //ctor
    this->user = "";
    artist.drawTop(1);
    artist.drawDFS();
    artist.drawBottom(1);
}

CommandLine::~CommandLine(){
    //dtor
}

// Limpia el buffer de entrada
void CommandLine::cleanBuffer(){
  while(getchar() != '\n');
}

// Emitie mensajes de error
void CommandLine::msgError(string msg){
  msg = string("\tError:\t") + msg + "\n";
  colors.FRED(msg);
}

// Valida que exista un usuario en la sesion
bool CommandLine::validateUser(){
  if(this->user == ""){
    this->msgError("No hay un usuario definido para esta sesion.");
    return false;
  }else{
    return true;
  }
}

// Obtiene el comando introducido y lo ejecuta
int CommandLine::getAndExecCommand(string command){
  string command_eval;  // Aqui guardaremos el comando
  string delimiter = " "; // Los comandos se separan por espacios
  size_t pos = 0;

  // Obtenemos el comando enviado
  command_eval = command.substr(pos, command.find(delimiter));
  // Lo convertimos a minusculas
  transform(command_eval.begin(), command_eval.end(), command_eval.begin(), ::tolower);

  if(command_eval == "exit"){
    return EXIT;
  }else{
    this->msgError(command_eval + " no es un comando.");
    return NO_COMMAND;
  }
}

// Interprete de comandos
void CommandLine::interpreter(){
  string user_output = "\t@" + this->user + " > ";
  string command; // Comando que se ejecutara
  int intCommand; // Valor entero equivalente al comando

  cleanBuffer();
  do{
    artist.drawTop(1);
    colors.FBLU(user_output);
    getline(cin, command);
    intCommand = getAndExecCommand(command);
    artist.drawBottom(1);
  }while (intCommand != EXIT);
}

// Punto de acceso al programa
void CommandLine::run(){
  artist.drawTop(1);  // Dibujamos la parte superior del marco

  // Validamos y obtenemos un usuario para la sesion actual
  while(!this->validateUser())
  {
    cout<<"\tIngrese un usuario para esta sesion:\t";
    cin>>this->user;
  }

  cout<<"\tHola "<<this->user<<" para mas ayuda escribe \\help"<<endl;
  artist.drawBottom(1);  // Dibujamos la parte inferior del marco
  this->interpreter();  // Pasamos al interprete de comandos
}
