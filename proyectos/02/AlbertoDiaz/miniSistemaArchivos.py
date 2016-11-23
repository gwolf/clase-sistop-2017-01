#!/usr/bin/python3
# -*- Encoding: utf-8 -*-
#Nombre: Carlos Alberto Díaz Olivares
#Proyecto: MiniSistemaArchivos

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
		if len(fin_nombre)>0:#Verifica que si ya existen archivos
			if str(buscarArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre)) != 'False':
				print("El nombre de archivo ya existe")
				return False
		directorioActual.seek(inicio_nombre[len(inicio_nombre)-1])#Posicionar el cursor en donde empieza el espacio de nombre
		#print("Aqui empieza "+ str(directorioActual.tell())) Para saber en que posicion empieza el nombre
		directorioActual.write(nombreArchivo)
		#print("Aqui termina "+ str(directorioActual.tell())) Para saber en que posicion se termina el nombre
		fin_nombre.append(directorioActual.tell())#Guarda la posicion del nombre
		inicio_nombre.append(inicio_nombre[len(inicio_nombre)-1]+71) #Guarda la posicion del siguiente inicio de nombre
		inicio_archivo.append(inicio_nombre[len(inicio_nombre)-2]+21) #Guarda la posicion de inicio del contenido del archivo que acabamos de nombrar
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
	if(len(cadena) > 50):
		print("La cadena sobrepasa el tamaño maximo del archivo")
		return
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
	lectura = leerArchivo(nombreDirectorio,nombreArchivo,inicio_nombre,fin_nombre,inicio_archivo,fin_archivo)
	if(len(cadena)+len(lectura) > 50):
		print("Se sobrepasa el tamaño maximo del archivo")
		return
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


inicio_nombre=[] #Lista para guardar posiciones de inicio de nombre
fin_nombre=[] #Lista para guardar posiciones de fin de nombre

inicio_archivo=[] #Lista para guardar posiciones de inicio de contenido
fin_archivo=[] #Lista para guardar posiciones de fin de contenido


existe = True
while existe == True:
	nombreDirectorio=input("Escribe el nombre del nuevo directorio")+".dat"
	existe = existeDirectorio(nombreDirectorio)
	directorioActual = crearDirectorio(nombreDirectorio)
	if  directorioActual == False:
		print ("Error el directorio ya existe")
	else:
		inicio_nombre.append(directorioActual.tell())
		directorioActual.close()

opcion = True
while opcion != False:
	print("Escoge una opcion\n  1.-Crear un archivo\n  2.-Escribir Archivo\n  3.- Leer Archivo\n  4.-Concatenar en archivo\n  5.- Borrar Archivo\n  6.-Listar Archivos del Directorio\n  7.-Salir")
	opcion = input()
	if(opcion == '1'):
		nombre=input("Escribe el nombre del nuevo archivo\n")
		directorioActual = crearArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre)
	elif(opcion == '2'):
		nombre=input("Escribe el nombre del archivo\n")
		cadena=input("Escribe la cadena a escribir en el archivo(Cualquier dato en el archivo se sobreescribira)\n")
		escribirArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre,inicio_archivo,fin_archivo,cadena)
	elif(opcion == '3'):
		nombre=input("Escribe el nombre del archivo\n")
		lectura = leerArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre,inicio_archivo,fin_archivo)
		print(lectura)
	elif(opcion == '4'):
		nombre=input("Escribe el nombre del archivo\n")
		cadena=input("Escribe la cadena a escribir en el archivo\n")
		concatenarArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre,inicio_archivo,fin_archivo,cadena)
	elif(opcion == '5'):
		nombre=input("Escribe el nombre del archivo\n")
		borrarArchivo(nombreDirectorio,nombre,inicio_nombre,fin_nombre)
	elif(opcion == '6'):
		listarArchivos(nombreDirectorio,inicio_nombre,fin_nombre)
	elif(opcion == '7'):
		opcion = False
	else:
		print("Opcion Invalida\n")




