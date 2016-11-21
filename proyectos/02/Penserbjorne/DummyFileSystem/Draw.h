/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase para dibujar cosas del sistema
*/

#ifndef DRAW_H
#define DRAW_H

#include "Colors.h"
#include <string>

using namespace std;

class Draw
{
    public:
        Draw();
        virtual ~Draw();

        // Funcion para diujar el titulo del sistema
        void drawHeader(string header, string optionalHeader);
        // Funcion para la parte superior del marco
        void drawTop(int divideBy);
        // Funcion para la parte inferior del marco
        void drawBottom(int divideBy);
    protected:
    private:
      Colors colors;
};

#endif // DRAW_H
