/**
*   Autor: Paul Aguilar a.k.a Penserbjorne
*   Tarea: Administracion de procesos: Algoritmos de planificacion
*   Algoritmo implementados: FCFS, RR, SRR
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
    int prioridad;  //  Solo para SRR
};

//  Lista procesos a trabajar
struct proceso procesos[nProcesos];
struct proceso procesosFCFS[nProcesos];
struct proceso procesosRR[nProcesos];
struct proceso procesosSRR[nProcesos];

  //  Resultado de como se corrieron los procesos por cada algoritmo
char* s_FCFS;
char s_RR[TamBuffer];
char s_SRR[TamBuffer];
char verSimulacion;

void imprimirProcesos();
void FCFS();
void resultadosFCFS();
void RR(int q);
void resultadosRR(int q);
void SRR(int q, int a, int b);
void resultadosSRR(int q, int a, int b);

int main()
{
    int i;
    int q1,q2;  //quantum!!!

    // a    Ritmo de incremento de prioridad de procesos nuevos en SRR
    // b    Ritmo de incremento de prioridad de procesos aceptados en SRR
    int a, b;

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

        procesosSRR[i].nombre = procesos[i].nombre;
        procesosSRR[i].inicio = procesos[i].inicio;
        procesosSRR[i].t = procesos[i].t;
        procesosSRR[i].tiempo_transcurrido = procesos[i].tiempo_transcurrido;
    }

    printf("Desea ver \"simulados\" los procesamientos de las colas? [y\\n]: ");
    scanf("%c",&verSimulacion);

    printf("\n\n---Round Robin---");
    do{
        printf("\n\nIngrese el tamaño del quantum: ");
        scanf("%i",&q1);
        if(q1<1){
            printf("\tEl quantum no puede ser menor a 1 tick.\n");
        }
    }while(q1<1);

    printf("\n\n---Selfish Round Robin---");
    do{
        printf("\n\nIngrese el tamaño del quantum: ");
        scanf("%i",&q2);
        if(q2<1){
            printf("\tEl quantum no puede ser menor a 1 tick.\n");
        }
    }while(q2<1);

    do{
        printf("\n\nIngrese el ritmo de incremento de prioridad de procesos nuevos: ");
        scanf("%i",&a);
        if(a<1){
            printf("\tEl incremento no puede ser menor a 1.\n");
        }
    }while(a<1);

    do{
        printf("\n\nIngrese el ritmo de incremento de prioridad de procesos aceptados: ");
        scanf("%i",&b);
        if(b<0){
            printf("\tEl incremento no puede ser menor a 0.\n");
        }
    }while(b<0);
    // Procesamos la cola de procesos
    FCFS();
    RR(q1);
    SRR(q2,a,b);

    imprimirProcesos();
    resultadosFCFS();
    resultadosRR(q1);
    resultadosSRR(q2,a,b);
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
                procesosFCFS[i].fin = tiempo_transcurrido+1;    // Añadimos 1 porque aun no actualizamos el contador
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

void RR(int q){
    int i; // Variable temporal
    int indiceProcesosRR,indiceColaProcesosRR;  //  Indices para administras las colas
    int procesosAtendidos;
    int tiempo_transcurrido;    // Tiempo transcurrido desde que comenzo este hilo
    time_t tiempo_actual;
    time_t tiempo_referencia;
    float diferencia_tiempo;    // Tiempo transcurrido en ticks
    struct proceso colaProcesosRR[nProcesos];   // Cola sobre la que se va rotando
    struct proceso procesoTemp; //  Proceso temporal para respaldar datos

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
                    procesosRR[i].fin = tiempo_transcurrido+1;    // Añadimos 1 porque aun no actualizamos el contador
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

void SRR(int q, int a, int b){
    // q    tamaño del quantum
    // a    Ritmo de incremento de prioridad de procesos nuevos
    // b    Ritmo de incremento de prioridad de procesos aceptados

    int i,j;  // Variables temporales
    int maxPrioridad, minPrioridad; // variables bandera para iterar y buscar las prioridades de los procesos
    int indiceProcesosSRR,indiceProcesosNuevos, indiceProcesosAceptados;  //  Indices para administras las colas
    int procesosAtendidos;
    int tiempo_transcurrido;    // Tiempo transcurrido desde que comenzo este hilo
    time_t tiempo_actual;
    time_t tiempo_referencia;
    float diferencia_tiempo;    // Tiempo transcurrido en ticks
    struct proceso procesosNuevos[nProcesos];   // Cola de procesos nuevos en espera
    struct proceso procesosAceptados[nProcesos];   // Cola sobre la que se va rotando
    struct proceso procesoTemp; //  Proceso temporal para respaldar datos

    // Simulamos los ticks haciendo una diferencia de tiempo
    tiempo_transcurrido = 0;
    time(&tiempo_referencia);
    indiceProcesosSRR = 0;
    indiceProcesosNuevos = 0;
    indiceProcesosAceptados = 0;
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

            // Buscamos todos los procesos que ya esten en tiempo de ser atendidos y los añadimos a los procesos nuevos
            for( i = indiceProcesosSRR; i< nProcesos; i++){
                // Si el siguiente proceso ya esta en tiempo de ser atendido, lo añadimos a la cola que se procesa
                if(tiempo_transcurrido >= procesosSRR[i].inicio){
                    procesosNuevos[indiceProcesosNuevos].nombre = procesosSRR[i].nombre;
                    procesosNuevos[indiceProcesosNuevos].inicio = procesosSRR[i].inicio;
                    procesosNuevos[indiceProcesosNuevos].t = procesosSRR[i].t;
                    procesosNuevos[indiceProcesosNuevos].tiempo_transcurrido = procesosSRR[i].tiempo_transcurrido;
                    procesosNuevos[indiceProcesosNuevos].prioridad = procesosSRR[i].prioridad;
                    indiceProcesosSRR++;
                    indiceProcesosNuevos++;
                }
            }

            // Si no hay procesos aceptados y si hay procesos nuevos, pasamos a buscar el proceso con mayor prioridad
            // de entre todos los nuevos para pasarlo a aceptados
            if(!indiceProcesosAceptados && indiceProcesosNuevos){
                j = 0;
                maxPrioridad = 0;
                // Buscamos el proceso nuevo con mayor prioridad
                for( i = 0; i < indiceProcesosNuevos; i++){
                    if(procesosNuevos[i].prioridad > maxPrioridad){
                        j = i;
                        maxPrioridad = procesosNuevos[i].prioridad;
                    }
                }
                // Insertamos el proceso con mayor prioridad de los nuevos en los aceptados
                procesosAceptados[indiceProcesosAceptados].nombre = procesosNuevos[j].nombre;
                procesosAceptados[indiceProcesosAceptados].inicio = procesosNuevos[j].inicio;
                procesosAceptados[indiceProcesosAceptados].t = procesosNuevos[j].t;
                procesosAceptados[indiceProcesosAceptados].tiempo_transcurrido = procesosNuevos[j].tiempo_transcurrido;
                procesosAceptados[indiceProcesosAceptados].prioridad = procesosNuevos[j].prioridad;

                // Recorremos la cola de procesos nuevos desde j que es donde se encontraba el proceso nuevo que movimos
                for( i = j; i < (indiceProcesosNuevos-1); i++){
                    procesosNuevos[i].nombre = procesosNuevos[i+1].nombre;
                    procesosNuevos[i].inicio = procesosNuevos[i+1].inicio;
                    procesosNuevos[i].t = procesosNuevos[i+1].t;
                    procesosNuevos[i].tiempo_transcurrido = procesosNuevos[i+1].tiempo_transcurrido;
                    procesosNuevos[i].prioridad = procesosNuevos[i+1].prioridad;
                }

                indiceProcesosNuevos--;
                indiceProcesosAceptados++;
            }

            // Si tenemos procesos aceptados
            if(indiceProcesosAceptados > 0){
                s_SRR[tiempo_transcurrido] = procesosAceptados[0].nombre;
                procesosAceptados[0].tiempo_transcurrido++;
                //  Si el tiempo que ha estado el proceso en memoria es igual al tiempo que se supone debe estar
                //  significa que ya ha estado el tiempo que debe estar y debemos procesar sus demas datos
                if(procesosAceptados[0].tiempo_transcurrido == procesosAceptados[0].t){
                    for( i = 0; procesosAceptados[0].nombre != procesosSRR[i].nombre; i++); // Bucamos el proceso en la tabla de procesos (no en la cola)
                    // Realizamos los calculos
                    procesosSRR[i].fin = tiempo_transcurrido+1; // Añadimos 1 porque aun no actualizamos el contador
                    procesosSRR[i].T = procesosSRR[i].fin - procesosSRR[i].inicio;
                    procesosSRR[i].E = procesosSRR[i].T - procesosSRR[i].t;
                    procesosSRR[i].P = procesosSRR[i].T / (float)procesosSRR[i].t;
                    procesosSRR[i].R = (float)procesosSRR[i].t / procesosSRR[i].T;
                    procesosSRR[i].prioridad = procesosAceptados[0].prioridad;

                    // Recorremos todos los procesos en la cola de aceptados, notese que ya no respaldamos ni insertamos el proceso en la cola nuevamente
                    for( i = 0; i < (indiceProcesosAceptados-1); i++){
                        procesosAceptados[i].nombre = procesosAceptados[i+1].nombre;
                        procesosAceptados[i].inicio = procesosAceptados[i+1].inicio;
                        procesosAceptados[i].t = procesosAceptados[i+1].t;
                        procesosAceptados[i].tiempo_transcurrido = procesosAceptados[i+1].tiempo_transcurrido;
                        procesosAceptados[i].prioridad = procesosAceptados[i+1].prioridad;
                    }
                    indiceProcesosAceptados--;
                    procesosAtendidos++;
                }else{
                    // En caso de que se haya cumplido el quantum
                    if((tiempo_transcurrido%q) == 0){
                        // En caso de que el proceso aun tenga que seguir en memoria, pasamos a moverlo al final de la cola

                        //  Respaldamos el dato
                        procesoTemp.nombre = procesosAceptados[0].nombre;
                        procesoTemp.inicio = procesosAceptados[0].inicio;
                        procesoTemp.t = procesosAceptados[0].t;
                        procesoTemp.tiempo_transcurrido = procesosAceptados[0].tiempo_transcurrido;
                        procesoTemp.prioridad = procesosAceptados[0].prioridad;

                        // Recorremos todos los procesos de la cola
                        for( i = 0; i < (indiceProcesosAceptados-1); i++){
                            procesosAceptados[i].nombre = procesosAceptados[i+1].nombre;
                            procesosAceptados[i].inicio = procesosAceptados[i+1].inicio;
                            procesosAceptados[i].t = procesosAceptados[i+1].t;
                            procesosAceptados[i].tiempo_transcurrido = procesosAceptados[i+1].tiempo_transcurrido;
                            procesosAceptados[i].prioridad = procesosAceptados[i+1].prioridad;
                        }
                        //  Insertamos el valor respaldado al final de la cola
                        procesosAceptados[i].nombre = procesoTemp.nombre;
                        procesosAceptados[i].inicio = procesoTemp.inicio;
                        procesosAceptados[i].t = procesoTemp.t;
                        procesosAceptados[i].tiempo_transcurrido = procesoTemp.tiempo_transcurrido;
                        procesosAceptados[i].prioridad = procesoTemp.prioridad;
                    }
                }
            }else{  // No hay ningun proceso atendiendose en este momento
                s_SRR[tiempo_transcurrido] = '-';
            }
            s_SRR[tiempo_transcurrido+1] = '\0';

            //Buscamos la prioridad mas pequeña de los procesos aceptados para ver si alguno nuevo puede entrar a los aceptados
            minPrioridad = TamBuffer;
            for( i = 0; i < indiceProcesosAceptados; i++){
                if(procesosAceptados[i].prioridad < minPrioridad){
                    minPrioridad = procesosAceptados[i].prioridad;
                }
            }
            //Buscamos los procesos nuevos que ya hayan llegado a la prioridad minima posible para poder ser aceptados
            for(i = 0; i < indiceProcesosNuevos; i++){
                // Si un proceso cumple el requisito
                if(procesosNuevos[i].prioridad >= minPrioridad){
                    // Insertamos el proceso nuevo en los aceptados
                    procesosAceptados[indiceProcesosAceptados].nombre = procesosNuevos[i].nombre;
                    procesosAceptados[indiceProcesosAceptados].inicio = procesosNuevos[i].inicio;
                    procesosAceptados[indiceProcesosAceptados].t = procesosNuevos[i].t;
                    procesosAceptados[indiceProcesosAceptados].tiempo_transcurrido = procesosNuevos[i].tiempo_transcurrido;
                    procesosAceptados[indiceProcesosAceptados].prioridad = procesosNuevos[i].prioridad;
                    // recorremos los procesos nuvos
                    for( j = i; j < (indiceProcesosNuevos-1); j++){
                        procesosNuevos[j].nombre = procesosNuevos[j+1].nombre;
                        procesosNuevos[j].inicio = procesosNuevos[j+1].inicio;
                        procesosNuevos[j].t = procesosNuevos[j+1].t;
                        procesosNuevos[j].tiempo_transcurrido = procesosNuevos[j+1].tiempo_transcurrido;
                        procesosNuevos[j].prioridad = procesosNuevos[j+1].prioridad;
                    }
                    indiceProcesosNuevos--;
                    indiceProcesosAceptados++;
                }
            }
            // Incrementamos las prioridades de todas las colas
            for( i = 0; i < indiceProcesosNuevos; i++){
                procesosNuevos[i].prioridad += a;
            }
            for( i = 0; i < indiceProcesosAceptados; i++){
                procesosAceptados[i].prioridad += a;
            }

            imprimirProcesos();
            printf("\n\n---Procesando con SRR (q = %i , a = %i , b = %i , b/a = %.2f)---\n\n",q,a,b,(float)b/(float)a);
            printf("t = %i\t%s\n",tiempo_transcurrido,s_SRR);

            //  Indicamos que ya paso un tick
            tiempo_transcurrido++;
        }
    }
}

void resultadosSRR(int q, int a, int b){
    int i;
    struct proceso promedio;
    promedio.T = 0.0;
    promedio.E = 0.0;
    promedio.P = 0.0;
    promedio.R = 0.0;

    printf("\n\n---Resultados de SRR (q = %i , a = %i , b = %i , b/a = %.2f)---\n\n",q,a,b,(float)b/(float)a);
    printf("Proceso\tInicio\tFin\tt\tT\tE\tP\tR\n");
    printf("----------------------------------------------------------------\n");
    for( i = 0; i < nProcesos; i++){
        printf("%c\t%i\t%i\t%i\t%.2f\t%.2f\t%.2f\t%.2f\n",procesosSRR[i].nombre,procesosSRR[i].inicio,procesosSRR[i].fin,procesosSRR[i].t,procesosSRR[i].T,procesosSRR[i].E,procesosSRR[i].P,procesosSRR[i].R);
        promedio.T += procesosSRR[i].T;
        promedio.E += procesosSRR[i].E;
        promedio.P += procesosSRR[i].P;
        promedio.R += procesosSRR[i].R;
    }
    promedio.T /= (float)nProcesos;
    promedio.E /= (float)nProcesos;
    promedio.P /= (float)nProcesos;
    promedio.R /= (float)nProcesos;
    printf("----------------------------------------------------------------\n");
    printf("Prom\t \t \t \t%.2f\t%.2f\t%.2f\t%.2f\n\n",promedio.T,promedio.E,promedio.P,promedio.R);
    printf("Orden: %s\n",s_SRR);
}
