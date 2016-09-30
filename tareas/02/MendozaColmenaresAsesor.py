'MENDOZA COLMENARES GERARDO'
'PROBLEMA: LOS ALUMNOS Y  EL ASESOR'
'ALUMNOS MAXIMOS PERMITIDOS POR ASESORIA = 3'
'PREGUNTAS MAXIMAS = 2'
import threading
import time
import random

alumnos = 0
auxiliarPreguntas = 0
turno = 0
dicAlumnos = {}

mutex = threading.Semaphore(1)
mano = threading.Semaphore(1)
cubiculo_vacio = threading.Semaphore(1)
torniquete = threading.Semaphore(1)

#Funcion que asesora al alumno que pregunto
def asesora(num):
    print "Asesorando al alumno %d\n" % num
    time.sleep(0.5)

#Funcion que hace preguntar al alumno
def pregunta(num,preguntasMax):
    print "El alumno %d pregunta por %da vez" % (num,preguntasMax)
    print "El alumno %d ya termino de preguntar" % num
    time.sleep(0.5)
    asesora(num)

#Funcion que duerme al asesor y reinicia el contador de hilos alumno
def asesor():
    global hilos_alum 
    cubiculo_vacio.acquire()
    print "--->EL ASESOR ESTA DORMIDO<---\n"
    hilos_alum = 1
    time.sleep(2.5)
    cubiculo_vacio.release()

#Funcion que controla a los alumnos para que no se cruzen sus preguntas y hagan ciertas preguntas como maximo
def alumno(num):
    global alumnos
    
    print "El alumno %d se para a tocar la puerta y entra" % num
    mutex.acquire()
    dicAlumnos[str(unichr(num+48))] = 0
    mutex.release()

    torniquete.acquire()
    torniquete.release()

    turno = 0
    while ((dicAlumnos[str(unichr(num+48))] != 2) and (turno < 2)):

      mano.acquire()
      mutex.acquire() 
      alumnos = alumnos + 1
      if alumnos == 1:
	  cubiculo_vacio.acquire()
      auxiliarPreguntas = dicAlumnos[str(unichr(num+48))]
      auxiliarPreguntas += 1
      dicAlumnos[str(unichr(num+48))] = auxiliarPreguntas
      pregunta(num, auxiliarPreguntas)
      mutex.release()
      mano.release()
      time.sleep(0.3)

      mutex.acquire()
      turno += 1
      if dicAlumnos[str(unichr(num+48))] == 2:
	alumnos -=2
	if alumnos == 0:
	  cubiculo_vacio.release()
	  asesor()
      mutex.release()
      time.sleep(0.2)

#Iniciar hilos alumno a 1 (Pues no existen alumnos 0)
hilos_alum = 1
#Mientras True siempre lanzara hilos
while True:
#Control del maximo numero permitido de alumnos
  while (hilos_alum < 4):
    time.sleep(0.05)
    if random.random() < 0.05:
      threading.Thread(target=alumno, args=[hilos_alum]).start()
      hilos_alum += 1
