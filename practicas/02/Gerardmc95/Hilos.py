import threading
import time
def trabajador():
  print threading.currentThread().getName(), 'Lanzado'
  print "Estoy trabajando" 
  time.sleep(2)
  print threading.currentThread().getName(), 'Deteniendo'
def servicio():
  print threading.currentThread().getName(), 'Lanzado'
  print threading.currentThread().getName(), 'Deteniendo'

t = threading.Thread(target=servicio, name='Servicio')
w = threading.Thread(target=trabajador, name='Trabajador')
z = threading.Thread(target=trabajador)
w.start()
z.start()
t.start()