#Mendoza Colmenares Gerardo
#Primer proyecto basado en monitoreo de procesos mediante multihilos

#En este primer archivo se intentara hacer uso de multiilos cuando se manden a llamar a ciertos comandos
#me reservo algunos comentarios en este primer intentp pues es seguro corrija despues ciertas cosas

#CORRECCIONES
#Lograr acabar el programa cuando se pone exit
#Borrar ciertas instrucciones que llenaban la pantalla con demasiada informacion que hacia dificil la lectura
#Evitar que la pantalla se borrara al llamar hilos

import wx
import threading
import time
import os

semaforo = threading.Semaphore(1)
thr = 0

def SYSTEM():
  global semaforo
  semaforo.acquire()
  print "/////SYSTEM INFO/////\n"
  os.system("arch") #Mostrar arquitectura de la maquina
  os.system("uname -r") #Mostrar la version del kernel usado
  #os.system("dmidecode -q") #Mostrar el hardware del sistema
  semaforo.release()

def HDD():
  global semaforo
  semaforo.acquire()
  print "/////HDD/////\n"
  #os.system("du -h") #Descubre archivos mas grandes del sistema
  os.system("tree") #Mostrar los ficheros y carpetas en forma de arbol comenzando por la raiz.
  semaforo.release()
  
def MEMORY():
  global semaforo
  semaforo.acquire()
  print "/////MEMORY/////\n"
  os.system("free") #Se visualiza la cantidad total de memoria libre, la memoria fisica utilizada y el intercambio en el sistema
  os.system("cat /proc/meminfo") #Verificar el uso de memoria
  semaforo.release()

def PROCESS():
  global semaforo
  semaforo.acquire()
  print "/////PROCESS/////\n"
  os.system("ps") #Muestra una instantanea de los procesos actuales
  os.system("pstree") #Muestra procesos actuales en forma de arbol
  semaforo.release()
  
def CPU():
  global semaforo
  semaforo.acquire()
  print "/////CPU/////\n"
  os.system("cat /proc/cpuinfo") #Mostar informacion del CPU
  semaforo.release()

def CLEAR():
  global semaforo
  semaforo.acquire()
  os.system("clear")
  semaforo.release()

def COMMAND(opcion):
  #Lanzador de hilos
  global hilo
  global thr
  if (opcion == "system"):
    filament = threading.Thread(target = SYSTEM)
    filament.start()
  elif (opcion == "disk"):
    filament = threading.Thread(target = HDD)
    filament.start()
  elif (opcion == "memory"):
    filament = threading.Thread(target = MEMORY)
    filament.start()
  elif (opcion == "process"):
    filament = threading.Thread(target = PROCESS)
    filament.start()
  elif (opcion == "cpu"):
    filament = threading.Thread(target = CPU)
    filament.start()
  elif (opcion == "clear"):
    filament = threading.Thread(target = CLEAR)
    filament.start()
  elif (opcion == "help"):
    print "INSERTAR AYUDA"
  elif (opcion == "all"):
    hilo()
  elif (opcion == "exit"):
    print "ADIOS :V"
    thr = 1
  else:
   print "Opcion invalida"
def hilo():
  filament0 = threading.Thread(target = SYSTEM)
  filament0.start()
  filament1 = threading.Thread(target = HDD)
  filament1.start()
  filament2 = threading.Thread(target = MEMORY)
  filament2.start()
  filament3 = threading.Thread(target = PROCESS)
  filament3.start()
  filament4 = threading.Thread(target = CPU)
  filament4.start()

def MONITOR():
  global opcion, thr, semaforo
  os.system("clear")
  while thr == 0:
      time.sleep(.5)
      print "===>COMANDOS<===\n"
      print "system\tdisk\tmemory\tprocess\tcpu\tall\tclear\thelp\texit"
      opcion = raw_input("wifislax@sudo$")
      COMMAND(opcion)
  semaforo.release()

MONITOR()