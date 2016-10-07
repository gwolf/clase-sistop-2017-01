#include <stdio.h>
#include <stdlib.h>

int main ()
{
 int primer_num, segundo_num, suma, resta, multiplicacion;
 printf("Calculadora que resuelve tres operaciones al mismo tiempo :)\n\n");
 printf("Dame un numero: ");
 scanf ("%i",&primer_num);
 printf("Dame otro numero: ");
 scanf ("%i",&segundo_num);
 suma = primer_num + segundo_num;
 resta = primer_num - segundo_num;
 multiplicacion = primer_num * segundo_num;
 
 printf("Los resultados son: \n SUMA = %i \n RESTA = %i \n MULTIPLICACION = %i\n\n",suma, resta, multiplicacion);
 
 return (0);
}

