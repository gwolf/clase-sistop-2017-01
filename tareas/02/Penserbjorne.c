/**
*   Autor: Paul Aguilar a.k.a Penserbjorne
*   Tarea: Administracion de procesos: Ejercicios de sincronizacion
*   Ejercicio: "El elevador"
*   Planteamiento:
*       El elevador de la facultad se descompone demasiado, porque sus usuarios
*           no respetan los limites.
*       -Implementa el elevador como un hilo, y a cada persona que quiere usarlo
*   como otro hilo.
*       -El elevador de la Facultad Ingenieria da servicio a cinco pisos.
*       --Un usuario puede llamarlo en cualquiera de ellos.
*       --Puede querer ir a cualquiera otro de ellos.
*       -El elevador tiene capacidad para cinco pasajeros (los pasajeros
*        tienen peso constante).
*       -Para ir del piso "x" al "y", el elevador tiene que cruzar todos los
*        pisos intermedios.
*       -Los usuarios prefieren esperar dentro del elevador que fuera de el.
*       --Si el elevador va subiendo y pasa por el piso "x", donde esta "A"
*           esperando para bajar, A aborda al elevador (no espera a que vaya
*           en la direccion correcta).
*   Refinamiento:
*       ¿Como puedes asegurarte de que una serie de alumnos que van entre dos
*           pisos no van a monopolizar al elevador ante otro usuario que va
*           para otro piso?
**/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MaxPersonasElevador 5
#define MaxPersonasEsperando 10
#define SegundosEntrePisos 2.0
#define MaxPisos 5
#define TiempoParaCrearPersonas 6.0

//  Estructura que simula al elevador
struct elevador_s{
    int sube;   // sube = 1 -> El elevador esta en ascenso
                // sube = 0 -> el elevador esta en descenso
    int pisoActual;
    int pisoTope;
    int personasEnElevador;
};

//  Estructura para enviar los parametros de los pisos a mover por persona en el elevador
struct arg_pisos{
    int origen;
    int destino;
};

//  Definicion de variables
pthread_mutex_t llave;
pthread_t elevador; //  Hilo para el elevador
pthread_t creadorDePersonas;    // Hilo para estar creando personas que piden el elevador
struct arg_pisos colaElevador[MaxPersonasElevador];  // Aqui se lleva el control de quienes estan dentro del elevador
struct arg_pisos colaEspera[MaxPersonasEsperando];    // Aqui se lleva el control de las personas que estan esperando y solicitaron elevador
int personasEnEspera;   // Contador de cuantas personas hay en espera para subir al elevador


//  Prototipo de funciones
void* controlDeElevador();
void* creadorDePersonas_Dios();
void* irDeXaYenElevador(void *param_pisos);

int main(void)
{
    int err;    // Bandera para errores al crear los hilos
    personasEnEspera = 0;

    //  Inicializando la llave de Mutex
    if(pthread_mutex_init(&llave, NULL) != 0){
        printf("La inicializacion de mutex ha fallado :(\n");
        return 1;
    }

    //Inicializando hilo del elevador
    err =  pthread_create(&elevador, NULL, &controlDeElevador, NULL);
    if(err != 0){
        printf("Error al crear el hilo del elevador\n");
        printf("Error: %s\n",strerror(err));
        return -1;
    }

    //Inicializando hilo del elevador
    err =  pthread_create(&creadorDePersonas, NULL, &creadorDePersonas_Dios, NULL);
    if(err != 0){
        printf("Error al crear el hilo que crea personas\n(Dios? eres tu? o acaso es la vida misma que se rehusa a la creacion de vida artificial? D;)\n");
        printf("Error: %s\n",strerror(err));
        return -1;
    }

    if(!err){
        //Hechando a andar el elevador
        pthread_join(elevador, NULL);

        //Hechando a andar el creador de personas/vida
        pthread_join(creadorDePersonas, NULL);
    }

    //  Destruyendo la llave Mutex
    pthread_mutex_destroy(&llave);

    return 0;
}

void* controlDeElevador(){
    //  Variales de tiempo para controlar el intervalo de tiempo entre cada piso
    time_t tiempo_inicio, tiempo_fin;
    double tiempo_transcurrido;
    int i,j;

    //  El elevador!!!!!
    struct elevador_s elevador;

    // Configuramos el elevador
    elevador.sube = 0;   // Por default vamos a bajar, asumiendo que no tenemos a que subir y bloqueamos el elevador en la planta baja
    elevador.pisoActual = 0; // Consideraremos a la planta baja como el piso "0"
    elevador.pisoTope = 0;  // Por default el piso tope es la planta baja
    elevador.personasEnElevador = 0; // Al principio el elevador esta vacio

    // Arrancamos servicio!!! :D
    while(1){
        tiempo_transcurrido = 0;
        time(&tiempo_inicio);
        // Control del elevador inicio
        if(personasEnEspera > 0 || elevador.personasEnElevador > 0){
            // Determinamos a cual piso dirigirnos como tope
            if(elevador.personasEnElevador){ // Si hay personas en el elevador
                if(elevador.sube){  // Buscamos el piso mas grande al cual dirigirnos
                    pthread_mutex_lock(&llave);
                    for(i = 0; i < elevador.personasEnElevador; i++){
                        if(elevador.pisoTope < colaElevador[i].destino){
                            elevador.pisoTope = colaElevador[i].destino;
                        }
                    }
                    pthread_mutex_unlock(&llave);
                }else{  //  Buscamos el piso mas pequeño al cual dirigirnos
                    pthread_mutex_lock(&llave);
                    for(i = 0; i < elevador.personasEnElevador; i++){
                        if(elevador.pisoTope > colaElevador[i].destino){
                            elevador.pisoTope = colaElevador[i].destino;
                        }
                    }
                    pthread_mutex_unlock(&llave);
                }
            }else{  // Si no hay personas en el elevador
                if(elevador.sube){  // Buscamos el piso mas grande en el cual recoger a alguien
                    pthread_mutex_lock(&llave);
                    for(i = 0; i < personasEnEspera; i++){
                        if(elevador.pisoTope < colaEspera[i].origen){
                            elevador.pisoTope = colaEspera[i].origen;
                        }
                    }
                    pthread_mutex_unlock(&llave);
                }else{  //  Buscamos el piso mas pequeño en el cual recoger a alguien
                    pthread_mutex_lock(&llave);
                    for(i = 0; i < personasEnEspera; i++){
                        if(elevador.pisoTope < colaEspera[i].origen){
                            elevador.pisoTope = colaEspera[i].origen;
                        }
                    }
                    pthread_mutex_unlock(&llave);
                }
            }
            // Movemos al elevador
            if(elevador.sube){
                if(elevador.pisoActual == (MaxPisos-1) || elevador.pisoActual == elevador.pisoTope){
                    elevador.sube = 0;
                    elevador.pisoActual--;
                }else{
                    elevador.pisoActual++;
                }
            }else{
                if(elevador.pisoActual == 0 || elevador.pisoActual == elevador.pisoTope){
                    elevador.sube = 1;
                    elevador.pisoActual++;
                }else{
                    elevador.pisoActual--;
                }
            }
            //  Atendemos a la gente del piso en el que estamos
            pthread_mutex_lock(&llave); // No me odien por bloquear un segmento de codigo tan grande :( hare harakiri de ser necesario para defender mi honor :(
            for(i = 0; i < elevador.personasEnElevador; i++){
                // Dejamos que la gente que baja en este piso se baje :D
                if(colaElevador[i].destino == elevador.pisoActual){
                    printf("Baje en el piso %i, venia del piso %i\n",colaElevador[i].destino, colaElevador[i].origen);
                    for(j = i; j < (elevador.personasEnElevador-1); j++){
                        colaElevador[j].origen = colaElevador[j+1].origen;
                        colaElevador[j].destino = colaElevador[j+1].destino;
                    }
                    colaElevador[j].origen = colaElevador[j+1].origen;
                    colaElevador[j].destino = colaElevador[j+1].destino;
                    elevador.personasEnElevador--;
                }
            }
            // Si es posible, subimos gente al elevador
            for(i = 0;i < personasEnEspera && elevador.personasEnElevador < MaxPersonasElevador; i++){
                if(colaEspera[i].origen == elevador.pisoActual){
                    // Subimos a una persona en espera
                    colaElevador[elevador.personasEnElevador].origen = colaEspera[i].origen;
                    colaElevador[elevador.personasEnElevador].destino = colaEspera[i].destino;
                    printf("Subi en el piso %i, voy al piso %i\n",colaElevador[elevador.personasEnElevador].origen, colaElevador[elevador.personasEnElevador].destino);
                    elevador.personasEnElevador++;
                    for(j = i; j < (personasEnEspera-1); j++){
                        colaEspera[j].origen = colaEspera[j+1].origen;
                        colaEspera[j].destino = colaEspera[j+1].destino;
                    }
                    colaEspera[j].origen = colaEspera[j+1].origen;
                    colaEspera[j].destino = colaEspera[j+1].destino;
                    personasEnEspera--;
                }
            }
            pthread_mutex_unlock(&llave); // No me odien por bloquear un segmento de codigo tan grande :( hare harakiri de ser necesario para defender mi honor :(
        }else if(elevador.pisoActual > 0){  // Si no hay nadie esperando ni usando el elevador, nos vamos a la planta baja
            elevador.pisoActual--;
        }
        // Control del elevador fin

        while(tiempo_transcurrido < SegundosEntrePisos){    // Verificamos el tiempo transcurrido entre pisos
            time(&tiempo_fin);
            tiempo_transcurrido = difftime(tiempo_fin,tiempo_inicio);
        }
        printf("Elevador en piso %i\n",elevador.pisoActual);
        printf("Personas en el elevador: %i\n",elevador.personasEnElevador);
        printf("Personas en espera: %i\n\n",personasEnEspera);
    }
}

void* creadorDePersonas_Dios(){
    //  Variales de tiempo para controlar el intervalo de tiempo entre las llegadas de las personas
    time_t tiempo_inicio, tiempo_fin;
    double tiempo_transcurrido;
    int err;    // Bandera para errores al crear los hilos

    // Crearemos gente infinitamente
    while(1){
        tiempo_transcurrido = 0;
        time(&tiempo_inicio);
        while(tiempo_transcurrido <= TiempoParaCrearPersonas){
            time(&tiempo_fin);
            tiempo_transcurrido = difftime(tiempo_fin, tiempo_inicio);
        }   //  -> Si ya paso el tiempo transcurrido, procedemos a crear una persona >:D

        if(personasEnEspera < MaxPersonasEsperando){    // Si no hay muchas personas esperando
            pthread_t persona;
            struct arg_pisos pisos;

            srand(time(NULL));

            do{
                pisos.origen = rand() % MaxPersonasElevador;
                pisos.destino = rand() % MaxPersonasElevador;
            }while(pisos.origen == pisos.destino);  // Indicamos el piso de origen y el piso de destino

            // Creamos a la persona y la mandamos a que pida el elevador
            err = pthread_create(&persona, NULL, &irDeXaYenElevador, &pisos);
            if(err != 0){
                printf("Error al crear al hilo que persona que solicita el elevador D;\n(Dios? eres tu? o acaso es la vida misma que se rehusa a la creacion de vida artificial? D;)\n");
                printf("Error: %s\n",strerror(err));
            }else{
                pthread_join(persona, NULL);
            }
        }else{
            printf("Ya hay demasiadas personas esperando ... usare las escaleras :( <'3\n");
        }

    }
}

void* irDeXaYenElevador(void *param_pisos){
    struct arg_pisos *pisos = param_pisos;
    printf("Hola, soy alguien de la facultad y quiero ir del piso %i al %i.\n",pisos->origen,pisos->destino);
    if(personasEnEspera < MaxPersonasEsperando){
        pthread_mutex_lock(&llave);     //  Bloqueamos recursos
        colaEspera[personasEnEspera].origen = pisos->origen;
        colaEspera[personasEnEspera].destino = pisos->destino;
        personasEnEspera++;
        pthread_mutex_unlock(&llave);
    }
}
