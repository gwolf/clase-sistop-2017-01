#tarea2 de sistemas operativos
#algoritmo FCFS
import random
import sys
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
		sys.stdout.write("\n"+"FCFS "+aux+ "--> T = "+str(float(t+esp)/len(tiempo))+" E ="+str(float(esp)/len(tiempo))+" P= "+str(totP/len(tiempo)))

	def zero(self,list):
		for i in list:
			if i !=0:
				return False
		return True

	def sumPen(self,lista,clk,index,f):
		for i in range(self.num):
			if self.tiempo[i]<=clk and i !=index and not(f[i]):
				lista[i]+=1
		return lista

	def RoundRobin(self,res):
		dr=[]
		for i in res:
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
		while not(self.zero(dr)) and clk <1000:
			cont=0
			# print("sale")
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
		print("\nRR"+str(aux))
		print(p)
		t=[]
		for m in range(3):
			t.append(p[m]+self.duracion[m])
		print(t)
n= colaProc(3)
axu=n.duracion
print(axu)
print(n.tiempo)
n.FCFS()
n.RoundRobin(axu)