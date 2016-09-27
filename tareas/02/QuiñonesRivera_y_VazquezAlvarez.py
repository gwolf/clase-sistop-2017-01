#
# *-* Encoding: utf-8 *-*
#
# Problema: El Cruce del Río.
#
# Autores:
#	Quiñones Rivera Josué Emanuel.
#	Vázquez Álvarez Ángel Eduardo.
#
# Posibilidades:
# 4 hackers o 4 serfs o 2 hackers y 2 serfs.

import threading
import random
import time

global hackers				# Contador para hackers
global serfs				# Contador para serfs

proteccionContadores = threading.Semaphore(1)	# Proteccion para los contadores 
mutex = threading.Semaphore(1)	# Mutex para incrementar contador de hackers/serfs

colaHackers = threading.Semaphore(0) #Cola para controlar el numero maximo de Hackers
colaSerfs = threading.Semaphore(0) #Cola para controlar el numero maximo de Serfs

def cruceDelRio(numHackers, numSerfs):
	print("Navegando con %d hackers y %d serfs.") %(numHackers, numSerfs)
	time.sleep(0.4)

def subirBalsaHacker(numHacker):
	mutex.acquire()
	global hackers
	global serfs
	hackers += 1
	print("Hacker %d llego.") %numHacker

	if(hackers >= 4):
		colaHackers.release()
		colaHackers.release()
		colaHackers.release()
		colaHackers.release()
		hackers -= 4
		cruceDelRio(4, 0)
		mutex.release()
	elif(hackers >= 2 and serfs >= 2):
		colaHackers.release()
		colaHackers.release()
		colaSerfs.release()
		colaSerfs.release()
		hackers -= 2
		serfs -= 2
		cruceDelRio(2, 2)
		mutex.release()
	else:
		mutex.release()

	colaHackers.acquire()

def subirBalsaSerf(numSerf):
	mutex.acquire()

	global hackers
	global serfs
	serfs += 1

	print("Serf %d llego.") %numSerf

	if(serfs >= 4):
		colaSerfs.release()
		colaSerfs.release()
		colaSerfs.release()
		colaSerfs.release()
		serfs -= 4
		cruceDelRio(0, 4)
		mutex.release()
	elif(hackers >= 2 and serfs >= 2):
		colaHackers.release()
		colaHackers.release()
		colaSerfs.release()
		colaSerfs.release()
		hackers -= 2
		serfs -= 2
		cruceDelRio(2, 2)
		mutex.release()
	else:
		mutex.release()

	colaSerfs.acquire()


hackers = 0
serfs = 0

numHacker = 0
numSerf = 0

while (True):
	if (random.random() < 0.5):
		# Genera hilo para hacker
		mutex.acquire()
		numHacker += 1
		hiloHacker = threading.Thread(target = subirBalsaHacker, args = [numHacker])
		hiloHacker.start()
		mutex.release()
	else:
		# Genera hilo para serf
		mutex.acquire()
		numSerf += 1
		hiloSerf = threading.Thread(target = subirBalsaSerf, args = [numSerf])
		hiloSerf.start()
		mutex.release()
