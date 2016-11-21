/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase para poner colores en la consola
*/

#ifndef COLORS_H
#define COLORS_H

#include <string>

using namespace std;
class Colors
{
    public:
        Colors();
        virtual ~Colors();

        // Texto
        void FRED(string text);
        void FGRN(string text);
        void FYEL(string text);
        void FBLU(string text);
        void FMAG(string text);
        void FCYN(string text);
        void FWHT(string text);

        // Fondo
        void BRED(string text);
        void BGRN(string text);
        void BYEL(string text);
        void BBLU(string text);
        void BMAG(string text);
        void BCYN(string text);
        void BWHT(string text);

        // Otros
        void FBOLD(string text);
        void FUNDL(string text);
        void FBLINK(string text);
        void FHIDDEN(string text);
    protected:
    private:
};

#endif // COLORS_H
