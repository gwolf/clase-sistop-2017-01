import threading
#alumno Max Armando Sanchez Hernandez 
def asignarBalsa():
	global balsa
	global linux
	global win
	global mutexAux
	global sl
	global sw
	mutexAux.acquire()
	if len(balsa)!=4 :
		mutexAux.release()
	
		sl.acquire()
		if len(linux)!=0:
			balsa.append(linux.pop())
		else:
			sl.release()
		if len(balsa)!=4 :
			sw.acquire()
			if len(win)!=0:
				balsa.append(win.pop())
			else:
				sw.release()
	else:
		print ("Aqui va una balsa: ")
		print (balsa)
		balsa=[]
		sl.release()
		sl.release()
		sw.release()
		sw.release()
		
		if len(linux)<2 and len(win)!=0:
	
			sw.release()
			sw.release()
		if len(win)<2 and len(linux)!=0:
	
			sl.release()
			sl.release()
	
		mutexAux.release()
balsa=[]
linux=[]#arreglo de pasajeros del team linux
win=[]#arreglo de pasajeros del team windows
mutexAux=threading.Semaphore(1)#mutex auxiliar para 
							 	#ayudar a que las consultas
							 	#se hagan por tiempos 
sl=threading.Semaphore(2)#semaforo linux
sw=threading.Semaphore(2)#semaforo windows
hilos=[]
nl=int(input("Cuantos programadores de linux tienes: "))
nw=int(input("Cuantos programadores de windows tienes: "))

for i in range(nl):#nombramos a nuestros pasajeros de windows
	linux.append("linux_"+str(i))
for i in range(nw):
	win.append("win_"+str(i))

c1=int((nl/4))+int((nl%4)+nw/4)
for i in range(nl+c1):
	hilos.append(threading.Thread(target=asignarBalsa))
for i in range(nw+c1):
	hilos.append(threading.Thread(target=asignarBalsa))
if len(linux)<2 and len(win)!=0:
	
	sw.release()
	sw.release()
if len(win)<2 and len(linux)!=0:
	

	sl.release()
	sl.release()
for i in range(nw+nl+2*c1):#lanzamos los hilos que asignan a los de linux a la balsa
	hilos[i].start()

for i in range(nw+nl+2*c1):
	hilos[i].join()

print("Estos fueron los que quedaron ")
print(linux)
print(win)
print (balsa)
