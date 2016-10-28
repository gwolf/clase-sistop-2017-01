#Programa desarrollado por Páez Bidkar
#Versión 2.2

#Importamos librerias
from numpy import *
import queue
import random

#Comenzamos definiendo la clase proc
class proc:
    t_llegada=0    #Tiempo de llegada
    t_necesario=0    #Tiempo minimo necesario para que acabe su ejecución
    T=0    #Tiempo de respuesta
    E=0    #Tiempo de espera
    P=0    #T/t_necesario

procesos=[]    #Definimos el arreglo para nuestros 5 procesos        
def Inicio():
    nombre=['A','B','C','D','E']
    tot=0
    for x in range(0,5):
        proceso=proc()
        proceso.t_llegada=random.randrange(10)    #Inicializamos el tiempo de llegada con un valor entre 0 y 9
        proceso.t_necesario=random.randrange(1,6,1)    #Inicializamos el tiempo necesario para el proceso con un valor entre 1 y 5
        tot+=proceso.t_necesario
        procesos.append(proceso)
        print("\tProceso "+nombre[x]+": "+str(proceso.t_llegada)+", t="+str(proceso.t_necesario))
    print("\tTotal: "+str(tot))

#Definimos la función que ordena por tiempo de llegada a nuestros procesos 
def Ordenar():
    cola=[]
    for tiempo in range(0,10):
        for x in range(0,5):
            proceso=procesos[x]
            if(tiempo==proceso.t_llegada):
                cola.append(proceso)
    return cola


def FCFS(cola=[]):
    #Limpiamos valores de T,E y P
    for x in range(0,5):
        cola[x].T=0
        cola[x].E=0
        cola[x].P=0

    tiempo=0
    while(tiempo<=45):  #5 números con un valor máximo de 9
        for x in range(0,5):        #Recorro cada proceso
            if(cola[x].t_llegada==tiempo or cola[x].E>0):       #Si el proceso llega en el tiempo o está en espera lo atiendo
                while(cola[x].t_necesario>cola[x].T):           #No lo dejo hasta que sea totalmente atendido
                    if(x<5):                                    #Trabajamos con el proceso actual y los siguientes
                        for y in range(x+1,5):                  
                            if(tiempo>=cola[y].t_llegada):      #Si procesos aún no atendidos tienen un tiempo de llegada igual o menor al tiempo actual significa que están en espera
                                cola[y].E+=1                    #Cada quantum pasado aumenta tiempo de espera en proceso bajo la condición dada
                    cola[x].T+=1
                    tiempo+=1
        tiempo+=1

    for x in range(0,5):
        cola[x].T+=cola[x].E
        cola[x].P=cola[x].T/cola[x].t_necesario

    Tp=0.0
    Ep=0.0
    Pp=0.0

#    Descomentar líneas 63 y 65 si desea comprobar resultados
#    print("\n")         #Imprimimos salto de linea para mejor visualizacion de los datos
    for x in range(0,5):
#        print("\tProceso "+str(x)+" necesita: "+str(cola[x].t_necesario)+", llego en: "+str(cola[x].t_llegada)+", T="+str(cola[x].T)+", E="+str(cola[x].E)+", P="+str(cola[x].P))
        Tp+=cola[x].T
        Ep+=cola[x].E
        Pp+=cola[x].P


    Tp=Tp/5
    Ep=Ep/5
    Pp=Pp/5
    print("\n\tFCFS: T={0:.2f}".format(round(Tp,2))+", E={0:.2f}".format(round(Ep,2))+", P={0:.2f}".format(round(Pp,2)))


def RR(cola=[]):
    #Limpiamos valores de T,E y P
    for x in range(0,5):
        cola[x].T=0
        cola[x].E=0
        cola[x].P=0

    tiempo=0
    RR=queue.Queue()
    while(tiempo<=45):       #5 procesos de máximo 9 quantums cada uno
        for x in range(0,5):
            if ((tiempo>=cola[x].t_llegada) and (cola[x].t_necesario>cola[x].T)):
                cola[x].E+=1

            if (cola[x].t_llegada==tiempo):
                RR.put(cola[x])
            
            
        if(RR.empty()==False):
            proceso=RR.get()
            proceso.T+=1
            tiempo+=1
            if(proceso.T<proceso.t_necesario):
                RR.put(proceso)
        else:
            tiempo+=1

    Tp=0
    Ep=0
    Pp=0
    for x in range(0,5):
        cola[x].E-=cola[x].t_necesario      #Eliminamos el tiempo requerido por el proceso del tiempo de espera, la condición hace que este también sea considerado y sumado, basta con quitarlo.
        cola[x].T+=cola[x].E
        cola[x].P=cola[x].T/cola[x].t_necesario

        Tp+=cola[x].T
        Ep+=cola[x].E
        Pp+=cola[x].P
#        Descomentar linea 117 para comprobar valores
#        print("Proceso "+str(x)+": llego en t="+str(cola[x].t_llegada)+", tiempo necesario="+str(cola[x].t_necesario)+", T="+str(cola[x].T)+", E="+str(cola[x].E)+", P="+str(cola[x].P))

    Tp=Tp/5
    Ep=Ep/5
    Pp=Pp/5
    print("\tRR1: T={0:.2f}".format(round(Tp,2))+", E={0:.2f}".format(round(Ep,2))+", P={0:.2f}".format(round(Pp,2)))


def SPN(cola=[]):
    #Limpiamos valores de T,E y P
    for x in range(0,5):
        cola[x].T=0
        cola[x].E=0
        cola[x].P=0
    
    tiempo=0
    while(tiempo<=45):
        disponibles=[]
        for x in range(0,5):
            if(cola[x].t_llegada==tiempo or (cola[x].E>0 and cola[x].T<cola[x].t_necesario)):
                disponibles.append(x)
        
        if disponibles:
            minimo=disponibles[0]
            for d in range(0,len(disponibles)):
                if(cola[minimo].t_necesario>cola[disponibles[d]].t_necesario):
                    minimo=disponibles[d]
#Puede descomentar las líneas 144 y 153 para una mejor visualización del proceso
#            print("En tiempo t="+str(tiempo)+" el mas corto siguiente es el proceso "+str(minimo))

            while(cola[minimo].T<cola[minimo].t_necesario):
                for j in range(0,5):
                    if(tiempo>=cola[j].t_llegada and cola[j].T<cola[j].t_necesario):
                        cola[j].E+=1
                cola[minimo].T+=1
                tiempo+=1
#                print(str(cola[minimo].T))

        else:
            tiempo+=1


    Tp=0
    Ep=0
    Pp=0
    for x in range(0,5):
        cola[x].E-=cola[x].t_necesario      #Eliminamos el tiempo requerido por el proceso del tiempo de espera, la condición hace que este también sea considerado y sumado, basta con quitarlo.
        cola[x].T+=cola[x].E
        cola[x].P=cola[x].T/cola[x].t_necesario

        Tp+=cola[x].T
        Ep+=cola[x].E
        Pp+=cola[x].P
#        Descomentar linea 170 para comprobar valores
#        print("Proceso "+str(x)+": llego en t="+str(cola[x].t_llegada)+", tiempo necesario="+str(cola[x].t_necesario)+", T="+str(cola[x].T)+", E="+str(cola[x].E)+", P="+str(cola[x].P))

    Tp=Tp/5
    Ep=Ep/5
    Pp=Pp/5
    print("\tSPN: T={0:.2f}".format(round(Tp,2))+", E={0:.2f}".format(round(Ep,2))+", P={0:.2f}".format(round(Pp,2)))

def Ronda():
    Inicio()
    cola = Ordenar()
    FCFS(cola)
    RR(cola)
    SPN(cola)

R=["Primera","Segunda","Tercera","Cuarta","Quinta"]
for x in range(0,5):
    print("\n-"+str(R[x])+" Ronda:\n")
    Ronda()
    procesos=[]
