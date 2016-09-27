# -*- coding: utf-8 -*-
"""
Created on Sun Sep  4 22:31:39 2016

@author: MigueBlogs
"""

#!/usr/bin/python
# Nombre de Fichero : mutex.py

import threading
from time import sleep
mutex = threading.Lock()
class Hilo(threading.Thread):
    def __init__(self, id):
        threading.Thread.__init__(self)
        self.id = id

    def run(self):
        mutex.acquire()
        sleep(3-self.id)
        print ("Yo soy %s la variable d tiene el valor %s") %self.id,d
        mutex.release()

d=1;
hilos = [Hilo(1),
Hilo(2),
Hilo(3)]

for h in hilos:
    h.start()