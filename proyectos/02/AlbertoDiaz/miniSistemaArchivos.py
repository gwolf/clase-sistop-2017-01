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

nombre=input("Escribe el nombre del nuevo archivo")
"""archivo.write(nombre)
fin_nombre.append(archivo.tell())
inicio_nombre.append(archivo.tell())"""
crearArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre)
nombre=input("Escribe el nombre del nuevo archivo")
crearArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre)
archivo= open(nombreDirectorio,"r+")
archivo.seek(inicio_nombre[0])
print(archivo.read(fin_nombre[0]-inicio_nombre[0]))
archivo.seek(inicio_nombre[1])
print(archivo.read(fin_nombre[1]-inicio_nombre[1]))
for x in inicio_nombre:
	print(x)
for x in fin_nombre:
	print(x)
archivo.seek(0)
print(archivo.read(8))
