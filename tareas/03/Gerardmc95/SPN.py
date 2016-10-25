from collections import deque
import random

b=0
fila = 1
tiempoComienzo = 0
tiempoFinalizacion = 0
tiempoEspera = 0
procA = False

SPN = deque([])
lista = []
listaDos = []

#Diccionarios para guardar tiempos y tabla de tiempos
tiempoLlegada = {}
tiempoDuracion = {}
tabla = {}
titulo = ['Proceso', 'Llegada', 'Duracion', 'Comienzo', 'Finalizacion', 'Espera']

# Agregando elementos a SPN
SPN.appendleft('a')
SPN.appendleft('b')
SPN.appendleft('c')
SPN.appendleft('d')
SPN.appendleft('e')

#Damos duracion a cada proceso
for i in reversed(SPN):
  if i == 'a':
    tiempoLlegada[i] = 0
    tiempoDuracion[i] = random.randint(1,10)
  else:
    tiempoLlegada[i] = random.randint(1,5)
    tiempoDuracion[i] = random.randint(1,10)
  lista.append(tiempoLlegada[i])

#Ordenacion de los valores por tamano de duracion del diccionario 'tiempoLlegada'
ordenada = tiempoDuracion.items()
ordenada.sort(key=lambda x : x[1])

#Mientras SPN no este vacia se ejecutaran los procesos
while SPN:
  #Evitamos que el primer proceso ssea ignorado y tenga fallas el programa
  if procA == True:
    listaAux = ordenada[b]
    proceso = listaAux[0]
    b += 1
    SPN.pop() #Vamos quitando proceso por preoceso para vaciar 'SPN'
  else:
    proceso = SPN.pop()
    procA = True
  #Medidas de diversos tiempos a partir del proceso elegido a ejecutar
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