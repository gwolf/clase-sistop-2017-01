/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase para dibujar cosas del sistema
*/

#include "Draw.h"
#include "Colors.h"
#include <iostream>
#include <fstream>
#include <string>

// Referencia https://en.wikipedia.org/wiki/Box-drawing_character#Unicode
// Referencia http://patorjk.com/software/taag/#p=display&f=Slant&t=Dummy%20File%0ASystem
#define FRAME_WIDTH 80
#define FRAME_LINE "\u2550"
#define FRAME_TOP_LEFT "\u2554"
#define FRAME_TOP_RIGHT "\u2557"
#define FRAME_BOTTOM_LEFT "\u255A"
#define FRAME_BOTTOM_RIGHT "\u255D"

using namespace std;

Draw::Draw()
{
    //ctor
}

Draw::~Draw()
{
    //dtor
}

// Funcion para diujar el titulo del sistema
void Draw::drawHeader(string header, string optionalHeader){
    // Cargamos el header para imprimirlo
    string line;
    ifstream fheader(header.c_str());
    // Abrimos el header
    if(fheader){
        // Imprimimos el header
        while(getline(fheader,line)){
            cout<<colors.FRED(line)<<endl;
        }
    }else{  // En caso de no poder abrir el archivo imprimimos a secas
        cout<<colors.FRED(optionalHeader);
    }
}

// Funcion para la parte superior del marco
void Draw::drawTop(int divideBy){
  short int i;
  // Calculamos el tamaño del marco
  short int width = FRAME_WIDTH / divideBy;

  // Imprimimos la parte del marco
  cout<<FRAME_TOP_LEFT;
  for( i = 0; i < width; i++){
    cout<<FRAME_LINE;
  }
  cout<<FRAME_TOP_RIGHT<<endl;
}

// Funcion para la parte inferior del marco
void Draw::drawBottom(int divideBy){
  short int i;
  // Calculamos el tamaño del marco
  short int width = FRAME_WIDTH / divideBy;

  // Imprimimos la parte del marco
  cout<<FRAME_BOTTOM_LEFT;
  for( i = 0; i < width; i++){
    cout<<FRAME_LINE;
  }
  cout<<FRAME_BOTTOM_RIGHT<<endl;
}
