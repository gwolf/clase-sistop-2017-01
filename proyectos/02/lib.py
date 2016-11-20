#esta es la biblioteca del micro sistema
import os
def impPresentacion():
	print("Micro sistema de archivos SanPer, creado por Max Armando Sanchez Hernandez y Perez Martinez David Antonio ")
	print("Escriba help para ayuda ")

def lsd(comando):
	try:
		tablaDeArch=open(".tablaDeArchivos.tbl","r")
	except IOError:
		crearReq(0)
		tablaDeArch=open(".tablaDeArchivos.tbl","r")
	for line in tablaDeArch:
		if line[0]!="#" and line[0]!="$":
			aux=line.split("\t")
			print(aux[0]+"\t")
	tablaDeArch.close()

def add(comando):
	cmd=comando.split(" ")
	# if tienePico(cmd):
	# 	archivoDestino=cmd[-1]
	# 	if len(archivoDestino)>50:
	# 		print("Nombre de archivo demasiado grande")
	# 		return False
	# 	else:
	# 		contenido=""
	# 		for i in range(1,len(cmd)-1):
	# 			if cmd[i]!=">>" and cmd[i]!=">":
	# 				contenido+=cmd[i]
	# 			else:
	# 				break
	# 		dr=buscar(archivoDestino)
	# 		if dr


def new(comando):
	arch=comando[1]
	if buscar(arch)!=-1:
		print("error archivo encontrado")
		return False
	try:
		archivos=open(".archivos.file","r")
	except IOError:
		crearReq(1)
		archivos=open(".archivos.file","r")
	for i in archivos:
		pass
	ultima=archivos.tell()
	archivos.close()
	try:
		tabla=open(".tablaDeArchivos.tbl","a")
	except IOError:
		crearReq(0)
		tabla=open(".tablaDeArchivos.tbl","a")
	tabla.write("\n"+comando[1]+"\t"+str(ultima)+"\t0")
	tabla.close()
	archivos=open(".archivos.file","a")
	archivos.write(" \EOF 0")
	print (ultima)


def dele(comando):
	#esta funcion pone un caracter de borrado en la tabla
	#de archivos para marcarlo como borrado
	try:
		tabla=open(".tablaDeArchivos.tbl","r")
	except IOError:
		crearReq(0)
		tabla=open(".tablaDeArchivos.tbl","r")
	diraux=-1 #la direccion auxiliar se pone en -1
	cont=0 #el contador de direcciones se pone en 0
	for linea in tabla:
		cont+=len(linea) # se aumenta el contador cada linea
		if linea[0]!="#" and linea[0]!="$":#caracteres de omision
			aux=linea.split("\t")
			if aux[0]==comando[1]:#se verifica el nombre
				diraux=cont-len(linea)+1#se guarda la direccion
				break
	tabla.close()
	if diraux!=-1:#si lo encontro lo cambia
		tabla=open(".tablaDeArchivos.tbl","r+")
		tabla.seek(diraux)
		tabla.write("#")#se inserta este caracter
		tabla.close()

def cat(comando):#muestra el contenido de un archivo
	archivo=comando[1]
	dr=buscar(archivo)
	if dr==-1:
		print("Error archivo no encontrado")
		return False
	else:
		try:
			archivos=open(".archivos.file","r")
		except IOError:
			crearReq(1)
			archivos=open(".archivos.file","r")
		while dr[0]!="\\EOF":
			archivos.seek(int(dr[0]))
			print(archivos.read(int(dr[1])))
			dr=archivos.readline().split(" ")[0:2]#limite de tamano por parte 10**5
		archivos.close()

def hel(comando):
	os.system("cat help.txt")
	print("\n")

def crearReq(tipoError):
	if tipoError==0:
		cad="#esto es un comentario la tabla de archivos tiene 5 columnas\n#nombre		direccion	tamaño 		borrable\n"
		os.system("echo "+cad+" > .tablaDeArchivos.tbl")
	else:
		os.system("touch .archivos.file")
	# Esta funcion sirve para crear todos los requerimientos
	# antes de que otra funcion quiera operar


def tienePico(cmd):
	for i in cmd:
		if i==">>" or ">":
			return True
	return False

def buscar(archivo):
	#esta funcion busca un archivo en la tabla de
	#archivos y regresa su direccion en el archivo
	#de archivos, si no lo encuentra regresa -1
	try:
		tabla=open(".tablaDeArchivos.tbl","r")
	except IOError:
		crearReq(0)
		tabla=open(".tablaDeArchivos.tbl","r")
	for line in tabla:
		if line[0]!="#" and line[0]!="$":
			aux=line.split("\t")
			if aux[0]==archivo:
				tabla.close()
				return [aux[1],aux[2]]
	tabla.close()
	return -1

def buscarborrado():
	#esta funcion encuentra un archivo borrado para ser sustituido
	try:
		tabla=open(".tablaDeArchivos.tbl","r")
	except IOError:
		crearReq(0)
		tabla=open(".tablaDeArchivos.tbl","r")
	for line in tabla:
		if line[0]=="#":
			aux=tabla.tell()-len(line)
			tabla.close()
			return aux
	tabla.close()
	return -1
