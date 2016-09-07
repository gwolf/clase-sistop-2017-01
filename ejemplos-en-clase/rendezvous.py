#!/usr/bin/python
# -*- Encoding: utf-8 -*-
# Uso de los patrones de semáforo "rendezvous" y "signal"
import threading
import time
import random

yasta = threading.Semaphore(0)
vamos1 = threading.Semaphore(0)
vamos2 = threading.Semaphore(0)
datos = []

def primera_mitad():
    global datos

    vamos1.release()
    vamos2.acquire()
    print "¡Listo 1!"

    datos.append('Hola')

    yasta.release()

def segunda_mitad():
    global datos

    print "Estamos listos para comenzar, el arreglo está vacío:"
    print datos

    vamos2.release()
    vamos1.acquire()
    print "¡Listo 2!"

    yasta.acquire()

    datos.append('Mundo')
    print datos

t1 = threading.Thread(target=segunda_mitad, args=[])
t2 = threading.Thread(target=primera_mitad, args=[])

t1.start()
t2.start()


