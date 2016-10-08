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
		self.q=2
		# self.q=int(input("La medida de q para Round Robin: "))
	def FCFS(self):
		duracion=self.duracion
		tiempo=self.tiempo
		sys.stdout.write("\t\t")
		aux="\t"
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
		sys.stdout.write("\n"+"FCFS "+aux+ "--> T = "+str(float(t+esp)/len(tiempo))+" E ="+str(float(esp)/len(tiempo))+" P= "+str(totP/len(tiempo))+"\n" )

	def zero(self,list):
		for i in list:
			if i !=0:
				return False
		return True

	def RoundRobin(self):
		
		duracion=self.duracion
		tiempo=self.tiempo
		q=self.q
		i=0
		clk=-1
		aux=""
		cond=True
		while not(self.zero(duracion)) and clk <1000:
			cont=0
			# print("sale")
			while(cont<q and cond):
				clk+=1
				sys.stdout.write(str(clk)+" ")
				aux+=chr(i+65)+" "
				if clk>9:
					aux+=" "
				cont+=1
				
				duracion[i]-=1
				if duracion[i]==0:
					cont=q
			cond=False
			if (i+1)<len(duracion):
				i+=1
				if (duracion[i]>0 and tiempo[i]<=clk):
					cond=True
				elif tiempo[i]>=clk:
					clk+=1
					sys.stdout.write(str(clk)+" ")
					aux+="Z"+" "
					if clk>9:
						aux+=" "
			elif len(duracion) !=0:
				i=0
				if (duracion[i]>0 and tiempo[i]<=clk):
					cond=True
				elif tiempo[i]>=clk:
					clk+=1
					sys.stdout.write(str(clk)+" ")
					aux+="Z"+" "
					if clk>9:
						aux+=" "
			# print(i)
			
		print("\n")
		print(aux)




n= colaProc(3)
print(n.duracion)
print(n.tiempo)
# n.FCFS()
n.RoundRobin()