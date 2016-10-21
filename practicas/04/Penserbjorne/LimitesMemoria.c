#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define SALIR 0

int subMenu();

int main()
{
    long long int i;
    int opcion;

    printf("Los límites de lo aceptable tras un malloc\n\n");
    do{
        printf("Seleccione una opcion\n\n");
        printf("\t1.-Ejercicio de @gwolf\n");
        printf("\t2.-Modificacion a tipo char\n");
        printf("\t3.-Modificacion a tipo float\n");
        printf("\t4.-Modificacion a tipo double\n");
        printf("\t0.-Salir\n");
        printf("Opcion: ");
        scanf("%i",&opcion);

        switch(opcion){
            case 0:
                printf(":'v adios!\n");
                break;
            case 1:
                ;
                int *datos;
                datos = (int*) malloc(16 * sizeof(int));
                for (i=0; i<65536; i++){
                    printf("La palabra #%d es: %d\n", i, datos[i]);
                }
                free(datos);
                break;
            case 2:
                ;
                char *datos_char;
                datos_char = (char*) malloc(sizeof(char));

                opcion = subMenu();

                switch(opcion){
                    case 1:
                        for (i = 0; i < LLONG_MAX; i++){
                            printf("La palabra #%d es: %c\n", i, datos_char[i]);
                        }
                        break;
                    case 2:
                        for (i = 0; i > LLONG_MIN; i--){
                            printf("La palabra #%d es: %c\n", i, datos_char[i]);
                        }
                        break;
                }
                free(datos_char);
                break;
            case 3:
                ;
                float *datos_float;
                datos_float = (float*) malloc(sizeof(float));

                opcion = subMenu();

                switch(opcion){
                    case 1:
                        for (i = 0; i < LLONG_MAX; i++){
                            printf("La palabra #%d es: %f\n", i, datos_float[i]);
                        }
                        break;
                    case 2:
                        for (i = 0; i > LLONG_MIN; i--){
                            printf("La palabra #%d es: %f\n", i, datos_float[i]);
                        }
                        break;
                }
                free(datos_float);
                break;
            case 4:
                ;
                double *datos_double;
                datos_double = (double*) malloc(sizeof(double));

                opcion = subMenu();

                switch(opcion){
                    case 1:
                        for (i = 0; i < LLONG_MAX; i++){
                            printf("La palabra #%d es: %lf\n", i, datos_double[i]);
                        }
                        break;
                    case 2:
                        for (i = 0; i > LLONG_MIN; i--){
                            printf("La palabra #%d es: %lf\n", i, datos_double[i]);
                        }
                        break;
                }
                free(datos_double);
                break;
            default:
                printf("Opcion inexistente. Seleccione una opcion valida.\n");
        }
    }while(opcion != SALIR);
    return 0;
}

int subMenu(){
    int opcion;
    do
    {
        printf("\t\tSeleccione una opcion:\n");
        printf("\t\t\t1.-Recorrer con indices positivos\n");
        printf("\t\t\t2.-Recorrer con indices negativos\n");
        printf("\t\tOpcion: ");
        scanf("%i",&opcion);
        if(opcion < 1 || opcion > 2){
            printf("\tIngrese una opcion valida. e.e\n");
        }
    }while(opcion < 1 || opcion > 2);
    return opcion;
}
