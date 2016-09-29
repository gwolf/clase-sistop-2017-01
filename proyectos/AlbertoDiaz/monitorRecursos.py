# *-* encoding: utf-8 *-*
import threading
import time
import commands
import os

torniquete = threading.Semaphore(0)

def obtMem():
	threading.Thread(target=watchMem,args=[]).start()
def watchMem():
	os.system("watch free -m")
seleccion = 2
while seleccion != 0:
	opciones = {'1':obtMem}
	seleccion = raw_input('Escoge una: \n')
	try:
		resultado = opciones[seleccion]()
	except:
		print("Respuesta no valida")
