# *-* encoding: utf-8 *-*
import threading
import time
import commands
import os

evento = threading.Semaphore(0)

def obtMem():
	threading.Thread(target=watchMem,args=[]).start()
	return 0


def hiloMem():
	contador = 0
	temp = 0
	while contador <= 10:
		os.system("clear")
		#os.system("cat /proc/meminfo")
		swapTotal=commands.getoutput('cat /proc/meminfo|grep "SwapTotal:"|tr -s "'" "'"|cut -d "'" "'" -f 2')
		swapFree=commands.getoutput('cat /proc/meminfo|grep "SwapFree:"|tr -s "'" "'"|cut -d "'" "'" -f 2')
		memTotal=commands.getoutput('cat /proc/meminfo|grep "MemTotal:"|tr -s "'" "'"|cut -d "'" "'" -f 2')
		memFree=commands.getoutput('cat /proc/meminfo|grep "MemFree:"|tr -s "'" "'"|cut -d "'" "'" -f 2')
		temp = int(memTotal)/1024
		memTotal = str(temp)
		temp = int(memFree)/1024
		memFree = str(temp)
		temp = int(swapTotal)/1024
		memOcu = str(int(memTotal) - int(memFree))
		swapTotal = str(temp)
		temp = int(swapFree)/1024
		swapFree = str(temp)
		print "Memoria Total " + memTotal + " MB \n"
		print "Memoria Libre " + memFree + " MB \n"
		print "Memoria Ocupada " + memOcu + " MB \n"
		print "Swap Total: " + swapTotal + " MB \n"
		print "Swap Libre: " + swapFree + " MB \n"
		time.sleep(1)
		contador+=1
	evento.release()
	return 0

def hiloVersion():
	threading.Thread(target=watchVersion,args=[]).start()
	return 0

def watchVersion():
	contador = 0
	version = commands.getoutput('cat /proc/version')
	while contador <= 10:
		os.system("clear")
		print version
		time.sleep(1)
		contador+=1
	evento.release()
	return 0

def hiloProc():
	threading.Thread(target=watchProc,args=[]).start()
	return 0

def watchProc():
	contador = 0
	numProc = commands.getoutput("grep processor /proc/cpuinfo | wc -l")
	numNucleos = commands.getoutput("cat /proc/cpuinfo | grep \"cpu cores\"")
	modelo = commands.getoutput("cat /proc/cpuinfo | grep \"model name\"")
	while contador <= 10:
		os.system("clear")
		print "Numero de Procesadores : " + numProc
		print numNucleos
		print modelo
		time.sleep(1)
		contador+=1
	evento.release()
	return 0
def Menu():
	global evento
	seleccion = '0'
	while seleccion != '4':
		os.system("clear")
		opciones = {'1':hiloMem,'2':hiloVersion,'3':hiloProc}
		print "Escoge una de las siguientes opciones:\n1.- Obtener informacion sobre RAM Y SWAP\n2.- Obtener informacion sobre la version de linux."
		print "3.- Informacion sobre el procesador(Numero de Procesadores, Numero de Nucleos, Modelo del Procesador)\n4.Salir"
		seleccion = raw_input('\nEscribe tu opcion: \n')
		try:
			resultado = opciones[seleccion]()
			evento.acquire()
		except:
			if seleccion != '4':
				print("Respuesta no valida")
		#print seleccion
Menu()