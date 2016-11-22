#Mendoza Colmenares Gerardo
#Segundo proyecto basado en creación de archivos a partir de un zip

#En este segundo archivo se añadirá el cuerpo de las funciones

#CORRECCIONES
#Lograr el objetivo de la función


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
		#Descomprimir zip
		unzip(find_zip)
		#'chdir' para cambiar de directorio de trabajo
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
#AÑADIR DESCRIPCIÓN EL CUERPO DE LA FUNCIÓN
#----------------------------------------------------------------------------------------------------------------------------

#Descomprimir el zip existente
def unzip(file_zip):
	if len(file_zip) > 0:
		os.system("unzip WOLF.zip")
		print("Se descomprimio el zip correctamente")
	else:
		print("No existe el zip WOLF!")

#Verificar que comando se mando a llamar
def comandos(comando):
	if comando == "newdir" or comando == "newfile" or comando == "removefile" or comando == "removedir" or comando == "edit" or comando == "read" or comando == "goin" or comando == "goback" or comando == "list-items" or comando == "exit" or comando == "help":
		return True
	else:
		return False

#Agrega una carpeta a WOLF
def nuevaCarpeta():
	print("¿Cómo se va a llamar la carpeta?\nMáximo 12 caracteres")
	user_input = input(">> ")
	path = os.getcwd()

	if len(user_input) < 12:
		if not os.path.exists(user_input):
			os.makedirs(user_input)
		else:
			print("¡La carpeta ya existe!")
	else:
		print("¡Tu carpeta excede los 12 caracteres!")

#Agrega un archivo a WOLF
def nuevoArchivo():
	print("¿Cómo se va a llamar archivo?\nMáximo 10 caracteres")
	user_input = input(">> ")

	if len(user_input) < 10:
		if not os.path.exists(user_input):
			f = open(user_input,'w')
			f.close()
		else:
			print("¡El archivo ya existe!")	
	else:
		print("Tu archivo excede los 10 caracteres!")

#Borra una carpeta de WOLF
def eliminarCarpeta():
	print("¿Cómo se llama la carpeta a borrar?")
	user_input = input(">> ")
	path = os.getcwd()

	if os.path.isdir(path+'/'+user_input):
		shutil.rmtree(user_input)

	else:
		print("¡La carpeta no existe!")
		pass

#Borra un archivo de una carpeta de WOLF
def eliminarArchivo():
	print("¿Qué archivo deseas borrar?")
	file = input(">> ")
	os.system("ls | grep "+ file +" > tmp")
	archivo = open("tmp", "r")
	find_file = archivo.readline()
	if len(find_file) > 0:
		os.system("rm -rf " + find_file)
	else:
		print("¡El archivo no existe!")

#Modifica un archivo de WOLF
def editar():
	print("¿Cómo se llama el archivo que quieres modificar? ")
	user_input = input(">> ")
	os.system("ls | grep "+ user_input +" > tmp")
	archivo = open("tmp", "r")
	find_file = archivo.readline()
	if len(find_file) > 0:
		os.system("vi " + find_file)
	else:
		print("¡El archivo no existe!")

#Abre un archivo de solo lectura
def leer():
	print("¿Cómo se llama el archivo que quieres leer?")
	user_input = input(">> ")
	if len(user_input) < 6:
		if os.path.exists(user_input):
			print("El Archivo '"+user_input+"' contiene: ")
			print("====================================")
			os.system("cat " + user_input)
			print("====================================")
		else:
			print("¡El archivo no existe!")	
	else:
		print("Tu achivo tiene más de 6 caracteres!")

#Dirige a una carpeta específica
def ir_a():
	global dentroDe
	print("¿Cómo se llama la carpeta a la que quieres entrar? ")
	user_input = input(">> ")
	os.system("ls | grep "+ user_input +" > tmp")
	archivo = open("tmp", "r")
	find_file = archivo.readline()
	if len(find_file) > 0:
		os.chdir(find_file[:-1])
		dentroDe += 1
	else:
		print("¡La carpeta no existe!")

#Regresa un directorio
def regresar_a():
	global dentroDe
	if dentroDe > 0:
		os.chdir("..")
		dentroDe -= 1
	else:
		print("Imposible, estas en la raíz")

#Enlista los archivos de la carpeta en la que se esta ubicado
def enlistar_archivos():
	os.system("ls --color=always")

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
