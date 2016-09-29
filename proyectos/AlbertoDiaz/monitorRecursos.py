# *-* encoding: utf-8 *-*
import threading
import time
import commands
import os

evento = threading.Semaphore(0)

def obtMem():
	threading.Thread(target=watchMem,args=[]).start()
	return 0


def watchMem():
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

def imprimeMenu():
	global evento
	seleccion = '0'
	while seleccion != '5':
		os.system("clear")
		opciones = {'1':obtMem}
		seleccion = raw_input('Escoge una: \n')
		try:
			resultado = opciones[seleccion]()
			evento.acquire()
		except:
			print("Respuesta no valida")
		print seleccion
imprimeMenu()