#include <stdio.h> 
#include <pthread.h>

int argext[2]={2,3};

int main () 
{ 
pthread_t tid;

void *mifuncion(void *arg);

printf("Creando hilo...\n"); 
fflush(stdout); 
 

pthread_create(&tid, NULL, mifuncion, (void *) NULL);

printf("Hilo creado. Esperando su finalizacion...\n"); 
fflush(stdout);

pthread_join(tid, NULL);

printf("Hilo finalizado...\n"); 
fflush(stdout);

}

void *mifuncion(void *arg) 
{

printf("Soy mifuncion...\n");

printf("Arg. ext. 1: %d. Arg. ext. 2: %d\n", argext[0], argext[1]);

printf("Trato de modificar los argumentos...\n");

argext[0] = 7; 
argext[1] = 8;

printf("Arg. ext. 1: %d. Arg. ext. 2: %d\n", argext[0], argext[1]);

printf("Saliendo de mifuncion...\n"); 
fflush(stdout);

pthread_exit(NULL);

}
