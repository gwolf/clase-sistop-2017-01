#!/usr/bin/python
# -*- Encoding: utf-8 -*-
#Nombre: Carlos Alberto Díaz Olivares

import threading
import time

global reno
global elfo

reno = 0
elfo = 0

mutex = threading.Semaphore(1)
santa = threading.Semaphore(0)

def llegaReno():
	global reno
	mutex.acquire()
	reno+=1
	print 'Llega un reno = %d' % (reno)
	if reno >= 9:
		santa.release()
	mutex.release()

def llegaElfo():
	global elfo
	mutex.acquire()
	elfo+=1
	print 'Llega un elfo = %d' %(elfo)
	if elfo == 3:
		santa.release()
		print'3 elfos llamamos a santa'
	mutex.release()

def despiertaSanta():
	global elfo
	global reno
	while True:
		santa.acquire()
		print 'santa despierta'
		mutex.acquire()
#	print 'Mutex adquirido por santa'
		if reno >= 9:
			print 'Iniciamos recorrido'
			print 'Mandamos de Vacaciones a los Renos'
			reno -= 9
		elif elfo >= 3:
			print 'Ayudando Elfos'
			elfo -=3
		print 'santa duerme'
		mutex.release()

threading.Thread(target = despiertaSanta, args = []).start()
while True:
	threading.Thread(target = llegaElfo, args = []).start()
	time.sleep(1)
	threading.Thread(target = llegaReno, args = []).start()
	time.sleep(0.15)
