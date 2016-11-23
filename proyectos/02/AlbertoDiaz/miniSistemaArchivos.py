#!/usr/bin/python3
# -*- Encoding: utf-8 -*-
#Nombre: Carlos Alberto Díaz Olivares

import os.path


def existeDirectorio(nombreDirectorio):
	if os.path.exists(nombreDirectorio):
		return True
	else:
		return False

def crearDirectorio(nombreDirectorio):
	if existeDirectorio(nombreDirectorio):
		return False
	else:
		return open(nombreDirectorio,"a+")

def crearArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre):
	if len(nombreArchivo) == 0:
		return False
	directorioActual =  open(nombreDirectorio,"r+")
	if len(nombreArchivo)>20:
		print("El nombre de archivo sobrepasa los 20 caracteres")
		return False
	else:
		if len(fin_nombre)>0:
			if str(buscarArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre)) != 'False':
				print("El nombre de archivo ya existe")
				return False
		directorioActual.seek(inicio_nombre[len(inicio_nombre)-1])
		print("Aqui empieza "+ str(directorioActual.tell()))
		directorioActual.write(nombreArchivo)
		print("Aqui termina "+ str(directorioActual.tell()))
		fin_nombre.append(directorioActual.tell())
		inicio_nombre.append(inicio_nombre[len(inicio_nombre)-1]+71)
		inicio_archivo.append(inicio_nombre[len(inicio_nombre)-2]+21)
		directorioActual.close()
		return directorioActual

def listarArchivos(nombreDirectorio,inicio_nombre,fin_nombre):
	directorioActual =  open(nombreDirectorio,"r+")
	if len(fin_nombre)>0:
		for x in range(len(inicio_nombre)-1):
			directorioActual.seek(inicio_nombre[x])
			nombre = directorioActual.read(fin_nombre[x]-inicio_nombre[x])
			print (nombre)
	else:
		print("No hay archivos para listar")
	directorioActual.close()

def buscarArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre):
	directorioActual =  open(nombreDirectorio,"r+")
	if len(fin_nombre)>0:
		for x in range(len(inicio_nombre)-1):
			directorioActual.seek(inicio_nombre[x])
			nombre = directorioActual.read(fin_nombre[x]-inicio_nombre[x])
			if nombre == nombreArchivo:
				directorioActual.close()
				return x
		directorioActual.close()
		return False
	else:
		directorioActual.close()
		return False


def borrarArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre):
	directorioActual =  open(nombreDirectorio,"r+")
	if len(fin_nombre)>0:
		posicion = buscarArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre)
		if(str(posicion)=='False'):
			print("Error el archivo no existe")
			directorioActual.close()
			return
		else:
			del inicio_nombre[posicion]
			del fin_nombre[posicion]
	else:
		print("El archivo no existe")
	directorioActual.close()
	return
def escribirArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre,inicio_archivo,fin_archivo,cadena):
	directorioActual =  open(nombreDirectorio,"r+")
	if len(fin_nombre)>0:
		posicion = buscarArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre)
		if(str(posicion)=='False'):
			print("Error el archivo no existe")
			directorioActual.close()
			return
		else:
			directorioActual.seek(inicio_archivo[posicion])
			directorioActual.write(cadena)
			fin_archivo.append(directorioActual.tell())
			directorioActual.close()
			return
	else:
		print("El archivo no existe")
	directorioActual.close()
	return
def leerArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre,inicio_archivo,fin_archivo):
	directorioActual =  open(nombreDirectorio,"r+")
	if len(fin_nombre)>0:
		posicion = buscarArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre)
		if(str(posicion)=='False'):
			print("Error el archivo no existe")
			directorioActual.close()
			return
		else:
			if(len(inicio_archivo) > len(fin_archivo)):
				fin_archivo.append(inicio_archivo[posicion])
			directorioActual.seek(inicio_archivo[posicion])
			lectura = directorioActual.read(fin_archivo[posicion]-inicio_archivo[posicion])
			directorioActual.close()
			return lectura
	else:
		print("El archivo no existe")
	directorioActual.close()
	return
def concatenarArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre,inicio_archivo,fin_archivo,cadena):
	directorioActual =  open(nombreDirectorio,"r+")
	if len(fin_nombre)>0:
		posicion = buscarArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre)
		if(str(posicion)=='False'):
			print("Error el archivo no existe")
			directorioActual.close()
			return
		else:
			if(len(inicio_archivo) > len(fin_archivo)):
				fin_archivo.append(inicio_archivo[posicion])
			directorioActual.seek(fin_archivo[posicion])
			directorioActual.write(cadena)
			fin_archivo[posicion] = directorioActual.tell()
			directorioActual.close()
			return
	else:
		print("El archivo no existe")
	directorioActual.close()
	return


inicio_nombre=[]
fin_nombre=[]

inicio_archivo=[]
fin_archivo=[]



nombreDirectorio=input("Escribe el nombre del nuevo directorio")+".dat"
directorioActual = crearDirectorio(nombreDirectorio)


if  directorioActual == False:
	print ("Error el directorio ya existe")
else:
	inicio_nombre.append(directorioActual.tell())
	directorioActual.close()

opcion = True
while opcion != False:
	for x in inicio_nombre:
		print("in")
		print(x)
	for x in fin_nombre:
		print("fn")
		print(x)
	for x in inicio_archivo:
		print("ia")
		print(x)
	for x in fin_archivo:
		print("fa")
		print(x)
	print("Escoge una opcion\n  1.-Crear un archivo\n  2.-Escribir Archivo\n  3.- Leer Archivo\n  4.-Concatenar en archivo\n  5.- Borrar Archivo\n  6.-Listar Archivos del Directorio")
	opcion = input()
	if(opcion == '1'):
		nombre=input("Escribe el nombre del nuevo archivo")
		directorioActual = crearArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre)
	elif(opcion == '2'):
		nombre=input("Escribe el nombre del archivo")
		cadena=input("Escribe la cadena a escribir en el archivo(Cualquier dato en el archivo se sobreescribira)")
		escribirArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre,inicio_archivo,fin_archivo,cadena)
	elif(opcion == '3'):
		nombre=input("Escribe el nombre del archivo")
		lectura = leerArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre,inicio_archivo,fin_archivo)
		print(lectura)
	elif(opcion == '4'):
		nombre=input("Escribe el nombre del archivo")
		cadena=input("Escribe la cadena a escribir en el archivo")
		concatenarArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre,inicio_archivo,fin_archivo,cadena)
	elif(opcion == '5'):
		nombre=input("Escribe el nombre del archivo")
		borrarArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre)
	elif(opcion == '6'):
		listarArchivos(nombreDirectorio,inicio_nombre,fin_nombre)
	elif(opcion == '7'):
		opcion = False
	else:
		print("Opcion Invalida")


"""listarArchivos(nombreDirectorio,inicio_nombre,fin_nombre)
for i in range(5):
	nombre=input("Escribe el nombre del nuevo archivo")
	archivo.write(nombre)
	fin_nombre.append(archivo.tell())
	inicio_nombre.append(archivo.tell())
	directorioActual = crearArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre)
listarArchivos(nombreDirectorio,inicio_nombre,fin_nombre)
nombre=input("Escribe el nombre del nuevo archivo")
borrarArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre)
listarArchivos(nombreDirectorio,inicio_nombre,fin_nombre)
"""


