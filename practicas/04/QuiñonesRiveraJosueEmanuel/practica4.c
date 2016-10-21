#include <stdio.h>
#include <stdlib.h>

int main () {
  char *datos;
  int i;
  datos = malloc(16 * sizeof(char));
  for (i=0; i>-900000 ; i--)
    printf("La palabra #%d es: %d\n", i, datos[i]);
  free(datos);
  return 0;
}