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
        string FRED(string text);
        string FGRN(string text);
        string FYEL(string text);
        string FBLU(string text);
        string FMAG(string text);
        string FCYN(string text);
        string FWHT(string text);

        // Fondo
        string BRED(string text);
        string BGRN(string text);
        string BYEL(string text);
        string BBLU(string text);
        string BMAG(string text);
        string BCYN(string text);
        string BWHT(string text);

        // Otros
        string FBOLD(string text);
        string FUNDL(string text);
        string FBLINK(string text);
        string FHIDDEN(string text);
    protected:
    private:
};

#endif // COLORS_H
