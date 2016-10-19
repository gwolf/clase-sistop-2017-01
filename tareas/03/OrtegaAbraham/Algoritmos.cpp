/*
Este programa "simula" los algoritmos de planificación más sencillos ( lo se me comió el tiempo :c)
Funciona a partir de un vector generado con 9 números aleatorios, ya que el primero debe ser 0 siempre.
Favor de compilar utilizando g++ -std=c++11
Hecho por Ortega Gonzalez Luis Abraham

*/
#include <iostream>
#include <vector>
#include <random>
#include "fcfs.h"
#include "roundr.h"
#include "snp.h"
int main(int argc, char **argv)
{
using namespace std;
//vector <float> pro {0,3,1,5,3,2,9,5,12,5};
vector <float> pro {0};
int i=0;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 5);// es tes un rango seguro, si se aumenta cosas raras comienzan a pasar.prueblo para segmentation core

for(i=0;i<9;i++)
{
pro.push_back(dis(gen));
}


fcfs fifo(&pro);//creacion del fcfs
cout<<"FCFS"<<endl<<endl;
fifo.fifo();//implementacion de fcfs
cout<<endl;
cout<<endl;
cout<<"Round Robin"<<endl<<endl;
roundR ronda(&pro);//creacion Round Robin
ronda.round();//implementacion de la ronda
cout<<endl;
cout<<endl;
cout<<"SPN"<<endl<<endl;
snP cortin(&pro);//creccion de SPN
cortin.shortP();//implementacion SPN

}