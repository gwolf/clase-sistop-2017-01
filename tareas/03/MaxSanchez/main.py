#cuerpo del programa
#Elaborado por: Sánchez Hernández Max Armando
#Fecha: 10/Octubre/2016
#Materia:Sistemas operativos
#Tarea 3
#Lenguaje: Python3
#archivos necesarios bib.py
from bib import *
print("Tarea: Realizar una prograama que simule la planeación de procesos usando un algoritmo de planeación")
print("algoritmos elegidos: First Come First Served (FCFS), Round Robin (RR) y Short Process Next")
cond=True
while cond:
	try:
		n=int(input("\nCuantos procesos quieres simular, recomendación 3-10: "))
		cond=False
	except:
		print("Error al convertir ese numero intenta de nuevo")
colaProc(n)
