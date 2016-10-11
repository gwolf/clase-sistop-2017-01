/*@file monitor.c
*@version 1.0
*@date 08/10/16
*@author Valdespino Hinojosa Erick Alejandro & Vargas Espinosa Miguel Angel
*@title Monitor de recursos sistema Linux
*@brief Programa que nos    ayuda a visualizar algunos datos curiosos de nuestro sistema. :-)
*Version del compilador: gcc 5.3.1
*Cambios: Ninguno a documentar desde semestre anterior
*Comandos a ejecutar: En cmd o command, escribir "gcc monitor.c"
*Comentarios añadidos para el sistema Doxygen y generación de documentos
*/

#include<stdio.h> /*@brief Cabecera estandar de I/O*/
#include<stdlib.h> /*@brief Cabecera estandar de proposito general*/
#include<dirent.h> /*@brief Cabecera que facilita desplazamiento en directorios*/
#include<unistd.h> /*@brief Provee acceso a la API del sistema operativo POSIX*/
#include<string.h> /*@brief Facilita el uso de arreglos de caracteres*/


void menu();  
int elMasGrande(); /*@brief En esta varieble acomodaremos nuestro proceso más grande en ejecución*/
int listarProc();  /*@brief Lista de procesos que veremos a continuación*/
int verMemoria();  /*@brief Memoria del sitema*/


int main(void){
     /**
     *@title main(void)
    * @brief Funcion main inicio del programa
    */
  char c;
  int opcion=0,error,pid;

  menu()/**
     *@title menu()
    * @brief Menu principal que nos ayuda a navegar entre las diferentes opciones que brindamos para mostrar.
    */;
     
  while(1){
    error= scanf("%d",&opcion);

    while(error==0)      /*@brief  Ciclo while que toma los caracteres ingresados por el usuario hasta que no haya mas y no interfiera con el scanf*/
      {
      printf("Dato no valido, ingrese uno nuevo por favor\n");
      while((c= getchar()) != '\n' && c != EOF);
      error= scanf("%d",&opcion);
    }

    switch(opcion){ 
      case 1:       // @brief Opción 1: Proceso mas grande
        pid= fork(); // @brief Crea la bifurcacion padre/hijo
        if(pid)
          continue;
        else{
          elMasGrande();
          menu();
          exit(0);
        }
      break;

      case 2:     // @brief Opción 2: Lista de procesos
        pid= fork();
        if(pid)
          continue;
        else{
          listarProc();
          menu();
          exit(0);
        }
      break;

      case 3:     //@brief Opción 3:Ver memoria del sistema.
        pid= fork();
        if(pid)
          continue;
        else{
          verMemoria();
          menu();
          exit(0);
        }
      break;

      case 4:     //@brief Opción 4: Limpiar pantalla
        system("clear");
        menu();
      break;

      case 5:  //@brief Opción 5: Salir del programa
        printf("\n\nSaliendo del programa... (Presiona enter)\n");
        while((c= getchar()) != '\n' && c != EOF);
        getchar();
        return 0;
      break;

      default:   //@brief Opción para ninguna de las anteriores
        printf("\n\nOpcion incorrecta\n");
      break;
    }
  }
}

void menu(){ //@brief Funcion que muestra menu y nos despliega las funciones.
  printf("\n\nMonitor del sistema linux\n\nIngrese la opci%cn que desea ver:\n",163);
  printf("1. Saber el proceso mas grande posible en el sistema\n");
  printf("2. Ver procesos activos\n");
  printf("3. Ver el estado del disco duro\n");
  printf("4. Limpiar pantalla\n");
  printf("5. Salir del programa\n\n>");

  return;
}

int elMasGrande(){ 
    /**
    * @brief Funcion que obtiene el proceso con el PID mas grande
    *PROC El sistema de archivos /proc contiene un sistema de archivos imaginario o virtual. Este no existe fisicamente en disco, sino que el nucleo lo crea en memoria. Se utiliza para ofrecer informacion relacionada con el sistema (originalmente acerca de procesos, de aqui su nombre).
    *@code
    *archivo= fopen("/proc/sys/kernel/pid_max","r");
    *@endcode
    */{ 
  FILE *archivo;
  int max_pid;
  //@brief PROC El sistema de archivos /proc contiene un sistema de archivos imaginario o virtual. Este no existe físicamente en disco, sino que el núcleo lo crea en memoria. Se utiliza para ofrecer información relacionada con el sistema (originalmente acerca de procesos, de aquí su nombre).
  archivo= fopen("/proc/sys/kernel/pid_max","r");
  if(archivo){
    fscanf(archivo,"%d",&max_pid);

    if(!fclose(archivo)){}
    else{
      printf("\n\nError al cerrar el archivo\n\n");
    }
  }else{
    printf("\n\nError al abrir archivo\n\n");
    return -1;
  }

  printf("\n\nEl mas grande es: %d\n",max_pid);

  return 0;
}

int listarProc(){  
    /**
    * @brief Funcion que lista los procesos
    */{
  DIR *dir; //@brief Tipo de dato que representa un directorio
  FILE *nombre,*tamano; //@brief tipo de dato que representa un fichero
  struct dirent *entry;
  int i,filtro,j=0,tam;
  char direccion[100]= "/proc",carpeta[100]="/proc/",aux1[100],c;
  char aux2[100],nom[100];

  dir = opendir(direccion);

  if(dir){


    printf("\n\nLos procesos activos en el sistema son:\n\n");
    for(i= 0;entry= readdir(dir);i++){

      filtro= atoi(entry->d_name); //@brief Convierte cadena en entero
      if(filtro > 0){
        j++;
        strcpy(aux1,carpeta);
        strcat(aux1,entry->d_name);
        strcat(aux1,"/status");
        strcpy(aux2,carpeta);
        strcat(aux2,entry->d_name);
        strcat(aux2,"/statm");
        nombre= fopen(aux1,"r");
        tamano= fopen(aux2,"r");

        if(nombre && tamano){
          fscanf(nombre,"Name: %s",nom);
          fscanf(tamano,"%d",&tam);
          printf("Proceso: %d\tPID: %d\tMemoria %dkB\tPrograma: %s\n",j,filtro,tam,nom);
          if(!fclose(nombre) && !fclose(tamano)){}
          else{
            printf("Error al cerrar uno de los archivos, archivos no cerrados");
            return -1;
          }
        }else{
          printf("\n\nError al intentar abrir los archivos\n\n");
          return -1;
        }
      }
    }
  }else{
    printf("\n\nError al intentar abrir el directorio\n\n");
    return -1;
  }

  return 0;
}

int verMemoria(){ 
   /**
    * @brief Funcion que muestra datos de la memoria
    */
  char carpeta[10]="/proc/",aux[20];
  FILE *memoria;
  int memtotal,memlibre,memusada,memdisponible;

  strcpy(aux,carpeta);
  strcat(aux,"meminfo");

  memoria= fopen(aux,"r");
  if(memoria){
    fscanf(memoria,"MemTotal: %d kB",&memtotal);
    fgets(aux,sizeof(aux),memoria);
    fscanf(memoria,"MemFree: %d kB",&memlibre);

    memusada= memtotal-memlibre;

    printf("\n\nEl sistema tiene %d kB (~%.2f MB) en total\n",memtotal,(float)memtotal/1024);
    printf("%d kB (~%.2f MB) estan usados\n",memusada,(float)memusada/1024);
    printf("%d kB (~%.2f MB) estan libres\n\n",memlibre,(float)memlibre/1024);

    if(!fclose(memoria)){}
    else{
      printf("Error al cerrar el archivo, archivo no cerrado");
      return -1;
    }
  }else{
    printf("\n\nError al intentar abrir el archivo\n\n");
    return -1;
  }

  return 0;
}
