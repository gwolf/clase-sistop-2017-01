# -*- coding: utf-8 -*-
"""
Created on Mon Sep  5 22:13:38 2016
No me quiero adjudicar todos los creditos, idea tomada y adapatada de:
http://stackoverflow.com/questions/3310049/proper-use-of-mutexes-in-python
Python v3.5
@author: MigueBlogs
"""
import time
from threading import Thread
from threading import Lock
import tempfile

def hazAlgo(i, mutex):
    mutex.acquire()  #Mutex iniciado
    temporal = tempfile.TemporaryFile(mode='w+t') #Se crea archivo temporal
    temporal.write("Thread: %d" %(i))
    time.sleep(0.5)
    temporal.seek(0)
    lectura = temporal.read()
    print(lectura)
    temporal.close()
    mutex.release()     #Fin de Mutex

mutex = Lock()
for i in range(0,10): #Este For genera todos mis hilos 
    t = Thread(target=hazAlgo, args=(i,mutex)) #Crea Hilo
    t.start()
    print ("Ciclo principal %s" % (i))