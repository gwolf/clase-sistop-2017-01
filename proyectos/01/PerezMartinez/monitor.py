#!/usr/bin/env python
# *-* encoding: utf-8 *-*
import threading
import time
from Tkinter import *
import re


#Se define el tamaño del cuadro de scroll#
def myfunction(event):
    canvas.configure(scrollregion=canvas.bbox("all"),width=800,height=600)

#Se define tamaños para la interfaz TKinter#
root = Tk()
sizex = 800
sizey = 600
posx  = 100
posy  = 100
root.wm_geometry("%dx%d+%d+%d" % (sizex, sizey, posx, posy))

#Se inicializá el frame donde se actualizaran los datos
myframe=Frame(root,relief=GROOVE,width=50,height=100,bd=1)
myframe.place(x=10,y=10)

canvas=Canvas(myframe)
frame=Frame(canvas)
#Se define el scrollbar
myscrollbar=Scrollbar(myframe,orient="vertical",command=canvas.yview)
canvas.configure(yscrollcommand=myscrollbar.set)

myscrollbar.pack(side="right",fill="y")
canvas.pack(side="left")
canvas.create_window((0,0),window=frame,anchor='nw')
frame.bind("<Configure>",myfunction)

#Creación del grupo de semaforos para el flujo de hilos
memSemaphore = threading.Semaphore(0)
cpuSemaphore = threading.Semaphore(0)
aboutDiskSemaphore = threading.Semaphore(0)

#Funcion para obtencion de datos de la memoria
def mem():
    memSemaphore.acquire()
    #Este es el segundo hilo en ser ejecutado
    #Abre directoriio que contiene la memoria
    memState = open("/proc/meminfo","r")
    memInfo = memState.readlines()
    #Seleccion de datos convenientes de memoria
    allMemInfo = memInfo[0]+memInfo[1]+memInfo[2]+memInfo[14]+memInfo[15]
    memState.close()
    #Impresion de texto en el frame
    memStats = Label(frame,justify=LEFT,text=allMemInfo).grid(row=1,column=0)
    #Se libera el siguiente hilo
    cpuSemaphore.release()

#Esta función generá al terminar un flujo de hilos para mantener actualizado el frame
def monitor():
 threading.Thread(target=disk,args=[]).start()
 threading.Thread(target=mem,args=[]).start()
 threading.Thread(target=cpuStats,args=[]).start()
 threading.Thread(target=aboutDisk,args=[]).start()

#Obtencion de datos del disco
def disk():
    #Este es el primer hilo en ser ejecutado
    #Abre el directorio donde contiene informacion del disco
    discState = open("/proc/diskstats","r")
    infoDisk = discState.read()
    #Se edita el espacio de informacion del disco
    infoDisk = "Estado del disco\n"+re.sub(" ","     ",infoDisk)
    discState.close()
    diskStates(infoDisk)

#Imprime en el frame la informacion del disco
def diskStates(infoDisk):
    #Se imprime en el frame la informacion de disco
    diskLabel = Label(frame,text=infoDisk,justify=LEFT).grid(row=0,column=0)
    #Se libera el siguiente hilo
    memSemaphore.release()
    #root.after mantendrá actualizado el frame cada segundo, el cual es llamado al finalizar un flujo de hilos
    root.after(1000,monitor)

#Obtiene informacion del cpu
def cpuStats():
    cpuSemaphore.acquire()
    #Este es el tercer hilo en ser ejecutado
    #Abre directorio que contiene informacion del cpu
    cpuState = open("/proc/stat","r")
    cpuInfo = cpuState.readlines()
    #Se elige la informacion mas reelevante
    allcpuInfo = cpuInfo[9]+cpuInfo[10]
    cpuState.close()
    #Se imprime en el frame la informacion del cpu
    memStats = Label(frame,text=allcpuInfo,justify=LEFT).grid(row=2,column=0)
    #SE libera el siguiente hilo
    aboutDiskSemaphore.release()

def aboutDisk():
    #Cuarto hilo en ser ejecutado
    aboutDiskSemaphore.acquire()
    #Se dan detalles de cata columna del disco
    aboutDiskStat = "Detalles de cada columna del estado del disco:\n1 - major number\n 2 - minor number\n 3 - Nombre del dispositivo\n 4 - Lecturas completadas satisfactoriamente\n 5 - lecture merged\n 6 - sectores leídos\n 7 - Tiempo gastado leyendo (ms)\n 8 - Escrituras completadas\n 9 - writes merged\n 10 - Sectores que han sido escritos\n 11 - tiempo gastado Esccribiendo (ms)\n 12 -  I/Os actualmente en progreso\n 13 - Tiempo gastado haciendo I/Os (ms)"
    #imprime en el frame la informacion de cada columna del estado del disco
    memStats = Label(frame,text=aboutDiskStat,justify=LEFT).grid(row=3,column=0)


#Hilos que se lanzan al inció de la ejecucín
threading.Thread(target=mem,args=[]).start()
threading.Thread(target=disk,args=[]).start()
threading.Thread(target=cpuStats,args=[]).start()
threading.Thread(target=aboutDisk,args=[]).start()

#lanza el frame
root.mainloop()


