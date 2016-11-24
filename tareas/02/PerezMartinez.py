#!/usr/bin/env python  
# *-* encoding: utf-8 *-*          

#La resolucion de este proble consiste en hacer un semaforo en la interseccion donde solo permitirá que solo un par de autos pase a la vez. Por otro lado se agrego otro semáforo que controla si dos autos que se les dio el paso pero estos van a encontrarse en la misma dirección, permita el paso a una a la vez para evitar el choque, una vez que termina de crusar ambos coches pueden pasar los de el otro sentido, con las mismas condiciones anteriores. Así se resuelve el problema de la inanición o del bloque mutuo
#               2 1
#               | |
#              =   = (Carril inferior 3 y carril superior 4)
#               | |

#El carro uno va verticalmente hacia arriba
#el carro dos va verticalmente hacia abajo

#El carril tres va en dirección horizontal, avanza hacia la derecha
#El carril cuatro va en dirección Horizontal, avanza hacia la izquierda

#Sentido 1 es sigue su curso actual
#sentido 2 gira a la derecha
#sentido 3 gira a la izquierda

import threading
import time
import random

#Semaforo que controla el cruce central
pasa = threading.Semaphore(0)
choqueV =threading.Semaphore(0)

#cuando dos autos van en la misma direccion permite que solo pase uno a la vez
def evitaChoque(nombre):
    print("--------pasa "+nombre)
    if nombre == "carro1" or nombre == "carro2":
        choqueV.release()
    else: 
        choqueH.release
    

#Este es el cruce central donde interseccionan loas autos
def cruceCentral(direccion,cualAuto):
    if cualAuto == "carro1":
        print("Cruce de autos verticales")
        infoAuto2=auto2()
        if direccion == 2 and infoAuto2[0] == 2:
            print("Cada carro gira a su derecha")
        if direccion == 3 and infoAuto2[0] == 3:
            print("cada carro gira a su izquierda")
        if direccion == 1 and infoAuto2[0] == 1:
            print("--------auto uno y dos siguen de frente")
        if direccion == 2 and (infoAuto2[0] == 1 or infoAuto2[0] == 2):
            print("--------auto1 gira en direccion 2")
            print("--------nauto2 va den direccion "+str(infoAuto2[0]))
        if infoAuto2[0] == 2 and (direccion == 1 or direccion == 2): 
            print("--------auto2 gira en direccion 2")
            print("--------auto1 va den direccion "+str(direccion))
        #señalizaciones para cuando dos autos van en el mismo sentido
        if infoAuto2[0] == 2 and cualAuto == 3:
            threading.Thread(target=evitaChoque,args=cualAuto).start()
            choqueV.acquire()
            threading.Thread(target=evitaChoque,args=infoAuto2[1]).start()
        if infoAuto2[0] == 3 and cualAuto == 2:
            threading.Thread(target=evitaChoque,args=cualAuto).start()
            choqueV.acquire()
            threading.Thread(target=evitaChoque,args=infoAuto2[1]).start()
        if infoAuto2[0] == 1 and cualAuto == 3:
            threading.Thread(target=evitaChoque,args=cualAuto).start()
            choqueV.acquire()
            threading.Thread(target=evitaChoque,args=infoAuto2[1]).start()
        if infoAuto2[0] == 3 and cualAuto == 1:
            threading.Thread(target=evitaChoque,args=cualAuto).start()
            choqueV.acquire()
            threading.Thread(target=evitaChoque,args=infoAuto2[1]).start()
            
    else:
        print("El paso es seguro")
        pasa.release()
        
    #Condiciones de cruce
    if cualAuto == "auto3":
        print("Cruce de autos Horizontales")
        infoAuto4=auto4()
        if direccion == 2 and infoAuto4[0] == 2:
            print("Cada carro gira a su derecha")
        if direccion == 3 and infoAuto4[0] == 3:
            print("cada carro quira a su izquierda")
        if direccion == 1 and infoAuto4[0] == 1:
            print("--------auto tres y cuatro siguen de frente")
        if direccion == 2 and (infoAuto4[0] == 1 or infoAuto4[0] == 2):
            print("--------auto3 gira en direccion 2")
            print("--------auto4 va den direccion "+str(infoAuto4[0]))
        if infoAuto4[0] == 2 and (direccion == 1 or direccion == 2):
            print("--------auto4 gira en direccion 2")
            print("--------auto3 va den direccion "+str(direccion))

#En esta partes tuve problemas al llamar a evitaChoque, a pesar de que señalizo cuando debe entrar algunas veces marca error como si estuviera recibiendo más de un argumento

        #if infoAuto4[0] == 2 and direccion == 3:
            #threading.Thread(target=evitaChoque,args=infoAuto4[1]).start()
            #choqueH.acquire()
            #threading.Thread(target=evitaChoque,args=cualAuto).start()
        #if direccion == 3 and infoAuto4[0] == 2:
            #threading.Thread(target=evitaChoque,args=cualAuto).start()
            #choqueH.acquire()
            #threading.Thread(target=evitaChoque,args=infoAuto4[1]).start()
        #if direccion == 1 and infoAuto4[0] == 3:
            #threading.Thread(target=evitaChoque,args=cualAuto).start()
            #choqueH.acquire()
            #threading.Thread(target=evitaChoque,args=infoAuto4[1]).start()
        #if direccion == 3 and infoAuto4[0] == 1:
            #threading.Thread(target=evitaChoque,args=cualAuto).start()
            #choqueH.acquire()
            #threading.Thread(target=evitaChoque,args=infoAuto4[1]).start()
    else:
        print("el paso es seguro")

    pasa.release()
    time.sleep(4)
    main()
        
#auto en direccion 1
def auto1():
    nombre = "carro1"
    direccion = sentidos()
    cruceCentral(direccion,nombre)

#auto en direccion 2
def auto2():
    nombre = "auto2"
    direccion = sentidos()
    return(direccion,nombre)

#auto en direccion 3
def auto3():
    pasa.acquire()
    nombre = "auto3"
    direccion = sentidos()
    cruceCentral(direccion,nombre)

#auto en direccion 4
def auto4():
    nombre = "auto4"
    direccion = sentidos()
    return(direccion,nombre)

#da un sentido aleatorio ak giro del auto
def sentidos():
    return random.randint(1, 3)

#Lanza el trafico
def main():
    threading.Thread(target=auto1,args=[]).start()
    threading.Thread(target=auto2,args=[]).start()
    threading.Thread(target=auto3,args=[]).start()
    threading.Thread(target=auto4,args=[]).start()

main()
