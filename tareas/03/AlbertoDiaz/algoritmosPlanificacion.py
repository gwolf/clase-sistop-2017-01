#!/usr/bin/python3
# -*- Encoding: utf-8 -*-
#Nombre: Carlos Alberto Díaz Olivares
#Algoritmos de Planificacion

import random

def promediar(lista):
	sum=0
	for i in range(len(lista)):
		sum = sum + lista[i]
	return sum/len(lista)
class Proc:
	def __init__(self,nombre,llegada,longitud):
		self.nombre=nombre
		self.llegada=llegada
		self.longitud=longitud
		self.fin = 0
	def __repr__(self):
		return repr((self.nombre, self.llegada, self.longitud,self.fin))


class Fifo:
	def __init__(self,listaProc):
		self.listaProc=listaProc
		self.e=[]
		self.t=[]
		self.p=[]

	def simular(self):
		t=0
		for x in range(len(listaProc)):
			self.e.append(t - listaProc[x].llegada)
			self.t.append(self.e[x] + listaProc[x].longitud)
			self.p.append(self.t[x]/listaProc[x].longitud)
			t = t + listaProc[x].longitud
			print("T: " + str(self.t[x]) + "  E: " + str(self.e[x]) + "  P: " + str(self.p[x]) + "  t= " + str(t))
		print("Promedio T:" + str(promediar(self.t)) + " Promedio E:" + str(promediar(self.e)) + " Promedio P:" + str(promediar(self.p)))

class RR:
	def __init__(self,listaProc,quantum):
		self.listaProc = listaProc
		self.quantum = quantum
		self.ejecutando = []
		self.terminado = []
		self.e=[]
		self.t=[]
		self.p=[]

	def simular(self):
		t=0
		count = -1
		while True:
			for x in range(len(self.listaProc)):
				if(self.listaProc[x].llegada==t):
					if(len(self.ejecutando)==1):
						self.ejecutando.insert(0,self.listaProc[x])
					else:
						self.ejecutando.insert(1,self.listaProc[x])
					count = x
			if(count!=-1):
				del self.listaProc[count]
			count = -1
			for x in range(len(self.ejecutando)):
				if(self.ejecutando[0].longitud-self.quantum > 0):
					#print("t=: " +str(t))
					self.ejecutando[0].longitud -= self.quantum
					self.ejecutando.append(self.ejecutando[0])
					del self.ejecutando[0]
					t += self.quantum
					#print("caso1: " +str(t))
					#print("caso3: " +str(t))
					#print("En lista de Ejecucion")
					#print(self.ejecutando)
					#print("En lista de procesos terminados")
					#print(self.terminado)
					continue
				elif(self.ejecutando[0].longitud-self.quantum == 0):
					#print("t=: " +str(t))
					self.ejecutando[0].fin = t + self.quantum
					self.terminado.append(self.ejecutando[0])
					del self.ejecutando[0]
					t += self.quantum
					#print("caso2: " +str(t))
					#print("caso3: " +str(t))
					#print("En lista de Ejecucion")
					#print(self.ejecutando)
					#print("En lista de procesos terminados")
					#print(self.terminado)
					continue
				else:
					#print("t=: " +str(t))
					self.ejecutando[0].fin = t + self.ejecutando[0].longitud
					self.terminado.append(self.ejecutando[0])
					del self.ejecutando[0]
					t += self.quantum
					#print("caso3: " +str(t))
					#print("En lista de Ejecucion")
					#print(self.ejecutando)
					#print("En lista de procesos terminados")
					#print(self.terminado)
					continue
			if(len(self.ejecutando)==0):
				break
		self.terminado = sorted(self.terminado, key=lambda Proc: Proc.llegada)
		for x in range(len(self.terminado)):
			self.t.append(self.terminado[x].fin - self.terminado[x].llegada)
			self.e.append(self.terminado[x].fin-self.terminado[x].llegada-self.terminado[x].longitud)
			self.p.append(self.t[x]/self.terminado[x].longitud)
			print("T: " + str(self.t[x]) + "  E: " + str(self.e[x]) + "  P: " + str(self.p[x]))
		print("Promedio T:" + str(promediar(self.t)) + " Promedio E:" + str(promediar(self.e)) + " Promedio P:" + str(promediar(self.p)))








			


listaProc = [Proc('A',0,3),Proc('C',3,2),Proc('B',1,5),Proc('E',12,5),Proc('D',9,5)]

listaProc = sorted(listaProc, key=lambda Proc: Proc.llegada)
print(listaProc)
print("FIFO:")
fifo1 = Fifo(listaProc)
fifo1.simular()
print("RR1:")
rr1 = RR(listaProc,1)
rr1.simular()

for i in range(5):
	listaProc = [Proc('A',0,random.randrange(1,10)),Proc('C',random.randrange(1,10),random.randrange(1,10)),Proc('B',random.randrange(1,10),random.randrange(1,10)),Proc('E',random.randrange(1,10),random.randrange(1,10)),Proc('D',random.randrange(1,10),random.randrange(1,10))]
	listaProc = sorted(listaProc, key=lambda Proc: Proc.llegada)
	print(listaProc)
	print("FIFO:")
	fifo1 = Fifo(listaProc)
	fifo1.simular()
	print("RR1:")
	rr1 = RR(listaProc,1)
	rr1.simular()


