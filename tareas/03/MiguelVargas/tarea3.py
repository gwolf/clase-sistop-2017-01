#########################################
####Miguel Angel Vargas Espinosa#########
####Facultad de Ingeniería###############
#######Sistemas Operativos###############
###########Sem 2017-1####################
######Algoritmo de planificacion#########
#########################################

import random, threading, queue 

ColaProcesos=queue.Queue()

ini=0
fin=0
T=0
E=0
P=0



class proceso:
    
    def __init__(self, llegada,duracion,name,espera): #constructor de la clase nos genera objetos del tipo proceso
        self.llegada=llegada
        self.duracion=duracion
        self.name=name
        self.espera=espera
    
    def fcfs(self): #Algoritmo parecido a la cola FIFO
        print("   Proceso   llegada    t      ini     fin       T        E        P")
        #print("______________________________________________________________________")      
        tespera=0
        prom_dura=0
        T=0
        while not ColaProcesos.empty():
            actual=ColaProcesos.get()
            actual.espera=tespera
            print("\n", actual.name,actual.llegada,actual.duracion, sep="\t", end="")
            prom_dura+=actual.duracion
            tduracion=actual.duracion
            while(actual.duracion>0):
                actual.duracion-=1
                tespera+=1
            ini=actual.espera
            print("\t", ini, end="")
            fin=ini+tduracion
            print("\t", fin, end="")
            T=fin-actual.llegada
            print("\t", T, end="")
            E=ini-actual.llegada
            print("\t", E, end="")
            P=T/tduracion
            print("\t", P, end="")
        prom_dura=prom_dura/5
        print("\n\tPromedio\t",prom_dura)
    def run(self):
        self.fcfs()
        
A=proceso(0,4*random.randint(1,5),"a",0)
B=proceso(random.randint(1,5),4*random.randint(1,5),"b",0)
C=proceso(random.randint(5,7),4*random.randint(1,8),"c",0)
D=proceso(random.randint(7,10),4*random.randint(5,9),"d",0)
E=proceso(random.randint(10,12),4*random.randint(1,5),"e",0)
#Comentar/descomentar para el ejemplo del libro:
#A=proceso(0,3,"a",0)
#B=proceso(1,5,"b",0)
#C=proceso(3,2,"c",0)
#D=proceso(9,5,"d",0)
#E=proceso(12,5,"e",0)
ColaProcesos.put(A)
ColaProcesos.put(B)
ColaProcesos.put(C)
ColaProcesos.put(D)
ColaProcesos.put(E)
threading.Thread(target=A.run).start()