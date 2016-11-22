#Mendoza Colmenares Gerardo
#Segundo proyecto basado en creación de archivos a partir de un zip

#En este último archivo se finaliza cambiando palabras claves de comandos y poniendo ayuda para quien use este .py
#además de agregar 'if' que distingan archivos de carpetas

#CORRECCIONES
#Agregar ayuda y cambiar palabras claves, ademas de dar un formato más presentable y diferenciar entre carpetas y archivos


#!/usr/bin/python
# -*- coding: utf-8 -*-

import os, sys, shutil

def main():
	global ciclo, dentroDe
	ciclo = 0
	dentroDe = 0
	#Con 'grep'  buscamos dentro de los archivos las líneas que concuerdan con un patrón
	os.system("ls | grep WOLF.zip > temporal")
	#Abrimos el archivo temporal en modo lectura
	archivo = open("temporal", "r")
	#Buscamos si existe el zip donde se trabajará y se descomprimirá
	find_zip = archivo.readline()

	if find_zip == "WOLF.zip\n":
		print("¡El zip existe!")
		#Descomprimir zip
		unzip(find_zip)
		#'chdir' para cambiar de directorio de trabajo
		os.chdir("WOLF")
		os.system("clear")
		muestra_comandos()
		#Mientras no pida salir, la terminal seguirá pidiendo comandos
		while ciclo != 1:
			fuente_normal()
			comando = input("root@fi_unam$ ")
			if comandos(comando):
				diccionarioComandos[comando]()
			else:
				fuente_error()
				print("¡Comando invalido!")
				print("Escribe 'ayuda' para saber mas acerca de los comandos")

		#rm -rf temporal usado para borrar y '..' para regresar un directorio, comprimimos la carpeta de nuevo y borramos la
		#versión de la carpeta 'WOLF' pasada
		os.system("rm -rf temporal")
		os.chdir("..")
		os.system("zip -r WOLF.zip WOLF")
		os.system("rm -rf WOLF")
		os.system("clear")
		fuente_aceptado()
		print("¡Hasta la proxima!")
	else:
		fuente_error()
		print("¡Archivo no encontrado!\nPor favor cree el archivo que se especifíca en la documentación")


#Fuentes para presentacion en terminal
def fuente_error():
    print (chr(27)+"[1;31m")

def fuente_exito():
    print (chr(27)+"[1;33m"+"¡ÉXITO!")

def fuente_aceptado():
    print (chr(27)+"[1;33m")

def fuente_normal():
    print (chr(27)+"[0;37m")

def fuente_pregunta():
	print (chr(27)+"[3;34m")

def muestra_comandos():
	fuente_normal()
	print("|----------==========----------==========----------|\n\t----COMANDOS DISPONIBLES----")
	print("|----------==========----------==========----------|")
	print("\t<CREACIÓN >> nuevaCarp, nuevoArch\n\t<<BORRADO>> elimCarp, elimArch")
	print("\t<<OTROS>> editar, leer\n\t<<DIRECTORIOS>> ir, regresar, enlistar\n\t<<MAS>> limpiar, ayuda, salir")
	print("|----------==========----------==========----------|")

#Descomprimir el zip existente
def unzip(file_zip):
	#Revisamos si existe el zip
	if len(file_zip) > 0:
		os.system("unzip WOLF.zip")
		fuente_exito()
		print("¡Se descomprimio el zip correctamente!")
	else:
		fuente_error()
		print("¡No existe el zip WOLF!")

#Verificar que comando se mando a llamar
def comandos(comando):
	#Comprobamos que el comando recibido sea correcto
	if comando in diccionarioComandos :
		return True

#Agrega una carpeta a WOLF
def nuevaCarpeta():
	fuente_pregunta()
	print("¿Cómo se va a llamar la carpeta?\nMáximo 12 caracteres")
	palabra = input(">> ")
	#'getcwd' para conocer el directorio actual
	path = os.getcwd()
	#Comprobamos que la longitud permitida sea correcta
	if len(palabra) < 12:
		#Creamos el directorio solicitado con makedirs
		if not os.path.exists(palabra):
			fuente_exito()
			os.makedirs(palabra)
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
	palabra = input(">> ")
	#Comprobamos que la longitud permitida sea correcta
	if len(palabra) < 10:
		#Creamos el archivo solicitado comprobando no exita previamente con 'exists'
		if not os.path.exists(palabra):
			f = open(palabra,'w')
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
	palabra = input(">> ")
	#'getcwd' para conocer el directorio actual
	path = os.getcwd()
	#Comprobamos exista la carpeta a borrar
	if os.path.isdir(path+'/'+palabra):
		os.system("rm -rf "+ palabra)
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
	os.system("ls | grep "+ file +" > temporal")
	archivo = open("temporal", "r")
	#Buscamos el archivo y lo borramos con 'rm'
	find_file = archivo.readline()
	if len(find_file) > 0:
		os.system("rm " + find_file)
		fuente_exito()
	else:
		fuente_error()
		print("¡El archivo no existe!")

#Modifica un archivo de WOLF
def editar():
	fuente_pregunta()
	print("¿Cómo se llama el archivo que quieres modificar? ")
	palabra = input(">> ")
	os.system("ls | grep "+ palabra +" > temporal")
	#Si el archivo existe se editará con 'nano'
	archivo = open("temporal", "r")
	find_file = archivo.readline()
	if os.path.isfile(palabra):
		if len(find_file) > 0:
			os.system("nano " + find_file)
			fuente_aceptado()
		else:
			fuente_error()
			print("¡El archivo no existe!")
	else:
		fuente_error()
		print("¡No se puede editar una carpeta!")

#Abre un archivo de solo lectura
def leer():
	fuente_pregunta()
	print("¿Cómo se llama el archivo que quieres leer?")
	palabra = input(">> ")
	if os.path.isfile(palabra):
		if len(palabra) < 10:
			#Con 'cat' concatenamos archivos para posteriormente desplegarlos en pantalla
			if os.path.exists(palabra):
				fuente_aceptado()
				print("El Archivo '"+palabra+"' contiene: ")
				print("------------------------------------------------------------------------")
				os.system("more " + palabra)
				print("------------------------------------------------------------------------")
			else:
				fuente_error()
				print("¡El archivo no existe!")	
		else:
			fuente_error()
			print("Tu achivo tiene más de 10 caracteres!")
	else:
		if os.path.isdir(palabra):
			fuente_error()
			print(palabra + " no es un archivo, sin embargo la carpeta contiene:")
			fuente_aceptado()
			os.system("ls "+ palabra)
		else:
			fuente_error()
			print("¡El archivo no exite!")

#Dirige a una carpeta específica
def ir_a():
	fuente_pregunta()
	global dentroDe
	print("¿Cómo se llama la carpeta a la que quieres entrar? ")
	palabra = input(">> ")
	os.system("ls | grep "+ palabra +" > temporal")
	archivo = open("temporal", "r")
	find_file = archivo.readline()
	if len(find_file) > 0:
		#Buscamos la carpeta a entrar
		os.chdir(find_file[:-1])
		dentroDe += 1
		fuente_aceptado()
		print("Estas dentro de '"+palabra+"'")
	else:
		fuente_error()
		print("¡La carpeta no existe!")

#Regresa un directorio
def regresar_a():
	fuente_pregunta()
	global dentroDe
	if dentroDe > 0:
		fuente_exito()
		print("Regresaste a ")
		#Regresamos un directorio con '..'
		os.chdir("..")
		os.system("pwd")
		dentroDe -= 1
	else:
		fuente_error()
		print("Imposible, estas en la raíz")

#Enlista los archivos de la carpeta en la que se esta ubicado
def enlistar_archivos():
	fuente_aceptado()
	#Con '--color=always" se diferencian las carpetas de los archivos
	os.system("ls --color=always")

#Imprime lo que cada comando realiza
def ayuda():
	fuente_pregunta()
	print("==========================================================================================================")
	print(">> nuevaCarp: Crea una nueva carpeta dentro de la carpeta actual")
	print(">> nuevaArch: Crea un nuevo archivo dentro de al carpeta actual")
	print(">> ellimCarp: Borra una carpeta existente")
	print(">> alimArch: Borra un archivo existente")
	print(">> editar: Edita un archivo con 'nano'")
	print(">> ir: Permite entrar a una carpeta")
	print(">> regresar: Permite salir de la carpeta actual a la carpeta anterior, estando en raíz no hará nada")
	print(">> enlistar: Despliega las carpetas y archivos existentes")
	print(">> leer: Despliega el contenido de un archivo existente")
	print(">> limpiar: Limpia pantalla para mostrar nuevamente los comandos disponibles")
	print(">> ayuda: Despliega detalles de los comandos existentes")
	print(">> salir: Salida del programa")
	print("==========================================================================================================")

def limpiar():
	os.system("clear")
	muestra_comandos()

def salir():
	global ciclo
	ciclo = 1

#Diccionario que facilita la llamada a los comandos
diccionarioComandos = {'nuevaCarp': nuevaCarpeta, 'nuevoArch': nuevoArchivo, 'elimCarp':eliminarCarpeta, 'elimArch':eliminarArchivo, 'editar':editar,'leer':leer, 'ir':ir_a, 'regresar':regresar_a, 'enlistar':enlistar_archivos, 'ayuda':ayuda, 'limpiar': limpiar, 'salir': salir}

#Llamamos a la funcion para empezar a pedir coomandos
if __name__ == '__main__':
  main()
