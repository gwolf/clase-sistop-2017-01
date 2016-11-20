/*
Vargas Espinosa Miguel Angel
Administrador de archivos simples.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h> //Biblioteca para enteros de tamaño estandar
#include <sys/types.h> //Llamadas estandar al sistema operativo
#include <sys/stat.h> /*Biblioteca de herramientas para reconocer 
						elementos del sistema*/
#include <unistd.h>  //Biblioteca para manejo de directorios


void nuevo_archivo(const);
void monta_archivo(const char*, char*);
void acceso_shell();


int32_t main(const int32_t argc, const char **argv){		
		
	if(argc != 2){
		printf("Poblema con agumentos iniciales \n");
		return 0; //Retorno si ejecucion no existosa
	}else{
		if(strlen(argv[1])<30){
		...
		
		}else{
			printf("Nombre demasiado grande\n");
			return -1;		
		}
	}

	return 0;
}

void monta_archivo(const char* argumento, char* string){
//Por medio de la funcion stat() y mount se monta y se prepara
//el sistema de ficheros objetivo

	struct stat st = {0};
	int32_t status= 1;

	if (stat("/tmp/ssfs", &st) == -1) {
		status= mkdir("/tmp/ssfs", 0700); //Permiso octal
		//Usuario estandar permisos totales, otros usuarios ninguno
	}

	if(status!=(-1)){
	
	}else{
		printf("Error al crear directorio para el archivo\n");
	}

	return;
}


void acceso_shell(void){

	int32_t estado= 0;
	FILE *existe= NULL;
	struct stat st_buf;

	chdir("/tmp/ssfs");	
	system("clear");	

	while(1){	
		getcwd(nuevaruta, sizeof(nuevaruta));
		strcat(nuevaruta,"/");
		printf("ssfs$ %s: ",nuevaruta);
		
		

		if(strcmp(comando,"crear")==0){
			
		}else if(strcmp(comando,"arbol")==0){
		
		}else if(strcmp(comando,"cdir")==0){
			
			if(parametro==".."){
				chdir(raiz);
			}else{

				if(estado!=0){
					printf("Error, ruta no valida\n");
				}
			}

		}else if(strcmp(comando,"edita")==0){
	
			if(existe==NULL || S_ISDIR(st_buf.st_mode)){
				printf("No existe el archivo\n");
				fclose(existe);
			}else{
				fclose(existe);

			}

		}else if(strcmp(comando,"leer")==0){

			if(existe==NULL || S_ISDIR(st_buf.st_mode)){

			}else{

			}

		printf("Opcion incorrecta\n");

	}

}


