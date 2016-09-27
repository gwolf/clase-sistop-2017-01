#!/usr/bin/python
# *-* encoding: utf-8 *-*
import threading
import time

k = 10
eventos = threading.Semaphore(0)
red = threading.Semaphore(0)

def jefe():
    global k
    for i in range(k):
        lanza_hilo()
    while True:
        red.acquire()
        print "Llegó un evento por la red"
        eventos.release()
        lanza_hilo()

def trabajador():
    eventos.acquire()
    procesa_evento()
    return 0

def procesa_evento():
    print "¡Qué bonito evento me tocó procesar!"

def lanza_hilo():
    threading.Thread(target=trabajador, args=[]).start()

threading.Thread(target=jefe, args=[]).start()
while True:
    time.sleep(1)
    red.release()
