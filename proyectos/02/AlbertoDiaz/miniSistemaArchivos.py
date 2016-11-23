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
			for x in range(len(inicio_nombre)-1):
				print (x)
				directorioActual.seek(inicio_nombre[x])
				nombre = directorioActual.read(fin_nombre[x]-inicio_nombre[x])
				if nombre == nombreArchivo:
					print("El nombre de archivo ya existe")
					return False
		directorioActual.seek(inicio_nombre[len(inicio_nombre)-1])
		print("Aqui empieza "+ str(directorioActual.tell()))
		directorioActual.write(nombreArchivo)
		print("Aqui termina "+ str(directorioActual.tell()))
		fin_nombre.append(directorioActual.tell())
		inicio_nombre.append(inicio_nombre[len(inicio_nombre)-1]+50)
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
listarArchivos(nombreDirectorio,inicio_nombre,fin_nombre)
for i in range(5):
	nombre=input("Escribe el nombre del nuevo archivo")
	"""archivo.write(nombre)
	fin_nombre.append(archivo.tell())
	inicio_nombre.append(archivo.tell())"""
	directorioActual = crearArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre)
listarArchivos(nombreDirectorio,inicio_nombre,fin_nombre)
for x in inicio_nombre:
	print(x)
for x in fin_nombre:
	print(x)

