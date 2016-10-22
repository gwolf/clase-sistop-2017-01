/**
*   Autor: Paul Aguilar a.k.a Penserbjorne
*   Tarea: Administracion de procesos: Algoritmos de planificacion
*   Algoritmo implementados: FCFS
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#define nProcesos 5
#define MaxTiempoProcesoDuracion 10
#define MaxTiempoProcesoInicio 10
#define TiempoEntreProcesos 0.5

//  Estructura que simula ser un proceso
struct proceso{
    char nombre;
    short int t;    //  Tiempo que tarda en ejecutarse el proceso
    short int inicio;
    short int tiempo_transcurrido;
    short int fin;
    float T;    //  Tiempo de respuesta
    float E;    // Tiempo en espera
    float P;    //  Proporcion de penalizacion
    float R;    //  Proporcion de respuesta
};

//  Lista procesos a trabajar
struct proceso procesos[nProcesos];
struct proceso procesosFCFS[nProcesos];

char* s_FCFS;  //  Resultado de como se corrieron los procesos
char verSimulacion;

void imprimirProcesos();
void* FCFS();
void resultadosFCFS();

int main()
{
    int i;

    srand(time(NULL));

    s_FCFS = (char*) malloc(sizeof(char));
    //  Inicializamos "aleatoriamente" los valores para cada proceso

    //  Primer proceso
    procesos[0].nombre = 'A';
    procesos[0].inicio = (rand()%MaxTiempoProcesoInicio)+1;
    procesos[0].t = (rand()%MaxTiempoProcesoDuracion)+1;
    procesos[0].tiempo_transcurrido = 0;
    //  Resto de procesos
    for(i = 1; i < nProcesos; i++){
        procesos[i].nombre = i + 65;
        procesos[i].inicio = (rand() % MaxTiempoProcesoInicio) + procesos[i-1].inicio;
        procesos[i].t = (rand() % MaxTiempoProcesoDuracion)+1;
        procesos[i].tiempo_transcurrido = 0;
    }

    // Copiamos los procesos a sus respectivas colas
    for(i = 0; i < nProcesos; i++){
        procesosFCFS[i].nombre = procesos[i].nombre;
        procesosFCFS[i].inicio = procesos[i].inicio;
        procesosFCFS[i].t = procesos[i].t;
        procesosFCFS[i].tiempo_transcurrido = procesos[i].tiempo_transcurrido;
    }

    printf("Desea ver \"simulados\" los procesamientos de las colas? [y\\n]: ");
    scanf("%c",&verSimulacion);
    //while(getchar() != '\n');

    // Procesamos la cola de procesos
    FCFS();

    imprimirProcesos();
    resultadosFCFS();
    return 0;
}

void imprimirProcesos(){
    system(CLEAR);
    int i;

    // Imprimimos los procesos a trabajar
    printf("---Procesos a tratar---\n\n");
    for(i = 0; i < nProcesos; i++){
        printf("Proceso:%c\tLlegada:%i\tTiempo:%i\n",procesos[i].nombre,procesos[i].inicio, procesos[i].t);
    }
}

void* FCFS(){
    int i;  // Contador temporal
    int tiempo_transcurrido;    // Tiempo transcurrido desde que comenzo este hilo
    time_t tiempo_actual;
    time_t tiempo_referencia;
    float diferencia_tiempo;    // Tiempo transcurrido entre quantums

    // Simulamos los quantums haciendo una diferencia de tiempo
    tiempo_transcurrido = 0;
    time(&tiempo_referencia);
    i = 0;
    while(i < nProcesos){
        // Obtenemos el tiempo actual y calculamos la diferencia de tiempo para ver si hicimos un quantum
        time(&tiempo_actual);
        diferencia_tiempo = difftime(tiempo_actual, tiempo_referencia);
        // HUBO UN QUANTUM!
        if(diferencia_tiempo >= TiempoEntreProcesos || (verSimulacion != 'y' && verSimulacion != 'Y')){
            // Actualizamos las referencias de tiempo para el quantum
            time(&tiempo_referencia);
            diferencia_tiempo = 0.0;

            //  El proceso actual esta en el tiempo que le corresponde ser atendido
            if(tiempo_transcurrido >= procesosFCFS[i].inicio){
                strcat(s_FCFS,&procesosFCFS[i].nombre);
                procesosFCFS[i].tiempo_transcurrido++;
            }else{
                strcat(s_FCFS,"-");
            }

            imprimirProcesos();
            printf("\n\n---Procesando con FCFS---\n\n");
            printf("t = %i\t%s\n",tiempo_transcurrido,s_FCFS);

            //  Indicamos que ya paso un quantum
            tiempo_transcurrido++;

            //  Si el tiempo que ha estado el proceso en memoria es igual al tiempo que se supone debe estar
            //  significa que ya ha estado el tiempo que debe estar y debemos procesar sus demas datos
            if(procesosFCFS[i].tiempo_transcurrido == procesosFCFS[i].t){
                procesosFCFS[i].fin = tiempo_transcurrido;
                procesosFCFS[i].T = procesosFCFS[i].fin - procesosFCFS[i].inicio;
                procesosFCFS[i].E = procesosFCFS[i].T - procesosFCFS[i].t;
                procesosFCFS[i].P = procesosFCFS[i].T / (float)procesosFCFS[i].t;
                procesosFCFS[i].R = (float)procesosFCFS[i].t / procesosFCFS[i].T;
                i++;
            }
        }
    }
}

void resultadosFCFS(){
    int i;
    struct proceso promedio;
    promedio.T = 0.0;
    promedio.E = 0.0;
    promedio.P = 0.0;
    promedio.R = 0.0;

    printf("\n\n---Resultados de FCFS---\n\n");
    printf("Proceso\tInicio\tFin\tt\tT\tE\tP\tR\n");
    printf("----------------------------------------------------------------\n");
    for( i = 0; i < nProcesos; i++){
        printf("%c\t%i\t%i\t%i\t%.2f\t%.2f\t%.2f\t%.2f\n",procesosFCFS[i].nombre,procesosFCFS[i].inicio,procesosFCFS[i].fin,procesosFCFS[i].t,procesosFCFS[i].T,procesosFCFS[i].E,procesosFCFS[i].P,procesosFCFS[i].R);
        promedio.T += procesosFCFS[i].T;
        promedio.E += procesosFCFS[i].E;
        promedio.P += procesosFCFS[i].P;
        promedio.R += procesosFCFS[i].R;
    }
    promedio.T /= (float)nProcesos;
    promedio.E /= (float)nProcesos;
    promedio.P /= (float)nProcesos;
    promedio.R /= (float)nProcesos;
    printf("----------------------------------------------------------------\n");
    printf("Prom\t \t \t \t%.2f\t%.2f\t%.2f\t%.2f\n\n",promedio.T,promedio.E,promedio.P,promedio.R);
    printf("Orden: %s\n",s_FCFS);
}
