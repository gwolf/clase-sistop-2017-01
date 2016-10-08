#tarea2 de sistemas operativos
#algoritmo FCFS
import random
import sys
class colaProc:
	tiempo=[]
	tot=0
	duracion=[]
	def __init__(self,num):
		self.num=num
		self.duracion.append(random.choice(range(10))+1)
		self.tiempo.append(self.tot)
		self.tot+=1
		while len(self.duracion)<num:
			if random.choice(range(100))%2==0:
				self.duracion.append(random.choice(range(10))+1)
				self.tiempo.append(self.tot)
			self.tot+=1
	def FCFS(self):
		duracion=self.duracion
		tiempo=self.tiempo
		aux="\t"
		cont=0
		pen=0
		t=0
		i=0
		test=[]
		sys.stdout.write("\t\t")
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
				test.append(totP)
				for j in range(duracion[i]):
					sys.stdout.write(str(cont)+" ")
					if cont>9:
						aux+=chr(i+65)+"  "	
					else:
						aux+=chr(i+65)+" "
					cont+=1
				# print("pen"+str(pen))
				# print("\t"+str(cont)+" "+str(tiempo[i])+"<--")
				t+=duracion[i]
				i+=1
			else:
				e=False
				sys.stdout.write(str(cont)+" ")
				if cont>9:
					aux+="Z"+"  "	
				else:
					aux+="Z"+" "
				cont+=1

			# sys.stdout.write("\n")
		print("\n")
		sys.stdout.write("\n"+"FCFS "+aux+ "T = "+str(float(t+esp)/len(tiempo))+" E ="+str(float(esp)/len(tiempo))+" P= "+str(totP/len(tiempo)) )

		
n= colaProc(3)
print(n.duracion)
print(n.tiempo)
n.FCFS()
