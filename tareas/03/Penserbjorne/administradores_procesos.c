/**
*   Autor: Paul Aguilar a.k.a Penserbjorne
*   Tarea: Administracion de procesos: Algoritmos de planificacion
*   Algoritmo implementados: FCFS, RR
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
#define TiempoEntreProcesos 1.0
#define TamBuffer 1024

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
struct proceso procesosRR[nProcesos];

  //  Resultado de como se corrieron los procesos por cada algoritmo
char* s_FCFS;
char s_RR[TamBuffer];
char verSimulacion;

void imprimirProcesos();
void FCFS();
void resultadosFCFS();
int RR();
void resultadosRR(int q);

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

        procesosRR[i].nombre = procesos[i].nombre;
        procesosRR[i].inicio = procesos[i].inicio;
        procesosRR[i].t = procesos[i].t;
        procesosRR[i].tiempo_transcurrido = procesos[i].tiempo_transcurrido;
    }

    printf("Desea ver \"simulados\" los procesamientos de las colas? [y\\n]: ");
    scanf("%c",&verSimulacion);

    // Procesamos la cola de procesos
    FCFS();
    int q;  //quantum!!!
    q = RR();

    imprimirProcesos();
    resultadosFCFS();
    resultadosRR(q);
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

void FCFS(){
    int i;  // Contador temporal
    int tiempo_transcurrido;    // Tiempo transcurrido desde que comenzo este hilo
    time_t tiempo_actual;
    time_t tiempo_referencia;
    float diferencia_tiempo;    // Tiempo transcurrido en ticks

    // Simulamos los ticks haciendo una diferencia de tiempo
    tiempo_transcurrido = 0;
    time(&tiempo_referencia);
    i = 0;
    while(i < nProcesos){
        // Obtenemos el tiempo actual y calculamos la diferencia de tiempo para ver si hicimos un tick
        time(&tiempo_actual);
        diferencia_tiempo = difftime(tiempo_actual, tiempo_referencia);
        // HUBO UN TICK!
        if(diferencia_tiempo >= TiempoEntreProcesos || (verSimulacion != 'y' && verSimulacion != 'Y')){
            // Actualizamos las referencias de tiempo para el tick
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
            //  Indicamos que ya paso un tick
            tiempo_transcurrido++;
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

int RR(){
    int i; // Variable temporal
    int q; // tamaño del quantum
    int indiceProcesosRR,indiceColaProcesosRR;  //  Indices para administras las colas
    int procesosAtendidos;
    int tiempo_transcurrido;    // Tiempo transcurrido desde que comenzo este hilo
    time_t tiempo_actual;
    time_t tiempo_referencia;
    float diferencia_tiempo;    // Tiempo transcurrido en ticks
    struct proceso colaProcesosRR[nProcesos];   // Cola sobre la que se va rotando
    struct proceso procesoTemp; //  Proceso temporal para respaldar datos

    printf("\n\n---Comenzando Round Robin---");
    do{
        printf("\n\nIngrese el tamaño del quantum: ");
        scanf("%i",&q);
        if(q<1){
            printf("\tEl quantum no puede ser menor a 1 tick.\n");
        }
    }while(q<1);

    // Simulamos los ticks haciendo una diferencia de tiempo
    tiempo_transcurrido = 0;
    time(&tiempo_referencia);
    indiceProcesosRR = 0;
    indiceColaProcesosRR = 0;
    procesosAtendidos = 0;
    while(procesosAtendidos < nProcesos){   // Mientras no se hayan atendido todos los procesos
        // Obtenemos el tiempo actual y calculamos la diferencia de tiempo para ver si hicimos un tick
        time(&tiempo_actual);
        diferencia_tiempo = difftime(tiempo_actual, tiempo_referencia);
        // HUBO UN TICK!
        if(diferencia_tiempo >= TiempoEntreProcesos || (verSimulacion != 'y' && verSimulacion != 'Y')){
            // Actualizamos las referencias de tiempo para el tick
            time(&tiempo_referencia);
            diferencia_tiempo = 0.0;

            if(indiceProcesosRR < nProcesos){
                // Si el siguiente proceso ya esta en tiempo de ser atendido, lo añadimos a la cola que se procesa
                if(tiempo_transcurrido >= procesosRR[indiceProcesosRR].inicio){
                    colaProcesosRR[indiceColaProcesosRR].nombre = procesosRR[indiceProcesosRR].nombre;
                    colaProcesosRR[indiceColaProcesosRR].inicio = procesosRR[indiceProcesosRR].inicio;
                    colaProcesosRR[indiceColaProcesosRR].t = procesosRR[indiceProcesosRR].t;
                    colaProcesosRR[indiceColaProcesosRR].tiempo_transcurrido = procesosRR[indiceProcesosRR].tiempo_transcurrido;
                    indiceProcesosRR++;
                    indiceColaProcesosRR++;
                }
            }

            // Si tenemos procesos en cola
            if(indiceColaProcesosRR > 0){
                s_RR[tiempo_transcurrido] = colaProcesosRR[0].nombre;
                colaProcesosRR[0].tiempo_transcurrido++;
                //  Si el tiempo que ha estado el proceso en memoria es igual al tiempo que se supone debe estar
                //  significa que ya ha estado el tiempo que debe estar y debemos procesar sus demas datos
                if(colaProcesosRR[0].tiempo_transcurrido == colaProcesosRR[0].t){
                    for( i = 0; colaProcesosRR[0].nombre != procesosRR[i].nombre; i++); // Bucamos el proceso en la tabla de procesos (no en la cola)
                    // Realizamos los calculos
                    procesosRR[i].fin = tiempo_transcurrido;
                    procesosRR[i].T = procesosRR[i].fin - procesosRR[i].inicio;
                    procesosRR[i].E = procesosRR[i].T - procesosRR[i].t;
                    procesosRR[i].P = procesosRR[i].T / (float)procesosRR[i].t;
                    procesosRR[i].R = (float)procesosRR[i].t / procesosRR[i].T;

                    // Recorremos todos los procesos en la cola, notese que ya no respaldamos ni insertamos el proceso en la cola de nuevo
                    for( i = 0; i < (indiceColaProcesosRR-1); i++){
                        colaProcesosRR[i].nombre = colaProcesosRR[i+1].nombre;
                        colaProcesosRR[i].inicio = colaProcesosRR[i+1].inicio;
                        colaProcesosRR[i].t = colaProcesosRR[i+1].t;
                        colaProcesosRR[i].tiempo_transcurrido = colaProcesosRR[i+1].tiempo_transcurrido;
                    }
                    indiceColaProcesosRR--;
                    procesosAtendidos++;
                }else{
                    // En caso de que se haya cumplido el quantum
                    if((tiempo_transcurrido%q) == 0){
                        // En caso de que el proceso aun tenga que seguir en memoria, pasamos a moverlo al final de la cola

                        //  Respaldamos el dato
                        procesoTemp.nombre = colaProcesosRR[0].nombre;
                        procesoTemp.inicio = colaProcesosRR[0].inicio;
                        procesoTemp.t = colaProcesosRR[0].t;
                        procesoTemp.tiempo_transcurrido = colaProcesosRR[0].tiempo_transcurrido;

                        // Recorremos todos los procesos de la cola
                        for( i = 0; i < (indiceColaProcesosRR-1); i++){
                            colaProcesosRR[i].nombre = colaProcesosRR[i+1].nombre;
                            colaProcesosRR[i].inicio = colaProcesosRR[i+1].inicio;
                            colaProcesosRR[i].t = colaProcesosRR[i+1].t;
                            colaProcesosRR[i].tiempo_transcurrido = colaProcesosRR[i+1].tiempo_transcurrido;
                        }
                        //  Insertamos el valor respaldado al final de la cola
                        colaProcesosRR[i].nombre = procesoTemp.nombre;
                        colaProcesosRR[i].inicio = procesoTemp.inicio;
                        colaProcesosRR[i].t = procesoTemp.t;
                        colaProcesosRR[i].tiempo_transcurrido = procesoTemp.tiempo_transcurrido;
                    }
                }
            }else{  // No hay ningun proceso atendiendose en este momento
                s_RR[tiempo_transcurrido] = '-';
            }
            s_RR[tiempo_transcurrido+1] = '\0';

            imprimirProcesos();
            printf("\n\n---Procesando con RR (q = %i)---\n\n",q);
            printf("t = %i\t%s\n",tiempo_transcurrido,s_RR);

            //  Indicamos que ya paso un tick
            tiempo_transcurrido++;
        }
    }
    return q;
}

void resultadosRR(int q){
    int i;
    struct proceso promedio;
    promedio.T = 0.0;
    promedio.E = 0.0;
    promedio.P = 0.0;
    promedio.R = 0.0;

    printf("\n\n---Resultados de RR (q = %i)---\n\n",q);
    printf("Proceso\tInicio\tFin\tt\tT\tE\tP\tR\n");
    printf("----------------------------------------------------------------\n");
    for( i = 0; i < nProcesos; i++){
        printf("%c\t%i\t%i\t%i\t%.2f\t%.2f\t%.2f\t%.2f\n",procesosRR[i].nombre,procesosRR[i].inicio,procesosRR[i].fin,procesosRR[i].t,procesosRR[i].T,procesosRR[i].E,procesosRR[i].P,procesosRR[i].R);
        promedio.T += procesosRR[i].T;
        promedio.E += procesosRR[i].E;
        promedio.P += procesosRR[i].P;
        promedio.R += procesosRR[i].R;
    }
    promedio.T /= (float)nProcesos;
    promedio.E /= (float)nProcesos;
    promedio.P /= (float)nProcesos;
    promedio.R /= (float)nProcesos;
    printf("----------------------------------------------------------------\n");
    printf("Prom\t \t \t \t%.2f\t%.2f\t%.2f\t%.2f\n\n",promedio.T,promedio.E,promedio.P,promedio.R);
    printf("Orden: %s\n",s_RR);
}
