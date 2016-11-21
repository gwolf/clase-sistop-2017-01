/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase para dibujar cosas del sistema
*/

#ifndef DRAW_H
#define DRAW_H


class Draw
{
    public:
        Draw();
        virtual ~Draw();

        // Funcion para diujar el titulo del sistema
        void drawDFS();
        // Funcion para la parte superior del marco
        void drawTop(int divideBy);
        // Funcion para la parte inferior del marco
        void drawBottom(int divideBy);
    protected:
    private:
};

#endif // DRAW_H
