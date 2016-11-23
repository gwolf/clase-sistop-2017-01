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

string Colors::FRED(string text){
  return text = KRED + text + RST;
}

string Colors::FGRN(string text){
  return text = KGRN + text + RST;
}

string Colors::FYEL(string text){
  return text = KYEL + text + RST;
}

string Colors::FBLU(string text){
  return text = KBLU + text + RST;
}

string Colors::FMAG(string text){
  return text = KMAG + text + RST;
}

string Colors::FCYN(string text){
  return text = KCYN + text + RST;
}

string Colors::FWHT(string text){
  return text = KWHT + text + RST;
}

// Fondo
string Colors::BRED(string text){
  return text = KBRED + text + RST;
}

string Colors::BGRN(string text){
  return text = KBGRN + text + RST;
}

string Colors::BYEL(string text){
  return text = KBYEL + text + RST;
}

string Colors::BBLU(string text){
  return text = KBBLU + text + RST;
}

string Colors::BMAG(string text){
  return text = KBMAG + text + RST;
}

string Colors::BCYN(string text){
  return text = KBCYN + text + RST;
}

string Colors::BWHT(string text){
  return text = KBWHT + text + RST;
}

// Otros
string Colors::FBOLD(string text){
  return text = BOLD + text + RST;
}

string Colors::FUNDL(string text){
  return text = UNDL + text + RST;
}

string Colors::FBLINK(string text){
  return text = BLINK + text + RST;
}

string Colors::FHIDDEN(string text){
  return text = HIDDEN + text + RST;
}
