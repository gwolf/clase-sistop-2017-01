/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase que servira como un pequeño interprete de comandos para el sistema
*/

#include "CommandLine.h"
#include <iostream>

using namespace std;

CommandLine::CommandLine()
{
    //ctor
}

CommandLine::~CommandLine()
{
    //dtor
}

void CommandLine::run(){
  artist.drawTop(1);
  artist.drawDFS(1);
  artist.drawBottom();
}
