/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase que servira como un pequeño interprete de comandos para el sistema
*/

#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include "Draw.h"

class CommandLine
{
    public:
        CommandLine();
        virtual ~CommandLine();
        void run();
    protected:
    private:
      Draw artist;
};

#endif // COMMANDLINE_H
