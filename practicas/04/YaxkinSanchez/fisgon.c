#include <stdio.h>
#include <stdlib.h>

int main () {
	int *datos;
	int i;
	datos = malloc(16 * sizeof(int));
	printf("Tamaño de datos: %d\n",sizeof(datos));
	printf("Tamaño de int: %d\n",sizeof(int));
	printf("Tamaño de long: %d\n",sizeof(long));
	printf("Tamaño de float: %d\n",sizeof(float));
	printf("Tamaño de char: %d\n",sizeof(char));
	printf("Tamaño de short: %d\n",sizeof(short));
	printf("Tamaño de double: %d\n",sizeof(double));
	for (i=0; i<65535; i++)
		printf("La palabra #%d es: %x\n", i, datos[i]);
	free(datos);
	return 0;
}

