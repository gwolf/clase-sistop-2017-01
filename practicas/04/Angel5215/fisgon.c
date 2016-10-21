
#include <stdio.h>
#include <stdlib.h>

int main()
{
	double *datos;
	int i;

	datos = malloc(16 * sizeof(double));

	for (i = 16; i >= -1000000; i--)
	{
		printf("La palabra #%d es: %.3f\n", i, datos[i]);
	}

	free(datos);
	return 0;
}