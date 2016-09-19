''' 
Este código presenta la implementación de la solución al problema "El cruze de rio" mediante el uso de semaforos,
barreras y mutex.
Hecho por Ortega González y Páez Lampon
'''
import threading #para emplear manejo de hilos y las primitivas de sincronización
import time# para uso de tim.sleep
global hackers#número de hackers
global serfs#número de trabajadores de microsoft
global numbal#numero de balsa
global pasajeros#numero pasajeros por balsa
numbal=0
hackers = 0
pasajeros=0
serfs = 0
lock=threading.Lock()#mutex secundario
hackerqueue = threading.Semaphore(0)#fila de hackers
serfqueue = threading.Semaphore(0)#fila de serfs
mutex = threading.Semaphore(1)#mutex primario
boat = threading.Barrier(4)#barrera para pasar
'''
Función que representa como se van formando los hackers y 
las condiciones necesarias para el abordaje. 
Recibe num: el número de hilo
'''
def hacker(num):
    global hackers
    global serfs
    mutex.acquire()
    hackers +=1
    if hackers == 4:
        permitePa(hackerqueue,4)#abre cuatro lugares para pasar alos hackers
        hackers -= 4
        mutex.release()
    elif hackers == 2 and serfs >= 2:
        permitePa(hackerqueue,2)#abre 2 lugares para pasar a los hackers
        permitePa(serfqueue,2)#abre 2 lugares para pasar a los serfs
        hackers -= 2
        serfs -= 2
        mutex.release()
    else:
        mutex.release()
    hackerqueue.acquire()
    if boat.broken:
        boat.reset()       
    boat.wait()
    lock.acquire()
    abordar("hacker",num)
    lock.release()
'''
Función que representa como se van formando los serfs y 
las condiciones necesarias para el abordaje. 
Recibe num: el número de hilo
'''
def serf(num):
    global hackers
    global serfs
    mutex.acquire()
    serfs +=1
    if serfs == 4:
        permitePa(serfqueue,4)
        serfs -= 4
        mutex.release()
    elif serfs == 2 and hackers >= 2:
        permitePa(hackerqueue,2)
        permitePa(serfqueue,2)
        hackers -= 2
        mutex.release()
    else:
        mutex.release()
    serfqueue.acquire()
    if boat.broken:
        boat.reset()       
    boat.wait()
    lock.acquire()
    abordar("serf",num)
    lock.release()
'''
Función que es llamda cada vez que una pasajero aborda.
Recibe 
s:una cadena 
num: número de hilo
'''
def abordar(s,num):
    global pasajeros
    pasajeros +=1
    print ('acabo de abordar y soy un '+s+' mi numero es', num)
    if pasajeros==4:#si hay 4 pasajeros a bordo 
        balsa()#se llama la función para que se vaya la balsa
        pasajeros=0#se reinicia le contador de pasajeros
'''
Funcíon que hace que la balsa se vaya
'''
def balsa():
    global numbal
    numbal += 1
    time.sleep(.5)
    print('La balsa ', numbal, 'se ha ido')
'''
Función que da paso a ciertos hilos de pasar un numero de veces, aumenta los semaforos para que sean adquiridos
Recibe:
self: un objeto, en este caso de tipo semaforo
times: numero en qeu se aumentara el smeaforo
'''
def permitePa(self,times):
    for i in range(times):
        self.release()


for i in range(10):
    threading.Thread(target = hacker, args = [i]).start()
    threading.Thread(target=serf, args = [i]).start()
