# -*- coding: utf-8 -*-
"""
Created on Sun Sep 18 19:14:38 2016

@author: MigueBlogs
"""


from threading import Thread
#from threading import Lock
#Intento fallido numero 1
#global lleno
#global pasajeros
#lleno = threading.Semaphore(0)
#pasajeros=[]
#
#def abordar():
#    global pasajeros
#    pasajeros.append("Ha subido un pasajero")
#    lleno.release()
#    ...
#    
#def sarpar():
#    global pasajeros
#    ...
#    
#linux =Thread(target=sarpar, args=[])
#microsoft =Thread(target=abordar, args=[])

#página 100 libro lectores-escritores
#Intento numero 2
import threading

#lectores = 0
Plinux=0
Pmicrosoft=0
mutex = threading.Semaphore(1)
cuarto_vacio = threading.Semaphore(1)
torniquete = threading.Semaphore(1)

def linux():
    torniquete.acquire()
    cuarto_vacio.acquire()
    
    escribe()
    #si pasajero = microsoft
        #no sarpes

    cuarto_vacio.release()
    torniquete.release()
    
def lector():
    global lectores
    torniquete.acquire()
    torniquete.release() #Porque lo suelta y lo libera tan seguido?
    mutex.acquire()
    lectores = lectores + 1
    if lectores == 1:
        cuarto_vacio.acquire()
    mutex.release()
    
    lee()
    
    mutex.acquire()
    lectores = lectores - 1
    if lectores == 0:
        cuarto_vacio.release()
    mutex.release()
    
for i in range(0,10):
    linux =Thread(target=escritor, args=[])
    microsoft =Thread(target=lector, args=[])
    linux.start()
    microsoft.start()
