from collections import deque
import random

base = 0
fila = 1
tiempoComienzo = 0
tiempoFinalizacion = 0
tiempoEspera = 0

FIFO = deque([])
lista = []

#Diccionarios para guardar tiempos y tabla de tiempos
tiempoLlegada = {}
tiempoDuracion = {}
tabla = {}
titulo = ['Proceso', 'Llegada', 'Duracion', 'Comienzo', 'Finalizacion', 'Espera']

# Agregando elementos a FIFO
FIFO.appendleft('a')
FIFO.appendleft('b')
FIFO.appendleft('c')
FIFO.appendleft('d')
FIFO.appendleft('e')

#Les damos tiempo de llegada y duracion a cada proceso
for i in reversed(FIFO):
  if i == 'a':
    tiempoLlegada[i] = 0
    tiempoDuracion[i] = random.randint(1,10)
  else:
    tiempoLlegada[i] = random.randint(base,base+3)
    tiempoDuracion[i] = random.randint(1,10)
  base += 3
  lista.append(tiempoLlegada[i])

#Mientras FIFO no este vacio seguira en ejecucion
while FIFO:
  proceso = FIFO.pop() #Proceso asignado a ejecucion
  #Medidas de diversos tiempos
  tiempoFinalizacion += tiempoDuracion[proceso]
  tiempoComienzo = tiempoFinalizacion - tiempoDuracion[proceso]
  tiempoEspera = (tiempoFinalizacion-tiempoLlegada[proceso])-tiempoDuracion[proceso]
  #Guardamos cada tiempo en un diccionario para imprimirlo en forma de tabla
  tabla[fila] = [proceso, tiempoLlegada[proceso], tiempoDuracion[proceso], tiempoComienzo, tiempoFinalizacion, tiempoEspera]
  fila += 1


#Impresion de la tabla de tiempo
for i in titulo:
  print i,"\t",
print

for i in tabla:
  for j in tabla[i]:
    if j < 0 :
      print "   0\t\t",
    else:
      print "  ", j, "\t\t",
  print