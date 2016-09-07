/**
*   Autor: Paul Aguilar a.k.a Penserbjorne
*   Descripcion:    Este programa ejemplifica el uso de hilos sin mutex y con
*                   mutex
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>>
#define MaxHilos 5
#define TopeRecursoCompartido 5

//  Definicion de variables
pthread_t hilosSinMutex[MaxHilos];
pthread_t hilosConMutex[MaxHilos];
pthread_mutex_t llave;
int recursoCompartido;

//  Prototipo de funciones
void* incrementarRecursoCompartidoSinMutex();
void* incrementarRecursoCompartidoConMutex();

int main(void)
{
    int err;
    int i;

    printf("--Hilos sin Mutex\n");

    // Inicializamos Hilos sin Mutex
    for(i = 0; i < MaxHilos; i++){
        err = pthread_create(&(hilosSinMutex[i]), NULL, &incrementarRecursoCompartidoSinMutex, NULL);
        if(err != 0){
            printf("Error al crear el hilo sin mutex %i\n",i);
            printf("Error:  %s\n",strerror(err));
        }
    }

    //  Arrancando Hilos sin Mutex
    for(i = 0; i < MaxHilos; i++){
        pthread_join(hilosSinMutex[i], NULL);
    }

    printf("--Hilos con Mutex\n");

    //  Inicializando la llave de Mutex
    if(pthread_mutex_init(&llave, NULL) != 0){
        printf("La inicializacion de mutex ha fallado :(\n");
        return 1;
    }

    //  Inicializando Hilos con Mutex
    for(i = 0; i < MaxHilos; i++){
        int j = i;
        err = pthread_create(&(hilosConMutex[i]), NULL, &incrementarRecursoCompartidoConMutex, NULL);
        if(err != 0){
            printf("Error al crear el hilo con mutex %i\n",i);
            printf("Error:  %s\n",strerror(err));
        }
    }

    //  Arrancando Hilos con Mutex
    for(i = 0; i < MaxHilos; i++){
        pthread_join(hilosConMutex[i],NULL);
    }

    //  Destruyendo la llave de Mutex
    pthread_mutex_destroy(&llave);

    return 0;
}

void* incrementarRecursoCompartidoSinMutex(){
    //  Este ciclo es una seccion critica sin proteger
    for(recursoCompartido = 0; recursoCompartido < TopeRecursoCompartido; recursoCompartido++){
        printf("Hilo Sin Mutex %u -- Recurso Compartido %i\n", pthread_self(), recursoCompartido);
    }
    return NULL;
}

void* incrementarRecursoCompartidoConMutex(){
    pthread_mutex_lock(&llave);     //  Bloqueamos el recurso con la llave mutex
    // Aqui nuestro codigo se vuelve una seccion critica protegida
    for(recursoCompartido = 0; recursoCompartido < TopeRecursoCompartido; recursoCompartido++){
        printf("Hilo Con Mutex %u -- Recurso Compartido %i\n", pthread_self(), recursoCompartido);
    }
    pthread_mutex_unlock(&llave);   //  Desbloqueamos el recurso con la llave mutex
    return NULL;
}
