/*
Vargas Espinosa Miguel Angel
Administrador de archivos simples.
*//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h> //Biblioteca para enteros de tamaño estandar
#include <sys/types.h> //Llamadas estandar al sistema operativo
#include <sys/stat.h> /*Biblioteca de herramientas para reconocer 
						elementos del sistema*/
#include <unistd.h>  //Biblioteca para manejo de directorios


void nuevo_arch(const char*, char*);
void montar(const char*, char*);
void shell(void);
void desmontar(const char*, char*);


int32_t main(const int32_t argc, const char **argv){	
//Se toman los valores del argv y se pasan a las funciones que los usaran
	
	char string[100], ruta[100];	
		
	if(argc != 2){
		printf("Error en los argumentos inciales\n");
		return -1; //Retorno si ejecucion no existosa
	}else{
		if(strlen(argv[1])<30){
			//Se obtiene la ruta de donde se ejecuta el archivo
			getcwd(ruta, sizeof(ruta));		
			nuevo_arch(argv[1],string);
			montar(argv[1],string);
			shell();
			desmontar(argv[1], ruta);
		}else{
			printf("Nombre de archivo demasiado grande\n");
			return -1;		
		}
	}

	return 0; //Retorno si ejecucion exitosa
}


void nuevo_arch(const char* argu, char* chain){

	FILE *existe=NULL;
	existe= fopen(argu,"r");
	//Comprueba existencia
	if(existe==NULL){
		strcpy(chain,"dd if=/dev/zero of=");
		strcat(chain,argu);
		strcat(chain," bs=1M count=100");
		system(chain);
	}else{
		fclose(existe);
	}

	strcpy(chain,"sudo mkfs -t ext4 -m 1 ");
	strcat(chain,argu);
	system(chain);
	
	return;
}


void montar(const char* argu, char* string){
//Por medio de la funcion stat() y mount se monta y se prepara
//el sistema de ficheros objetivo

	struct stat st = {0};
	int32_t status= 1;

	if (stat("/tmp/ssfs", &st) == -1) {
		status= mkdir("/tmp/ssfs", 0700); //Permiso octal
		//Usuario estandar permisos totales, otros usuarios ninguno
	}

	if(status!=(-1)){
		strcpy(string,"sudo mount -t ext4 -o loop ");
		strcat(string, argu);
		strcat(string, " /tmp/ssfs");
		system(string);	
	}else{
		printf("Error al crear directorio para el archivo\n");
	}

	return;
}


void shell(void){
//Funcion principal que nos abre una ventana de comandos parecida a Linux, aqui se insertan los comandos asociados en 
// la documentacion.
	char *comando, *param, usr[100]={'\0'};
	char new_route[100]={'\0'}, *raiz= "/tmp/ssfs";
	char asyst[100]={'\0'};
	char *token, *separa= " ";
	int32_t estado= 0;
	FILE *existe= NULL;
	struct stat st_buf;

	chdir("/tmp/ssfs");	
	system("clear");	

	while(1){	
		getcwd(new_route, sizeof(new_route));
		strcat(new_route,"/");
		printf("ssfs$ %s: ",new_route);
		fgets(usr,100,stdin);
		token= strtok(usr, separa);
		comando= token;
		token= strtok(NULL, separa);
		param= token;
		

		if(strcmp(comando,"create")==0){
			strcpy(asyst,"sudo touch ");
			strcat(asyst,new_route);
			strcat(asyst,param);
			system(asyst);	
		
		}else if(strcmp(comando,"delete")==0){
			strcpy(asyst,"sudo rm ");
			strcat(asyst,new_route);
			strcat(asyst,param);
			system(asyst);
		
		}else if(strcmp(comando,"createdir")==0){
			strcpy(asyst,"sudo mkdir ");
			strcat(asyst,new_route);
			strcat(asyst,param);
			system(asyst);
		
		}else if(strcmp(comando,"deleteadir")==0){
			strcpy(asyst,"sudo rmdir ");
			strcat(asyst,new_route);
			strcat(asyst,param);
			system(asyst);

		}else if(strcmp(comando,"list")==0){
			strcpy(asyst,"sudo ls ");
			strcat(asyst,new_route);
			system(asyst);
		
		}else if(strcmp(comando,"tree")==0){
			strcpy(asyst,"sudo tree ");
			strcat(asyst,new_route);
			system(asyst);
		
		}else if(strcmp(comando,"cdir")==0){
			
			if(param==".."){
				chdir(raiz);
			}else{
				strcpy(asyst,new_route);
				strcat(asyst,param);
				estado= chdir(asyst);
				if(estado!=0){
					printf("Error, ruta no valida\n");
				}
			}

		}else if(strcmp(comando,"edit")==0){
			existe= fopen(param,"r");
			estado= stat(param, &st_buf);
			if(existe==NULL || S_ISDIR(st_buf.st_mode)){
				//Indica si es un directorio o un archivo
				//Se usa la estructura stat
				printf("No existe el archivo\n");
				fclose(existe);
			}else{
				fclose(existe);
				strcpy(asyst,"sudo nano ");
				strcat(asyst,param);			
				system(asyst);
			}

		}else if(strcmp(comando,"read")==0){
			existe= fopen(param,"r");
			estado= stat(param, &st_buf);
			if(existe==NULL || S_ISDIR(st_buf.st_mode)){
				printf("No es un archivo\n");
				fclose(existe);
			}else{
				fclose(existe);
				strcpy(asyst, "cat ");
				strcat(asyst,param);
				system(asyst);
			}

		}else if(strcmp(comando,"out")==0){
			chdir("/tmp");
			return;
		}else
		printf("Opcion incorrecta\n");

	}

}


void desmontar(const char* nombrearch, char* ruta){
//Funcion que desmonta y permite al usuario el borrar el sistema de ficheros 
//objetivo

	char salida= '\0', nombre[100];	

	system("sudo umount /tmp/ssfs");
	printf("Desea borrar el archivo generado?(s/n)\n");
	scanf("%c",&salida);
	if(salida=='s'){
		strcpy(nombre,"rm ");
		strcat(nombre,ruta);
		strcat(nombre, "/");
		strcat(nombre,nombrearch);
		system(nombre);
	}	
		
	return;
}
