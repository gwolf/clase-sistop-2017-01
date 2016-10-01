#Mendoza Colmenares Gerardo
#Primer proyecto basado en monitoreo de procesos mediante multihilos

#En este primer archivo se intentara hacer uso de multiilos cuando se manden a llamar a ciertos comandos

#CORRECCIONES
#Lograr ejecutar una ventana con casilla de seleccion


import wx
import threading
import time
import os

#Diccionario que guarda las selecciones de la ventana para posterior ejecucion
diccionarioElegidos = {'system':True, 'disk':True, 'memory':True, 'process':True, 'cpu':True, 'color':True}

semaforo = threading.Semaphore(1)
thr = 0

'------------------------------------------------------Ventana de casillas desde wxpython------------------------------------------------------'
#Definimos la clase OpcionesMonitor que contenga cada uno de los botones y casilla a usar
class OpcionesMonitor(wx.Frame):
  def __init__(self, parent, id, title):
    wx.Frame.__init__(self, parent, id, title, size=(250, 170))#Tamano de la ventana

    #Declaro un panel de wxpython
    ventanaCasillas = wx.Panel(self, -1)

    #Declaro casillas con metodo CheckBox que las liga al panel, le da un nombre, un tamano y una posicion
    #con el metodos SetValue le doy un bool como valor que sera si aparece la casilla con o sin seleccion; True = Activada | False = Desactivada 
    #con EVT_CHECKBOX puedo leer cada que se use la casilla, obteniendo un valor booleano
    self.cb = wx.CheckBox(ventanaCasillas, -1, 'system', (10, 10))
    self.cb.SetValue(True)
    wx.EVT_CHECKBOX(self, self.cb.GetId(), self.boolSystem)

    self.cb = wx.CheckBox(ventanaCasillas, -1, 'disk', (120, 10))
    self.cb.SetValue(True)
    wx.EVT_CHECKBOX(self, self.cb.GetId(), self.boolDisk)

    self.cb = wx.CheckBox(ventanaCasillas, -1, 'memory', (10, 45))
    self.cb.SetValue(True)
    wx.EVT_CHECKBOX(self, self.cb.GetId(), self.boolMemory)
    
    self.cb = wx.CheckBox(ventanaCasillas, -1, 'process', (120, 45))
    self.cb.SetValue(True)
    wx.EVT_CHECKBOX(self, self.cb.GetId(), self.boolProcess)
    
    self.cb = wx.CheckBox(ventanaCasillas, -1, 'cpu', (10, 80))
    self.cb.SetValue(True)
    wx.EVT_CHECKBOX(self, self.cb.GetId(), self.boolCpu)
    
    self.cb = wx.CheckBox(ventanaCasillas, -1, '', (120, 80))
    self.cb.SetValue(True)
    
    #Inserto botones adicionales con metodo wx.Button que la liga al panel y le da nombre, tamano y posicion
    #con EVT_BUTTON comprube si el boton se a clickado

    self.botonLimpiar = wx.Button(ventanaCasillas, -1, 'Limpiar', size=(60,30), pos=(50,120))
    self.Bind(wx.EVT_BUTTON, self.CLEAR, self.botonLimpiar)

    self.botonEjecutar = wx.Button(ventanaCasillas, -1, 'Ejecutar', size=(70,30), pos=(120,120))
    self.Bind(wx.EVT_BUTTON, self.Ejecutar, self.botonEjecutar)

    #Caracteristicas visuales de ventana
    self.Show()
    self.Centre()

   #Deficiones que toman el valor de la casilla que las usa, el valor es guardado en el 'diccionarioElegidos' para su verificacion
   #se usan variables globales para usar aquella que estan declaradas abajo y no declarar adicionales
  def boolSystem(self, event):
    global banderaSys
    if self.cb.GetValue():
      banderaSys = not banderaSys
      diccionarioElegidos["system"] = banderaSys
      print banderaSys
            
  def boolDisk(self, event):
    global banderaDisk
    if self.cb.GetValue():
      banderaDisk = not banderaDisk
      diccionarioElegidos["disk"] = banderaDisk
      print banderaDisk
      
  def boolMemory(self, event):
    global banderaMem
    if self.cb.GetValue():
      banderaMem = not banderaMem
      diccionarioElegidos["memory"] = banderaMem
      print banderaMem

  def boolProcess(self, event):
    global banderaProc
    if self.cb.GetValue():
      banderaProc = not banderaProc
      diccionarioElegidos["process"] = banderaProc
      print banderaProc

  def boolCpu(self, event):
    global banderaCpu
    if self.cb.GetValue():
      banderaCpu = not banderaCpu
      diccionarioElegidos["cpu"] = banderaCpu
      print banderaCpu
      
  def boolColor(self, event):
    global banderaColor
    if self.cb.GetValue():
      banderaColor = not banderaColor
      diccionarioElegidos["color"] = banderaColor
      print banderaColor

  #Funciones ligadas a los botones de limpiar y ejecutar
  def CLEAR(self,event):
    global semaforo
    semaforo.acquire()
    os.system("clear")
    semaforo.release()

  def Ejecutar(self,event):
    hilo(diccionarioElegidos)

#Variables que me indican si la casilla se a seleccionado
banderaSys = True
banderaDisk = True
banderaMem = True
banderaProc = True
banderaCpu = True
banderaColor = True
'------------------------------------------------------------------------------------------------------------'

 #Funciones que ejecutan los comandos seleccionados mediante la libreria os
 #os.system("comando")
def SYSTEM():
  global semaforo
  semaforo.acquire()
  print chr(27)+"[1;31m"+"===>",
  print chr(27)+"[3;33m"+"SYSTEM",
  print chr(27)+"[1;31m"+"<===\n"
  print chr(27)+"[3;32m"+"Arquitectura de la maquina",
  print chr(27)+"[3;37m"
  os.system("arch") #Mostrar arquitectura de la maquina
  print chr(27)+"[3;32m"+"Version del kernel usado",
  print chr(27)+"[3;37m"
  os.system("uname -r") #Mostrar la version del kernel usado
  #os.system("dmidecode -q") #Mostrar el hardware del sistema
  semaforo.release()

def HDD():
  global semaforo
  semaforo.acquire()
  print chr(27)+"[1;31m"+"===>",
  print chr(27)+"[3;33m"+"DISK",
  print chr(27)+"[1;31m"+"<===\n"
  #os.system("du -h") #Descubre archivos mas grandes del sistema
  print chr(27)+"[3;33m"+"Ficheros y carpetas en forma de arbol comenzando por la raiz"
  print chr(27)+"[3;37m"
  os.system("tree") #Mostrar los ficheros y carpetas en forma de arbol comenzando por la raiz.
  semaforo.release()
  
def MEMORY():
  global semaforo
  semaforo.acquire()
  print chr(27)+"[1;31m"+"===>",
  print chr(27)+"[3;33m"+"MEMORY",
  print chr(27)+"[1;31m"+"<===\n"
  print chr(27)+"[3;34m"+"Cantidad total de memoria libre, la memoria fisica utilizada y el intercambio en el sistema"
  print chr(27)+"[3;37m"
  os.system("free") #Se visualiza la cantidad total de memoria libre, la memoria fisica utilizada y el intercambio en el sistema
  print chr(27)+"[3;34m"+"Uso de Memoria"
  print chr(27)+"[3;37m"
  os.system("cat /proc/meminfo") #Verificar el uso de memoria
  semaforo.release()

def PROCESS():
  global semaforo
  semaforo.acquire()
  print chr(27)+"[1;31m"+"===>",
  print chr(27)+"[3;33m"+"PROCESS",
  print chr(27)+"[1;31m"+"<===\n"
  print chr(27)+"[3;35m"+"Instantanea de los procesos actuales"
  print chr(27)+"[3;37m"
  os.system("ps") #Muestra una instantanea de los procesos actuales
  print chr(27)+"[3;35m"+"Procesos actuales en forma de arbol"
  print chr(27)+"[3;37m"
  os.system("pstree") #Muestra procesos actuales en forma de arbol
  semaforo.release()
  
def CPU():
  global semaforo
  semaforo.acquire()
  print chr(27)+"[1;31m"+"===>",
  print chr(27)+"[3;33m"+"CPU",
  print chr(27)+"[1;31m"+"<===\n"
  print chr(27)+"[3;36m"+"Informacion del CPU"
  print chr(27)+"[3;37m"
  os.system("cat /proc/cpuinfo") #Mostar informacion del CPU
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

#Funcion que lanza los hilos de los comandos seleccionados basandosse en la seleccion de las casillas de la ventana
def hilo(diccionarioElegidos):
  if diccionarioElegidos["system"] == True:
    filament0 = threading.Thread(target = SYSTEM)
    filament0.start()
  if diccionarioElegidos["disk"] == True:
    filament1 = threading.Thread(target = HDD)
    filament1.start()
  if diccionarioElegidos["memory"] == True:
    filament2 = threading.Thread(target = MEMORY)
    filament2.start()
  if diccionarioElegidos["process"] == True:
    filament3 = threading.Thread(target = PROCESS)
    filament3.start()
  if diccionarioElegidos["cpu"] == True:
    filament4 = threading.Thread(target = CPU)
    filament4.start()

def MONITOR():
  global opcion, thr, semaforo
  os.system("clear")
  while thr == 0:
      time.sleep(.5)
  
      print chr(27)+"[1;31m"+"===>",
      print chr(27)+"[3;33m"+"COMANDOS",
      print chr(27)+"[1;31m"+"<===\n"
      print "system\tdisk\tmemory\tprocess\tcpu\tall\tclear\thelp\texit"
      opcion = raw_input("wifislax@sudo$")
      COMMAND(opcion)
  semaforo.release()

casillasBooleanas = wx.App()
OpcionesMonitor(None, -1, 'Monitor de Sistema')
casillasBooleanas.MainLoop()
#MONITOR()

