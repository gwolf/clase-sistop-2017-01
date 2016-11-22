#Mendoza Colmenares Gerardo
#Segundo proyecto basado en creación de archivos a partir de un zip

#En este cuarto archivo se hará uso de funciones para poner más presentación a la hora de ejecución

#CORRECCIONES
#Ninguna


#!/usr/bin/python
# -*- coding: utf-8 -*-

import os, sys, shutil

def main():
	global ciclo, dentroDe
	ciclo = 0
	dentroDe = 0
	#Con 'grep'  buscamos dentro de los archivos las líneas que concuerdan con un patrón
	os.system("ls | grep WOLF.zip > tmp")
	#Abrimos el archivo tmp en modo lectura
	archivo = open("tmp", "r")
	#Buscamos si existe el zip donde se trabajará y se descomprimirá
	find_zip = archivo.readline()

	if find_zip == "WOLF.zip\n":
		print("¡El zip existe!")
		#Descomprimir zip
		unzip(find_zip)
		#'chdir' para cambiar de directorio de trabajo
		os.chdir("WOLF")
		os.system("clear")
		print("|----------==========----------==========----------|\n\t\t----COMANDOS----")
		print("|----------==========----------==========----------|")
		print("\tnewdir, newfile, removedir, removefile\nedit, read, goin, goback, list-items\nexit, help")
		print("|----------==========----------==========----------|")
		#Mientras no pida salir, la terminal seguirá pidiendo comandos
		while ciclo != 1:
			fuente_normal()
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
#
#----------------------------------------------------------------------------------------------------------------------------

#Fuentes para presentacion en terminal
def fuente_error():
    print (chr(27)+"[1;31m")

def fuente_exito():
    print (chr(27)+"[1;33m"+"¡ÉXITO!")

def fuente_normal():
    print (chr(27)+"[0;37m")

def fuente_pregunta():
	print (chr(27)+"[3;34m")



#Descomprimir el zip existente
def unzip(file_zip):
	#Revisamos si existe el zip
	if len(file_zip) > 0:
		os.system("unzip WOLF.zip")
		fuente_exito()
		print("¡Se descomprimio el zip correctamente!")
	else:
		fuente_error()
		print("No existe el zip WOLF!")

#Verificar que comando se mando a llamar
def comandos(comando):
	#Comprobamos que el comando recibido sea correcto
	if comando == "newdir" or comando == "newfile" or comando == "removefile" or comando == "removedir" or comando == "edit" or comando == "read" or comando == "goin" or comando == "goback" or comando == "list-items" or comando == "exit" or comando == "help":
		return True
	else:
		return False

#Agrega una carpeta a WOLF
def nuevaCarpeta():
	fuente_pregunta()
	print("¿Cómo se va a llamar la carpeta?\nMáximo 12 caracteres")
	user_input = input(">> ")
	#'getcwd' para conocer el directorio actual
	path = os.getcwd()
	#Comprobamos que la longitud permitida sea correcta
	if len(user_input) < 12:
		#Creamos el directorio solicitado con makedirs
		if not os.path.exists(user_input):
			fuente_exito()
			os.makedirs(user_input)
		else:
			fuente_error()
			print("¡La carpeta ya existe!")
	else:
		fuente_error()
		print("¡Tu carpeta excede los 12 caracteres!")

#Agrega un archivo a WOLF
def nuevoArchivo():
	fuente_pregunta()
	print("¿Cómo se va a llamar archivo?\nMáximo 10 caracteres")
	user_input = input(">> ")
	#Comprobamos que la longitud permitida sea correcta
	if len(user_input) < 10:
		#Creamos el archivo solicitado comprobando no exita previamente con 'exists'
		if not os.path.exists(user_input):
			f = open(user_input,'w')
			f.close()
			fuente_exito()
		else:
			fuente_error()
			print("¡El archivo ya existe!")	
	else:
		fuente_error()
		print("¡Tu archivo excede los 10 caracteres!")

#Borra una carpeta de WOLF
def eliminarCarpeta():
	fuente_pregunta()
	print("¿Cómo se llama la carpeta a borrar?")
	user_input = input(">> ")
	#'getcwd' para conocer el directorio actual
	path = os.getcwd()
	#Comprobamos exista la carpeta a borrar
	if os.path.isdir(path+'/'+user_input):
		shutil.rmtree(user_input)
		fuente_exito()
	else:
		fuente_error()
		print("¡La carpeta no existe!")
		#'pass' para seguir adelante sin eejecutar nada
		pass

#Borra un archivo de una carpeta de WOLF
def eliminarArchivo():
	fuente_pregunta()
	print("¿Qué archivo deseas borrar?")
	file = input(">> ")
	#Con 'grep'  buscamos dentro de los archivos las líneas que concuerdan con un patrón
	os.system("ls | grep "+ file +" > tmp")
	archivo = open("tmp", "r")
	#Buscamos el archivo y lo borramos con 'rm'
	find_file = archivo.readline()
	if len(find_file) > 0:
		os.system("rm -rf " + find_file)
		fuente_exito()
	else:
		fuente_error()
		print("¡El archivo no existe!")

#Modifica un archivo de WOLF
def editar():
	fuente_pregunta()
	print("¿Cómo se llama el archivo que quieres modificar? ")
	user_input = input(">> ")
	os.system("ls | grep "+ user_input +" > tmp")
	#Si el archivo existe se editará con 'vi'
	archivo = open("tmp", "r")
	find_file = archivo.readline()
	if len(find_file) > 0:
		os.system("vi " + find_file)
		fuente_exito()
	else:
		fuente_error()
		print("¡El archivo no existe!")

#Abre un archivo de solo lectura
def leer():
	fuente_pregunta()
	print("¿Cómo se llama el archivo que quieres leer?")
	user_input = input(">> ")
	if len(user_input) < 6:
		#Con 'cat' concatenamos archivos para posteriormente desplegarlos en pantalla
		if os.path.exists(user_input):
			fuente_exito()
			print("El Archivo '"+user_input+"' contiene: ")
			print("====================================")
			os.system("cat " + user_input)
			print("====================================")
		else:
			fuente_error()
			print("¡El archivo no existe!")	
	else:
		fuente_error()
		print("Tu achivo tiene más de 6 caracteres!")

#Dirige a una carpeta específica
def ir_a():
	fuente_pregunta()
	global dentroDe
	print("¿Cómo se llama la carpeta a la que quieres entrar? ")
	user_input = input(">> ")
	os.system("ls | grep "+ user_input +" > tmp")
	archivo = open("tmp", "r")
	find_file = archivo.readline()
	if len(find_file) > 0:
		#Buscamos la carpeta a entrar
		os.chdir(find_file[:-1])
		dentroDe += 1
		fuente_exito()
	else:
		fuente_error()
		print("¡La carpeta no existe!")

#Regresa un directorio
def regresar_a():
	fuente_pregunta()
	global dentroDe
	if dentroDe > 0:
		fuente_exito()
		#Regresamos un directorio con '..'
		os.chdir("..")
		dentroDe -= 1
	else:
		fuente_error()
		print("Imposible, estas en la raíz")

#Enlista los archivos de la carpeta en la que se esta ubicado
def enlistar_archivos():
	fuente_exito()
	#Con '--color=always" se colorean aquellos que ya se habían creado anteriormente
	os.system("ls --color=always")

#Imprime lo que cada comando realiza
def ayuda():
	fuente_pregunta()
	return 0

def salir():
	global ciclo
	ciclo = 1

#Diccionario que facilita la llamada a los comandos
diccionarioComandos = {'newdir': nuevaCarpeta, 'newfile': nuevoArchivo, 'removedir':eliminarCarpeta, 'removefile':eliminarArchivo, 'edit':editar,'read':leer, 'goin':ir_a, 'goback':regresar_a, 'list-items':enlistar_archivos, 'help':ayuda, 'exit': salir}

#Llamamos a la funcion para empezar a pedir coomandos
if __name__ == '__main__':
  main()
