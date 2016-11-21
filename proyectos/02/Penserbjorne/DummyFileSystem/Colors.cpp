/*
*   Autor: Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne
*   Descripcion: Clase para poner colores en la consola
*/

//Original code from - http://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
// Extended by Penserbjorne using http://misc.flogisoft.com/bash/tip_colors_and_formatting

#include "Colors.h"
#include <iostream>
#include <string>

using namespace std;

// Texto
#define RST  "\x1B[0m"
#define KBLK  "\x1B[31m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

// Fondo
#define BRST  "\x1B[49m"
#define KBBLK  "\x1B[40m"
#define KBRED  "\x1B[41m"
#define KBGRN  "\x1B[42m"
#define KBYEL  "\x1B[43m"
#define KBBLU  "\x1B[44m"
#define KBMAG  "\x1B[45m"
#define KBCYN  "\x1B[46m"
#define KBWHT  "\x1B[47m"

// Otros
#define BOLD "\x1B[1m"
#define UNDL "\x1B[4m"
#define BLINK "\x1B[5m"
#define HIDDEN "\x1B[8m"

using namespace std;

Colors::Colors()
{
    //ctor
}

Colors::~Colors()
{
    //dtor
}

void Colors::FRED(string text){
  cout<<KRED<<text<<RST;
}

void Colors::FGRN(string text){
  cout<<KGRN<<text<<RST;
}

void Colors::FYEL(string text){
  cout<<KYEL<<text<<RST;
}

void Colors::FBLU(string text){
  cout<<KBLU<<text<<RST;
}

void Colors::FMAG(string text){
  cout<<KMAG<<text<<RST;
}

void Colors::FCYN(string text){
  cout<<KCYN<<text<<RST;
}

void Colors::FWHT(string text){
  cout<<KWHT<<text<<RST;
}

// Fondo
void Colors::BRED(string text){
  cout<<KBRED<<text<<RST;
}

void Colors::BGRN(string text){
  cout<<KBGRN<<text<<RST;
}

void Colors::BYEL(string text){
  cout<<KBYEL<<text<<RST;
}

void Colors::BBLU(string text){
  cout<<KBBLU<<text<<RST;
}

void Colors::BMAG(string text){
  cout<<KBMAG<<text<<RST;
}

void Colors::BCYN(string text){
  cout<<KBCYN<<text<<RST;
}

void Colors::BWHT(string text){
  cout<<KBWHT<<text<<RST;
}

// Otros
void Colors::FBOLD(string text){
  cout<<BOLD<<text<<RST;
}

void Colors::FUNDL(string text){
  cout<<UNDL<<text<<RST;
}

void Colors::FBLINK(string text){
  cout<<BLINK<<text<<RST;
}

void Colors::FHIDDEN(string text){
  cout<<HIDDEN<<text<<RST;
}
