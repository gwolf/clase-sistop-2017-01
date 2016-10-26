Práctica 4

Sistema operativo: Ubuntu 16.04.1 LTS

Compilador: gcc versión 5.3.1 20160406 

Biblioteca de c:(GNU libc) 2.22

Iteraciones con tipo INT:33788

Iteraciones con tipo LONG:16894

Iteraciones con tipo DOUBLE:16894

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
char-8 bits
int-16 bits
long int-32 bits
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

int main () {
  char *datos;
  int i;
  datos = malloc(16 * sizeof(char));
  //datos = malloc(16 * sizeof(int));
  //datos = malloc(16 * sizeof(long int));
 for (i=0; i>-100000 ; i--)
    printf("La palabra #%d es: %d\n", i, datos[i]);
  free(datos);
  return 0;
}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
En este caso queria probarlo en los diferentes SO que tengo pero a falta de tiempo lo dejare en uno.Esperaba un resultado un poco mas predecible pero no fue asi todos los valores si daban cero al ejecutarlo varias veces a veces si salia diferente aparecieron datos con valor,creo que se debe al uso de ubuntu. Dependiendo del tipo de dato era las interecciones eso debe a que no es lo mismo un char un long int. Recuerdo que una vez jugando con malloc entre a memoria que no debia y termine reiniciando mi equipo.
---------------------------------------------------------------------------------------------------------------------------------------------------------------------

