#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#define NUM_THREADS     5

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Este es el hilo >> #%ld!\n", tid);
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=0; t<NUM_THREADS; t++){
      printf("En main: creando el hilo >> %ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (rc){
         printf("ERROR; codigo de error regresado por pthread_create() es %d\n", rc);
         exit(-1);
      }
   }
   pthread_exit(NULL);
}