#!/usr/bin/python
# -*- Encoding: utf-8 -*-
#
# Implementación ejecutable del ejemplo de nuestro libro de texto
# (agregando las funciones escribe() y lee(), demoras para ambos
# roles, lanzamiento de los hilos)
import threading
import time
import random
lectores = 0
mutex = threading.Semaphore(1)
cuarto_vacio = threading.Semaphore(1)
torniquete = threading.Semaphore(1)

def escribe(num):
    print "Entra el escritor %d" % num
    time.sleep(0.8)

def lee(num):
    print "Entra el lector %d" % num
    time.sleep(0.2)

def escritor(num):
    print "El escritor %d se para a esperar pacientemente" % num
    torniquete.acquire()
    cuarto_vacio.acquire()
    escribe(num)
    cuarto_vacio.release()
    torniquete.release()
    print "El escritor %d ya terminó" % num

def lector(num):
    print "El lector %d se para a esperar pacientemente" % num
    global lectores
    torniquete.acquire()
    torniquete.release()

    mutex.acquire()
    lectores = lectores + 1
    if lectores == 1:
        cuarto_vacio.acquire()
    mutex.release()

    lee(num)

    mutex.acquire()
    lectores = lectores - 1
    if lectores == 0:
        cuarto_vacio.release()
    mutex.release()
    print "El lector %d ya terminó" % num

hilos_lect = 0
hilos_escr = 0
while True:
    time.sleep(0.05)
    if random.random() < 0.05:
        threading.Thread(target=escritor, args=[hilos_escr]).start()
        hilos_escr += 1
    else:
        threading.Thread(target=lector, args=[hilos_lect]).start()
        hilos_lect += 1
