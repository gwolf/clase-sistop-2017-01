#!/usr/bin/python
# -*- Encoding: utf-8 -*-
# Uso del patrón de semáforo "señalizar"
#
# Ojo, semáforo inicializado a 0
import threading

global yasta
global datos
yasta = threading.Semaphore(0)
datos = []

def primera_mitad():
    global datos
    datos.append('Hola')
    yasta.release()

def segunda_mitad():
    global datos
    yasta.acquire()
    datos.append('Mundo')
    print datos

t1 = threading.Thread(target=segunda_mitad, args=[])
t2 = threading.Thread(target=primera_mitad, args=[])

t1.start()
t2.start()


