#+/usr/bin/python
# *-* Encoding: utf-8 *-*
#
# Ilustra el uso de un Mutex
#
# Presentado en la clase del 01/09/2016.
#
# Comparar los resultados de la primera ejecución (sin mutex) y la
# segunda ejecución (con mutex).

import time
import threading

global mutex
global contador

mutex = threading.Lock()

def escalerita_con_mutex(yo):
    global contador
    mutex.acquire()
    contador = 0
    time.sleep(0.1)
    while contador < 10:
        print "%d=>%d" % (contador, yo)
        contador += 1
        time.sleep(0.1)
    mutex.release()

def escalerita_sin_mutex(yo):
    global contador
    contador = 0
    time.sleep(0.1)
    while contador < 10:
        print "%d => %d" % (contador, yo)
        contador += 1
        time.sleep(0.1)

print "Ejecución del código sin mutex:"
for i in range(4):
    threading.Thread(target = escalerita_sin_mutex, args = [i]).start()

time.sleep(2)

print "Ejecución del código sin mutex:"
for i in range(4):
    threading.Thread(target = escalerita_con_mutex, args = [i]).start()

time.sleep(2)
