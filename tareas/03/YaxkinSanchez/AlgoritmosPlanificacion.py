#!/usr/bin/python
# -*- Encoding: utf-8 -*-

#####################################################################
#																	#
#	AlgoritmosPlanificacion.py 										#
#	Autor: David Yaxkin Sanchez Neri								#
#																	#
#	Simulador de algunos algoritmos de planificación de procesos:	#
#	-> First Come, First Serve										#
#	-> Round Robin													#
#	-> Shortest Process Next										#
#																	#
#####################################################################

from collections import deque
import random
import threading

class Proceso():
	nombre = ""
	ticks_necesarios = 0
	tiempo_llegada = 0
	ticks_restantes = 0
	tiempo_inicio = 0
	tiempo_final = 0
	tiempo_espera = 0 		
	tiempo_respuesta = 0
	proporcion_penalizacion = 0

	def __init__(self,nombre):
		self.nombre = nombre
		self.ticks_necesarios = int(round(random.random()*9) + 1)

	def procesar(self):
		global tiempo_transcurrido
		if self.ticks_restantes > 0:
			print self.nombre,
			self.ticks_restantes -= 1
			
	def calcula_metricas(self):
		self.tiempo_respuesta = self.tiempo_final - self.tiempo_llegada
		self.tiempo_espera = self.tiempo_final - self.tiempo_llegada - self.ticks_necesarios
		self.proporcion_penalizacion = round(self.tiempo_respuesta / (self.ticks_necesarios*1.0),2)


class AlgoritmoPlanificacion():
	tiempo_transcurrido = 0 
	lista_procesos = []
	cola_procesos = deque([])
	numero_procesos = 0
	lista_procesos_pendientes = []
	lista_procesos_terminados = []

	def __init__(self):
		self.lista_procesos = []
		self.lista_procesos.append(Proceso("A"))
		self.lista_procesos.append(Proceso("B"))
		self.lista_procesos.append(Proceso("C"))
		self.lista_procesos.append(Proceso("D"))
		self.lista_procesos.append(Proceso("E"))
		self.numero_procesos = len(self.lista_procesos)
		for i in range(len(self.lista_procesos)):
			if i == 0:
				self.lista_procesos[i].tiempo_llegada = 0
			else:
				t = int(round(random.random()*5))
				self.lista_procesos[i].tiempo_llegada += self.lista_procesos[i-1].tiempo_llegada + t 
		self.muestra_procesos()

	def reiniciarProcesos(self):
		for item in self.lista_procesos:
			item.ticks_restantes = item.ticks_necesarios

	def encolarProcesos(self):
		procesos_encolados = 0
		if len(self.lista_procesos_pendientes) != 0:
			for item in self.lista_procesos_pendientes:
				if item.tiempo_llegada <= self.tiempo_transcurrido:
					self.cola_procesos.append(item)
					procesos_encolados += 1
			for i in range(procesos_encolados):
				self.lista_procesos_pendientes.pop(0)

	def muestra_procesos(self):
		print "Proceso | Llegada | Ticks"
		for item in self.lista_procesos:
			print "   " + item.nombre + "\t     " + str(item.tiempo_llegada) + "       " + str(item.ticks_necesarios)

	def muestra_resultados(self):
		for item in self.lista_procesos_terminados:
			print "   " + item.nombre + " espera=" + str(item.tiempo_espera) + " respuesta=" + str(item.tiempo_respuesta) + " penalizacion=" + str(item.proporcion_penalizacion)

	def obtener_resultados(self):
		acc_tiempo_espera = 0
		acc_tiempo_respuesta = 0
		acc_proporcion_penalizacion = 0
		for item in self.lista_procesos_terminados:
			item.calcula_metricas()
			acc_tiempo_espera += item.tiempo_espera
			acc_tiempo_respuesta += item.tiempo_respuesta
			acc_proporcion_penalizacion += item.proporcion_penalizacion
		avg_tiempo_espera = acc_tiempo_espera / (len(self.lista_procesos_terminados)*1.0)
		avg_tiempo_respuesta = acc_tiempo_respuesta / (len(self.lista_procesos_terminados)*1.0)
		avg_proporcion_penalizacion = acc_proporcion_penalizacion / len(self.lista_procesos_terminados)
		print "\n\tE: " + str(avg_tiempo_espera) + " T: " + str(avg_tiempo_respuesta) + " P: " + str(avg_proporcion_penalizacion)

	def runFCFS(self):
		self.reiniciarProcesos()
		self.lista_procesos_pendientes = list(self.lista_procesos)
		self.lista_procesos_terminados = []
		self.tiempo_transcurrido = 0 
		while len(self.lista_procesos_terminados) < self.numero_procesos:
			self.encolarProcesos()
			if len(self.cola_procesos) == 0:
				self.tiempo_transcurrido +=1
				print "X",
			else:
				proceso = self.cola_procesos.popleft()
				proceso.tiempo_inicio = self.tiempo_transcurrido
				while proceso.ticks_restantes > 0:
					proceso.procesar()
					self.tiempo_transcurrido +=1
				self.lista_procesos_terminados.append(proceso)
				proceso.tiempo_final = self.tiempo_transcurrido
		self.obtener_resultados()
	
	def runRR(self,quantum):
		tamano_quantum = quantum
		self.reiniciarProcesos()
		self.lista_procesos_pendientes = list(self.lista_procesos)
		self.lista_procesos_terminados = []
		self.tiempo_transcurrido = 0 
		while len(self.lista_procesos_terminados) < self.numero_procesos:
			self.encolarProcesos()
			if len(self.cola_procesos) == 0:
				self.tiempo_transcurrido +=1
				print "X",
			else:
				ticks_quantum = quantum
				proceso = self.cola_procesos.popleft()
				proceso.tiempo_inicio = self.tiempo_transcurrido
				while proceso.ticks_restantes > 0 and ticks_quantum > 0:
					proceso.procesar()
					self.tiempo_transcurrido +=1
					ticks_quantum -=1
				self.encolarProcesos()
				if proceso.ticks_restantes > 0:
					self.cola_procesos.append(proceso)
				else:
					self.lista_procesos_terminados.append(proceso)
					proceso.tiempo_final = self.tiempo_transcurrido
		self.obtener_resultados()

	def runSPN(self):
		lista_procesos_listos = []
		self.reiniciarProcesos()
		self.lista_procesos_pendientes = list(self.lista_procesos)
		self.lista_procesos_terminados = []
		self.tiempo_transcurrido = 0 
		while len(self.lista_procesos_terminados) < self.numero_procesos:
			self.encolarProcesos()
			if len(self.cola_procesos) == 0:
				self.tiempo_transcurrido +=1
				print "X",
			else:
				proceso_mas_corto = self.cola_procesos.popleft()
				for i in range(len(self.cola_procesos)):
					aux = self.cola_procesos.popleft()
					if aux.ticks_necesarios < proceso_mas_corto.ticks_necesarios:
						self.cola_procesos.append(proceso_mas_corto)
						proceso_mas_corto = aux
					else:
						self.cola_procesos.append(aux)
				proceso = proceso_mas_corto
				proceso.tiempo_inicio = self.tiempo_transcurrido
				while proceso.ticks_restantes > 0:
					proceso.procesar()
					self.tiempo_transcurrido +=1
				self.lista_procesos_terminados.append(proceso)
				proceso.tiempo_final = self.tiempo_transcurrido
		self.obtener_resultados()

for i in range(5):
	print "Ronda " + str(i+1)
	algoritmo = AlgoritmoPlanificacion()
	print "FCFS"
	algoritmo.runFCFS()
	print "RR(4)"
	algoritmo.runRR(4)
	print "SPN"
	algoritmo.runSPN()
