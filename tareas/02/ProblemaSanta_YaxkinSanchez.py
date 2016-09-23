# -*- Encoding: utf-8 -*-
#
# Santa Claus duerme en el polo norte mientras sus elfos trabajan frenéticamente en la construcción de millones 
# de nuevos juguetes.
# -> A veces se topan con un problema - Pueden pedir ayuda a Santa Claus, pero sólo de tres en tres.
# Sus nueve renos pasan todo el año de vacaciones en las playas del Caribe.
# -> Santa debe despertar a tiempo para iniciar su viaje anual.
#
# Si los nueve renos están de vuelta, es hora de despertar a Santa Claus para que inicie su recorrido.
# Si los elfos tienen algún problema construyendo algún juguete, le piden ayuda a Santa Claus.
# -> Para no darle demasiada lata, lo hacen cuando sólo hay tres elfos que tienen un problema. Mientras tanto
#    lo dejan dormir.
# -> Puede haber cualquier cantidad de elfos.

import threading
import time
import random

#Contadores para renos y elfos.
global contador_renos
global contador_elfos

contador_renos = 0
contador_elfos = 0

#Mutex para modificar y checar los contadores.
mutex_contador = threading.Semaphore(1)

#Señal para enviar a los renos de vacaciones.
senal_renos = threading.Semaphore(0)

#Señal para despachar a los elfos.
senal_elfos = threading.Semaphore(0)

#Mutex para evitar que otros elfos entren cuando un grupo está siendo atendido.
mutex_grupo_elfos = threading.Semaphore(1)

#Señal para despertar a Santa.
senal_santa = threading.Semaphore(0)

def ayudar_elfos():
	print "Santa ayuda a elfos."
	time.sleep(0.5)
	print "Santa ha terminado de ayudar a los elfos."

def repartir_juguetes():
	print "Santa sale a repartir juguetes."
	time.sleep(2.5)
	print "Santa ha regresado."

def vacaciones_reno(num):
	print "El reno %d se va de vacaciones." % num
	time.sleep(random.random()*10)

def elfo(num):
	global contador_elfos
	print "El elfo %d espera a que se junte un grupo para pedir ayuda a Santa." % num
	#El elfo adquiere el mutex para evitar que más elfos se aglomeren si es que con él son tres.
	mutex_grupo_elfos.acquire()
	#Y adquiere el mutex para incrementar su contador.
	mutex_contador.acquire()
	contador_elfos += 1
	#Si se ha juntado el grupo de tres, despiertan a Santa para pedir ayuda.
	if contador_elfos == 3:
		print "Se han juntado tres elfos, ¡a llamar a Santa!."
		senal_santa.release()
	#En caso contrario, libera el mutex para recibir a más elfos.
	else:
		mutex_grupo_elfos.release()
	#Y libera el mutex para su contador.
	mutex_contador.release()
	
	#El elfo recibe la señal de que fue despachado.
	senal_elfos.acquire()
	print "El elfo %d está satisfecho." % num

	#Adquiere el mutex para reducir su contador.
	mutex_contador.acquire()
	contador_elfos -= 1
	#El último libera el mutex para permitir entrar a más elfos.
	if contador_elfos == 0:
		mutex_grupo_elfos.release()
	#Y libera el mutex para su contador.
	mutex_contador.release()

def reno(num):
	global contador_renos
	while True:
		#El reno regresa de sus vacaciones.
		print "El reno %d ha regresado al Polo Norte." % num
		
		#Adquiere el mutex para incrementar su contador.
		mutex_contador.acquire()
		contador_renos += 1
		#Si los 9 renos ya llegaron, despiertan a Santa para salir.
		if contador_renos == 9:
			print "Están todos los renos, ¡a llamar a Santa para salir!"
			senal_santa.release()
		#Si aún no llegan todos, no pasa nada.

		#Y liberan el mutex para el contador y esperan.
		mutex_contador.release()
		
		#Los renos adquieren la señal de regreso.
		senal_renos.acquire()
		
		#Y se toman sus merecidas vacaciones
		vacaciones_reno(num)

def santa():
	global contador_elfos
	global contador_renos
	while True:
		#Santa despierta al ser llamado por los elfos o los renos.
		senal_santa.acquire()
		#Santa adquiere el mutex para checar los contadores.
		mutex_contador.acquire()
		#Si lo llaman los renos...
		if contador_renos == 9:
			#Sale a repartir juguetes
			repartir_juguetes()
			#Modifica el contador de los renos.
			contador_renos -= 9
			#Y les manda una señal de que ya regresaron al Polo Norte.
			for i in range(9):
				senal_renos.release()
		#Si lo llaman los elfos....
		elif contador_elfos == 3:
			#Les ayuda.
			ayudar_elfos()
			#Y manda una señal de que han sido despachados.
			for i in range(3):
				senal_elfos.release()
		#Al terminar su labor, libera el mutex del contador, y regresa a dormir.
		mutex_contador.release()

hilos_elfos = 0
hilos_renos = 0

#Hilo único para Santa.
threading.Thread(target=santa, args=[]).start()

#Nueve hilos para los renos.
for i in range(1,10):
	threading.Thread(target=reno, args=[i]).start()

#Hilos para los elfos.
while True:
	time.sleep(0.25)
	#Suponiendo que los elfos son un tanto eficientes (y para dejar descansar a Santa)
	if random.random() < 0.75:
		threading.Thread(target=elfo, args=[hilos_elfos]).start()
		hilos_elfos += 1

# NOTA
#
# Es importante que el elfo busque adquirir primero mutex_grupo_elfos primero,
# ya que si buscara adquirir mutex_contador primero, entraría en una condición de carrera con Santa
# y muy seguramente provocaría un dealock:
# -> Santa espera eternamente por mutex_contador 
# -> Los elfos esperan eternamente por senal_elfos para poder se atendidos
#    pues Santa no tiene acceso a los contadores para saber quien lo llama.
