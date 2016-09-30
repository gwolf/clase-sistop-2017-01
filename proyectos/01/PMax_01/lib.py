#Objetivo :
#realizar un monitor que despliegue la informacion que le corresponde a cada proceso
import os
import threading
from time import *
global mutex
import sys
#primero se buscan todos los procesos existentes y sus nombres
def monH():
	os.system("cat /proc/sched_debug > ./proc.txt")
	os.system("touch li.txt")
	arch=open("proc.txt","r")
	arch1=open("li.txt","w")
	line=arch.readline()
	line="\tNombre\tPID\ttiem-espera\tsum-exec\tsum-sleep\n"
	arch1.write(line)
	for i in range(4):
		while line!="runnable tasks:\n":
			line=arch.readline()
		line=arch.readline()
		line=arch.readline()
		line=arch.readline()
		while line!="\n":
			line=line[0:24]+line[62:106]+"\n"
			arch1.write(line)
			line=arch.readline()
	line="Presiona q para salir de la visualizacion"
	arch1.write(line)
	arch.close()
	arch1.close()
	os.system("less li.txt")

def monAct():
	os.system("sh monH.sh")
	arch=open("cheat.txt","r")
	arch2=open("procAc.txt","w")
	line=arch.readline()
	cont=1
	aux=""
	for line in arch:
		line=line[0:6]+line[24:len(line)-1]
		# print (line)
		if len(line)<16:
			line+="\t"
		if cont%6==0:
			arch2.write(aux+"\n")
			aux=""
		aux=aux+line+"\t"
		cont+=1
	arch.close()
	arch2.close()
	os.system("cat procAc.txt")
	opcion=input("Quieres cerrar algun proceso?(s/n) ")

	if opcion.lower()=='s':
		opcion=input("Quieres cerrar por pid(identificador de proceso)(p) o nombre(n)(presiona q para cancelar): ")
		if opcion.lower()=='p':
			op=threading.Thread(target=cerrarPr(opcion.lower()))
			op.start()
		elif opcion.lower()=='n':
			op=threading.Thread(target=cerrarPr(opcion.lower()))
			op.start()
	opcion=input("Quieres ver la informacion especifica de algun proceso?(s/n): ")
	if opcion.lower()=='s':
		op=threading.Thread(target=infoEsp)
		op.start()
	op.join()

def cerrarPr(noid):
	pid=input("Cual es el proceso que quieres cerrar?(presiona si quieres cancelar q): ")
	if pid!='q':
		print("\n\nAlgunos procesos estan protegidos por el sistema,")
		print("estos proces suelen ser importantes,  si  quieres")
		print("asegurarte de que cierren, presiona 'a'  (esto,")
		print("funcionara pidiendote la contraseña para privile-")
		print("gios de superusuario (sudo), si no quieres otogar")
		print("estos privilegios presiona cualquier tecla)(para ") 
		opcion=input("cancelar presiona q): ")
		k="kill"
		if noid=='n':
			k="p"+k
		if opcion=='a':
			exito=os.system("su -c '"+k+" "+pid+"'")
		elif opcion!='q':
			exito=os.system(k+" "+pid)
		if exito==0:
			print("Se cerro el proceso exitosamente")
		else:
			print("El proceso no existe ")
		pid=input("Presiona enter para continuar")

def infoEsp():

	pid=input("Dame el pid del proceso(es probable que alguno proceso ya no existan): ")
	ex=os.system("cat /proc/"+pid+"/status > tem.txt")
	if ex==0:
		os.system("touch info.txt")
		arch=open("tem.txt","r")
		arch2=open("info.txt","w")
		for line in arch:
			if line[0:4]=="Name":
				arch2.write("Nombre:\t"+line[5:len(line)])
			elif line[0:5]=="State":
				arch2.write("Estado:\t"+line[6:len(line)])
			elif line[0:3]=="Pid":
				arch2.write("Pid:\t"+line[5:len(line)])
			elif line[0:7]=="Threads":
				arch2.write("Hilos:\t"+line[9:len(line)])
			elif line[0:9]=="voluntary":
				arch2.write("Cambios voluntarios de contexto: "+line[25:len(line)])
			elif line[0:12]=="nonvoluntary":
				arch2.write("Cambios involuntarios de contexto: "+line[28:len(line)])
		arch.close()
		arch2.write("comando: ")
		arch2.close()
		os.system("cat /proc/"+pid+"/cmdline >> info.txt")
		arch2=open("info.txt","a")
		arch2.write("\nlimites:\n")
		arch2.close()
		os.system("cat /proc/"+pid+"/limits >> info.txt")
		opcion=input("Deseas informacion sobre cuales son la condiciones de entorno?(su)(s/n): ")
		if opcion=='s':
			arch2=open("info.txt","a")
			arch2.write("\nEntorno: ")
			arch2.close()
			os.system("su -c 'cat /proc/'"+pid+"/environ >> info.txt")
		opcion=input("Deseas informacion sobre la entrada y salida del programa?(su)(s/n): ")
		if opcion=='s':
			arch2=open("info.txt","a")
			arch2.write("\n\nIO: ")
			arch2.close()
			os.system("su -c 'cat /proc/'"+pid+"/io >> info.txt")
		arch2.close()
		print("\nINFO DEL PROCESO "+pid+"\n")
		os.system("cat info.txt")	
	else:
		print("Ocurrio un error, no existe ese proceso")
	opcion=input("\nPresiona enter para continuar: ")

def actualizar():
	os.system("ls /proc > temp.txt")
	arch1=open("temp.txt","r")

	global lista
	lista=[]
	aux=arch1.readline()

	while ord(aux[0])>47 and ord(aux[0])<58:
		lista.append(int(aux[0:len(aux)-1]))
		aux=arch1.readline()
	lista.sort()
	t=[]#hilos
	# print (lista)
	global semp
	os.system("rm TR.txt")
	os.system("touch TR.txt")
	os.system("echo 'pid    nombre\t\t\testado   cambios voluntarios   cambios involuntarios  cantidad de memoria en uso  VmSwap' >TR.txt ")
	semp=threading.Semaphore(1)
	padre=threading.Thread(target=lanzarHilos)
	padre.start()
	padre.join()
	os.system("cat TR.txt")

def obtenerDatos(pid):
	cond=True
	while cond:
		semp.acquire()
		if pid==lista[0]:
			aux=info(lista.pop(0))
			# os.system("echo '"+aux+"' >> TR.txt")
			sys.stdout.write(aux)
			if (len(lista)%2==0):
				sys.stdout.write("\n")
			cond=False
		semp.release()


def lanzarHilos():
	t=[]
	for i in lista:
		t.append(threading.Thread(target=obtenerDatos, args=[i]))
	for i in t:
		i.start()
		i.join()

def info(pid):
	ret=str(pid)
	while (len(ret)<5):
		ret+=" "
	os.system("cat /proc/"+str(pid)+"/comm > temp.txt")
	arch=open("temp.txt","r")
	aux=arch.readline()
	aux=aux[0:len(aux)-1]
	while (len(aux)<15):
		aux+=" "
	ret=ret+"  "+aux
	arch.close()	
	os.system("(cat /proc/"+str(pid)+"/status | grep State; cat /proc/"+str(pid)+"/status | grep 'volunta'; cat /proc/"+str(pid)+"/status | grep VmS) > temp.txt")
	arch=open("temp.txt","r")
	aux=arch.readline()
	
	ret+=aux[9:len(aux)-1]
	while (len(ret)<35):
		ret +=" "
	aux=arch.readline()
	ret+=aux[25:len(aux)-1]
	while (len(ret)<48):
		ret +=" "
	aux=arch.readline()
	ret+=aux[28:len(aux)-1]
	while (len(ret)<58):
		ret +=" "
	aux=arch.readline()
	ret+=aux[8:len(aux)-1]
	while (len(ret)<68):
		ret +=" "
	aux=arch.readline()
	aux=arch.readline()
	ret+=aux[8:len(aux)-1]+" "
	while (len(ret)<84):
		ret +=" "
	arch.close()
	return ret

def refresh():
	while opcion:
		os.system("clear")
		actualizar()
		print("presiona f para salir (puede tardar en salir)")
		sleep(15)
def infoTR():
	global opcion
	opcion=True
	hilo=threading.Thread(target=refresh)
	hilo.start()
	while opcion:
		opcion=input("")
		if opcion=='f':	
			opcion=False
	hilo.join()

