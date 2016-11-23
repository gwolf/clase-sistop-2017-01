#!/usr/bin/python3
# -*- Encoding: utf-8 -*-
#Nombre: Carlos Alberto Díaz Olivares

class Proc:
	def __init__(self,nombre,llegada,longitud):
		self.nombre=nombre
		self.llegada=llegada
		self.longitud=longitud
		self.fin = 0
	def __repr__(self):
		return repr((self.nombre, self.llegada, self.longitud))


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

class RR:
	def __init__(self,listaProc,quantum):
		self.listaProc = listaProc
		self.quantum = quantum
		self.ejecutando = []
		self.terminado = []
		self.cambioContexto = [] 

	def simular(self):
		t=0
		while True:
			for x in range(len(self.listaProc)):
				if(listaProc[x].llegada==t)
				self.ejecutando.append(listaProc[x])
				del self.listaProc[x]
			for x in range(len(self.ejecutando)):
				if(self.ejecutando[x].longitud-self.quantum > 0):
					self.ejecutando[x].longitud -= self.quantum
					self.ejecutando.append(self.ejecutando[x])
					del self.ejecutando[x]
					t += self.quantum
				elif(self.ejecutando[x].longitud-self.quantum == 0):
					self.ejecutando[x].fin = t + self.quantum
					self.terminado.append(self.ejecutando[x])
					del self.ejecutando[x]
					t += self.quantum
				else:
					self.ejecutando[x].fin = t + self.ejecutando[x].longitud
					self.terminado.append(self.ejecutando[x])
					del self.ejecutando[x]
					t += self.quantum
			if(len(self.listaProc)==0)
			break
		for x in 








			


listaProc = [Proc('A',0,3),Proc('C',3,2),Proc('B',1,5),Proc('E',12,5),Proc('D',9,5)]

listaProc = sorted(listaProc, key=lambda Proc: Proc.llegada)

print(listaProc)
fifo1 = Fifo(listaProc)
fifo1.simular()