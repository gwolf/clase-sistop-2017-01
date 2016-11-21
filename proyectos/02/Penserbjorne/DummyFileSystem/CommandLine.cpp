/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase que servira como un pequeño interprete de comandos para el sistema
*/

#include "CommandLine.h"
#include "Colors.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <fstream>

using namespace std;

enum commands{
  NO_COMMAND = -1,
  ABOUT,
  EXIT,
  HELP,
  USAGE
};

CommandLine::CommandLine(){
    //ctor
    string header = "art_dfs_header.txt";
    string optionalHeader = "\t\t\t--------Dummy File System--------\n";
    optionalHeader += "\t\t\t---------by Penserbjorne---------\n\n";

    this->user = "";
    this->artist.drawTop(1);
    this->artist.drawHeader(header,optionalHeader);
    this->artist.drawBottom(1);
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
  msg = this->colors.FRED("\tError:\t") + msg + "\n";
  cout<<msg;
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

// Muestra la informacion de un commando generico
void CommandLine::genericCommand(string header, string optionalHeader,string fileContent){
  // Dibujamos el header
  this->artist.drawHeader(header,optionalHeader);
  // Cargamos el archivo para imprimirlo
  string line;
  ifstream file(fileContent.c_str());
  // Abrimos el archivo
  if(file){
      // Imprimimos el archivo
      while(getline(file,line)){
          //colors.FRED(line);
          cout<<line<<endl;
      }
  }else{  // En caso de no poder abrir el archivo mandamos un mensaje
      cout<<endl;
      this->msgError("No fue posible cargar el archivo. Contacte a su proveedor.");
  }
}

// Obtiene el comando introducido y lo ejecuta
int CommandLine::getAndExecCommand(string command){
  string commandEval;  // Aqui guardaremos el comando
  string commandEvalOriginal;
  string delimiter = " "; // Los comandos se separan por espacios
  size_t pos = 0;

  // Obtenemos el comando enviado
  commandEval = command.substr(pos, command.find(delimiter));
  commandEvalOriginal = commandEval;

  // Lo convertimos a minusculas
  transform(commandEval.begin(), commandEval.end(), commandEval.begin(), ::tolower);

  if(commandEval == "about"){
    string header = "art_dfs_header.txt";
    string optionalHeader = "\t\t\t--------Dummy File System--------\n";
          optionalHeader += "\t\t\t----------Acerca de DFS----------\n\n";
    string fileContent = "info_about.txt";
    this->genericCommand(header, optionalHeader,fileContent);
    return USAGE;
  }else if(commandEval == "exit"){
    return EXIT;
  }else if(commandEval == "help"){
    string header = "art_dfs_help.txt";
    string optionalHeader = "\t\t\t--------Dummy File System--------\n";
          optionalHeader += "\t\t\t--------------Ayuda--------------\n\n";
    string fileContent = "info_help.txt";
    this->genericCommand(header, optionalHeader,fileContent);
    return HELP;
  }else if(commandEval == "usage"){
    string header = "art_dfs_usage.txt";
    string optionalHeader = "\t\t\t--------Dummy File System--------\n";
          optionalHeader += "\t\t\t----------Manual de Uso----------\n\n";
    string fileContent = "info_usage.txt";
    this->genericCommand(header, optionalHeader,fileContent);
    return USAGE;
  }else{
    this->msgError(colors.BGRN(commandEvalOriginal) + " no es un comando.");
    return NO_COMMAND;
  }
}

// Interprete de comandos
void CommandLine::interpreter(){
  int currentLine = 1;
  string userOutput;  // Contador de line y usuario
  string command; // Comando que se ejecutara
  int intCommand; // Valor entero equivalente al comando

  cleanBuffer();
  do{
    this->artist.drawTop(1);
    userOutput = "\t" + to_string(currentLine) + " @ " + this->user + " > ";
    cout<<this->colors.FBLU(userOutput);
    getline(cin, command);
    intCommand = getAndExecCommand(command);
    this->artist.drawBottom(1);
    currentLine++;
  }while (intCommand != EXIT);
}

// Punto de acceso al programa
void CommandLine::run(){
  this->artist.drawTop(1);  // Dibujamos la parte superior del marco

  // Validamos y obtenemos un usuario para la sesion actual
  while(!this->validateUser())
  {
    cout<<"\tIngrese un usuario para esta sesion:\t";
    cin>>this->user;
  }

  cout<<"\tHola "<<this->colors.FBLU(this->user)<<" para mas ayuda escribe "<<this->colors.BGRN("\"help\"")<<endl;
  this->artist.drawBottom(1);  // Dibujamos la parte inferior del marco
  this->interpreter();  // Pasamos al interprete de comandos
}
