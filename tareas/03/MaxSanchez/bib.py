#tarea3 de sistemas operativos

import random
import sys

def sumLista(lista):
	acum=0
	for i in lista:
		acum+=i
	return acum

def zero(lista):#verifica que todos los miembros de la lista sean cero
	for i in lista:
		if i !=0:
			return False
	return True

def pminPos(dr,ti,clk):#regresa el proceso minimo posible
	#este el algoritmo de decision SPN
	if zero(dr):
		return -1#no hay mas procesos
	dr_pos=[]#aqui vamos a ver cuales son posibles
	in_pos=[]
	for i in range(len(dr)):
		if clk>=ti[i] and dr[i]!=0:#si es posible
			dr_pos.append(dr[i])#se apendiza la duracion
			in_pos.append(i)#se apendiza el indice
	if len(dr_pos)==0:
		return -2#hay procesos pero falta tiempo para ejecutarlos
	else:
		return in_pos[dr_pos.index(min(dr_pos))]#la funcion regresa el indice del minimo posible de una lista

class colaProc:

	def __init__(self,num):
		self.tiempo=[]
		self.tot=0
		self.duracion=[]
		self.num=num
		self.duracion.append(random.choice(range(10))+1)
		self.tiempo.append(self.tot)
		self.tot+=1
		while len(self.duracion)<num:
			if random.choice(range(100))%2==0:
				self.duracion.append(random.choice(range(10))+1)
				self.tiempo.append(self.tot)
			self.tot+=1
		cond=True
		while cond:
			try:
				self.q=int(input("La medida de q para Round Robin: "))
				cond=False
			except:
				print("Error ese no es un numero")
		print("\nDuración de cada proceso\t\t"+str(self.duracion))
		print("Tiempo de entrada por cada proceso\t"+str(self.tiempo),end="\n\n")
		self.FCFS()
		self.RoundRobin()
		self.SPN()

	def FCFS(self):
		duracion=self.duracion
		tiempo=self.tiempo
		sys.stdout.write("Guia de tiempo\t")
		aux="\t\t"
		cont=0
		t=0
		i=0
		totP=0
		e=True
		esp=0
		while i <self.num:
			if tiempo[i]<=cont:
				if e:
					pen=cont-tiempo[i]
					esp+=pen
				else:
					pen=0
					e=True
				totP+=1+float(pen)/duracion[i]
				for j in range(duracion[i]):
					sys.stdout.write(str(cont)+" ")
					aux+=chr(i+65)+" "
					if cont>9:
						aux+=" "
					cont+=1
				t+=duracion[i]
				i+=1
			else:
				e=False
				sys.stdout.write(str(cont)+" ")
				aux+="Z"+" "
				if cont>9:
					aux+=" "
				cont+=1
		print("\nFCFS%s--> T=%.2f\tE=%.2f\tP=%.2f"%(aux,float(t+esp)/len(tiempo),float(esp)/len(tiempo),totP/len(tiempo)))

	def sumPen(self,lista,clk,index,f):
		for i in range(self.num):
			if self.tiempo[i]<=clk and i !=index and not(f[i]):
				lista[i]+=1
		return lista

	def RoundRobin(self):
		dr=[]
		for i in self.duracion:
			dr.append(i)
		tiempo=self.tiempo
		q=self.q
		i=0
		clk=-1
		aux="\t\t"
		cond=True
		p=[]
		f=[]
		t=[]
		for m in range(self.num):
			p.append(0)
			f.append(False)
		while not(zero(dr)):
			cont=0
			while(cont<q and cond):
				clk+=1
				p=self.sumPen(p,clk,i,f)
				aux+=chr(i+65)+" "
				if clk>9:
					aux+=" "
				cont+=1
				dr[i]-=1
				if dr[i]==0:
					cont=q
					f[i]=True
			cond=False
			cont=0
			while not(cond) and (len(dr)*2)>cont:
				i+=1
				i=i%len(dr)
				if (dr[i]>0 and tiempo[i]<=clk+1):
					cond=True
				cont+=1
			if not(cond):
				clk+=1
				aux+="Z"+" "
				if clk>9:
					aux+=" "
		aux=aux[:-3]
		t=[]
		for m in range(len(p)):
			t.append(p[m]+self.duracion[m])
		pena=0
		for i in range(len(p)):
			pena+=1+(p[i]/self.duracion[i])
		print("RR%s--> T=%.2f\tE=%.2f\tP=%.2f"%(aux,sumLista(t)/self.num,sumLista(p)/self.num,pena/self.num))#agregar opcion para modificar el quantum

	def SPN(self):
		dr=[]
		num=self.num
		for i in self.duracion:
			dr.append(i)
		ti=self.tiempo
		aux="SPN\t\t"
		clk=0#reloj igual a 0
		indice=0
		indicesdeFin=[]
		for i in dr:
			indicesdeFin.append(0)
		while indice!=-1:
			if indice==-2:
				aux+="Z "
			else:
				aux+=chr(indice+65)+" "
				dr[indice]-=1
			if clk>9:
				aux+=" "
			#fin de algoritmo SPN considerando solo duracion
			clk+=1
			if dr[indice]==0:
				indicesdeFin[indice]=clk
			indice=pminPos(dr,ti,clk)#inicio de algoritmo SPN considerando solo duracion
		tiempo=(sumLista(indicesdeFin)-sumLista(ti))
		esp=(tiempo-clk)
		pena=0
		for i in range(len(indicesdeFin)):
			pena+=1+((indicesdeFin[i]-ti[i])/self.duracion[i])
		print("%s--> T=%.2f\tE=%.2f\tP=%.2f"%(aux,tiempo/num,esp/num,pena/num))
