# -*- coding: utf-8 -*-
"""
Created on Mon Sep  5 21:58:11 2016

@author: MigueBlogs
"""
import threading
import tempfile

mutex = threading.Semaphore(1)
elementos = threading.Semaphore(0)
buffer=[]


def productor():
    while True:
        event=genera_evento()
        mutex.acquire()
        buffer.append(event)
        mutex.release()
        elementos.release()

def consumidor():
    while True:
        elementos.acquiere()
        with mutex:
            event = buffer.pop()
        event.process()
        
def genera_evento():
    tempfile.TemporaryFile(mode='w+b', buffering=None, encoding=None, newline=None, suffix=None, prefix=None, dir=None)
    
    
    

threading.Thread(target=productor, args=[]).start()
threading.Thread(target=consumidor, args=[]).start()