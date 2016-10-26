from collections import deque
import random

letra = ord('a')
b=0
totalEjecucion = 0
casillas = 0

RR = deque([])
lista = []
listaZ = []

#Diccionarios para guardar tiempos y tabla de tiempos
tiempoLlegada = {}
tiempoDuracion = {}
tiempoDuracionDos = {}
titulo = ['Proceso', 'Llegada', 'Duracion']

# Agregando elementos a RR
RR.appendleft('a')
RR.appendleft('b')
RR.appendleft('c')
RR.appendleft('d')
RR.appendleft('e')

#Damos duracion a cada proceso
for i in reversed(RR):
  if i == 'a':
    tiempoLlegada[i] = 0
    tiempoDuracion[i] = random.randint(1,10)
    tiempoDuracionDos[i] = tiempoDuracion[i]
    totalEjecucion += tiempoDuracion[i]
  else:
    tiempoLlegada[i] = random.randint(1,3)
    tiempoDuracion[i] = random.randint(1,10)
    tiempoDuracionDos[i] = tiempoDuracion[i]
    totalEjecucion += tiempoDuracion[i]
  lista.append(tiempoLlegada[i])


#Ordenacion de los valores por tamano de duracion del diccionario 'tiempoLlegada' para dar una porcion equitativa
ordenada = tiempoDuracion.items()
ordenada.sort(key=lambda x : x[1])

#Una porcion justa en este caso seria la del procesos mas pequeno
listaAux = ordenada[b]
porcion = listaAux[1]

#Impresion de la tabla de tiempo
for i in titulo:
  print i,"\t",
print

for i in range(5):
  print chr(i+65),"\t\t",tiempoLlegada[chr(i+97)],"\t\t",tiempoDuracionDos[chr(i+97)]
print

#Funcion que coloca los segmentos de los procesos en forma de lista para simular los pedazos de los mismos
def cortador(let, diccionarioLet, porcionLet,listaLet):
  tam = diccionarioLet[let]
  #Si "tam >= porcion" da a entender que ese proceso tendra una longitud mayor a cero despues de quitarle un pedazo
  if tam >= porcion:
    for i in range(porcion-1):
      print chr(ord(let)-32),
      listaLet.append(let)
    diccionarioLet[let] = tam - porcionLet
    return porcionLet
  #Si "tam < porcion" da a entender que ese proceso tendra una longitud igual a cero despues de quitarle un pedazo
  elif (tam < porcionLet) and (tam > 0):
    for i in range(tam-1):
      print chr(ord(let)-32),
      listaLet.append(let)
    diccionarioLet[let] = 0
    return tam
  #Si no hay nada de proceso, simplemente no agregamos nada a la listaZ
  else:
    return 0

#While que se asegura los procesos se formen debidamente
while casillas < totalEjecucion:
  #casillas cortara el while, y cortador es la funcion que recibe nombre de proceso, duracion, porcion a cortar y listaZ donde se guardaran
  #los pedazos de cada proceso
  casillas += cortador(chr(letra), tiempoDuracion, porcion, listaZ)
  if letra < 101:
    letra += 1
  else:
    letra = 97