#include <stdio.h>
#include <stdlib.h>

int main () {
  int *datos;
  int i;
  datos = malloc(16 * sizeof(double));
  for (i=0; i<65536; i++){
    printf("%d\n",(int)sizeof(double) );
    //printf("La palabra #%d es: %d\n", i, datos[i]);
	}
  free(datos);
  return 0;
}