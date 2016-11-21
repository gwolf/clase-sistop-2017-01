/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase para dibujar cosas del sistema
*/

#include "Draw.h"
#include <iostream>
#include <fstream>
#include <string>

#define FRAME_WIDTH 78
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
void Draw::drawDFS(){
    // Cargamos el header para imprimirlo
    string header_dir = "art_dfs_header.txt";
    string line;
    ifstream header(header_dir.c_str());
    // Abrimos el header
    if(header){
        // Imprimimos el header
        while(getline(header,line)){
            cout<<line<<endl;
        }
    }else{  // En caso de no poder abrir el archivo imprimimos a secas
        cout<<"\t----------Dummy File System----------\n";
        cout<<"\t-----------by Penserbjorne-----------\n\n";
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
