#!/usr/bin/python
# -*- coding: utf-8 -*-

import os, sys, shutil

def main():
	global ciclo, dentroDe
	ciclo = 0
	dentroDe = 0
	os.system("clear")
	os.system("ls | grep WOLF.zip > tmp")
	archivo = open("tmp", "r")

	#Buscamos si existe el zip donde se trabajará y se descomprimirá
	find_zip = archivo.readline()
	if find_zip == "WOLF.zip\n":
		print("El zip existe!")
		unzip(find_zip)
		#chdir para cambiar de directorio de trabajo
		os.chdir("WOLF")
		os.system("clear")
		print("|----------==========----------==========----------|\n\t\t----COMANDOS----")
		print("|----------==========----------==========----------|")
		print("\tnewdir, newfile, removedir, removefile\nedit, read, goin, goback, list-items\nexit, help")
		print("|----------==========----------==========----------|")
		#Mientras no pida salir, la terminla seguirá pidiendo comandos
		while ciclo != 1:		
			comando = input("root@fi_unam$ ")
			if comandos(comando):
				diccionarioComandos[comando]()
			else:
				print("¡Comando invalido!")
				print("Escribe 'help' para saber mas acerca de los comandos o intenta de nuevo con los de arriba\n")
		#rm -rf tmp usado para borrar y '..' para regresar un directorio, comprimimos la carpeta de nuevo y borramos la
		#versión de la carpeta 'WOLF' pasada
		os.system("rm -rf tmp")
		os.chdir("..")
		os.system("zip -r WOLF.zip WOLF")
		os.system("rm -rf WOLF")
		os.system("clear")
		print("¡Hasta la proxima!")
	else:
		print("¡Archivo no encontrado!\n")

#----------------------------------------------------------------------------------------------------------------------------
#AÑADIR EL CUERPO DE LA FUNCIÓN
#----------------------------------------------------------------------------------------------------------------------------

#Descomprimir el zip existente
def unzip(file_zip):
	return 0
#Verificar que comando se mando a llamar
def comandos(comando):
	return 0
#Agrega una carpeta a WOLF
def nuevaCarpeta():
	return 0

#Agrega un archivo a WOLF
def nuevoArchivo():
	return 0

#Borra una carpeta de WOLF
def eliminarCarpeta():
	return 0

#Borra un archivo de una carpeta de WOLF
def eliminarArchivo():
	return 0

#Modifica un archivo de WOLF
def editar():
	return 0

#Abre un archivo de solo lectura
def leer():
	return 0

#Dirige a una carpeta específica
def ir_a():
	return 0

#Regresa un directorio
def regresar_a():
	return 0

#Enlista los archivos de la carpeta en la que se esta ubicado
def enlistar_archivos():
	return 0

#Imprime lo que cada comando realiza
def ayuda():
	return 0

def salir():
	global ciclo
	ciclo = 1

#Diccionario que facilita la llamada a los comandos
diccionarioComandos = {'newdir': nuevaCarpeta, 'newfile': nuevoArchivo, 'removedir':eliminarCarpeta, 'removefile':eliminarArchivo, 'edit':editar,'read':leer, 'goin':ir_a, 'goback':regresar_a, 'list-items':enlistar_archivos, 'help':ayuda, 'exit': salir}

#Llamamos a la funcion para empezar a pedir coomandos
if __name__ == '__main__':
  main()
