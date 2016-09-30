#Mendoza Colmenares Gerardo
#Primer proyecto basado en monitoreo de procesos mediante multihilos

#En este primer archivo se intentara hacer uso de multiilos cuando se manden a llamar a ciertos comandos

#CORRECCIONES
#Se agrego una ventana que simula la carga de una tarea, ademas de corregir errores de formato de impresion en terminal

import wx
import threading
import time
import os

#Diccionario que guarda las selecciones de la ventana para posterior ejecucion
diccionarioElegidos = {'system':True, 'disk':True, 'memory':True, 'process':True, 'cpu':True, 'color':True}

semaforo = threading.Semaphore(1)
thr = 0
rangoTiempo = 10

#Clase Tarea que cargara una ventana de carga cada que se ejecute una o varias tareas
class Tarea(wx.Frame):           
  def __init__(self, *args, **kw):
    super(Tarea, self).__init__(*args, **kw)         
    self.InitUI()

  #Funcion de temporizador
  def InitUI(self):           
    self.timer = wx.Timer(self, 1)
    self.count = 0
    self.Bind(wx.EVT_TIMER, self.OnTimer, self.timer)

    #Creacion de la ventana y una caja de botones que ira dentro la anterior
    ventanaTarea = wx.Panel(self)
    vbox = wx.BoxSizer(wx.VERTICAL)
    hbox1 = wx.BoxSizer(wx.HORIZONTAL)
    hbox2 = wx.BoxSizer(wx.HORIZONTAL)
    hbox3 = wx.BoxSizer(wx.HORIZONTAL)

    #Establecemos formato de tamano y del tipo de botones a usar
    self.gauge = wx.Gauge(ventanaTarea, range=rangoTiempo, size=(250, 25))
    self.btn1 = wx.Button(ventanaTarea, wx.ID_OK)
    self.btn2 = wx.Button(ventanaTarea, wx.ID_CANCEL)
    self.text = wx.StaticText(ventanaTarea, label='Seguro que desea realizar esta tarea?')

    #Cada que se presione un boton, mandara a llamar a la funcion indicada
    self.Bind(wx.EVT_BUTTON, self.OnOk, self.btn1)
    self.Bind(wx.EVT_BUTTON, self.OnStop, self.btn2)

    #Formato donde se decide donde poner en pantalla cada boton
    hbox1.Add(self.gauge, proportion=1, flag=wx.ALIGN_CENTRE)
    hbox2.Add(self.btn1, proportion=1, flag=wx.RIGHT, border=10)
    hbox2.Add(self.btn2, proportion=1)
    hbox3.Add(self.text, proportion=1)
    vbox.Add((0, 30))
    vbox.Add(hbox1, flag=wx.ALIGN_CENTRE)
    vbox.Add((0, 20))
    vbox.Add(hbox2, proportion=1, flag=wx.ALIGN_CENTRE)
    vbox.Add(hbox3, proportion=1, flag=wx.ALIGN_CENTRE)

    ventanaTarea.SetSizer(vbox)

    #Nombre y tamano de la ventana
    self.SetSize((300, 200))
    self.SetTitle('TAREAS')
    self.Centre()
    self.Show(True)     

  #Funciones de los botones Ok y Cancelar, en el caso de Ok saldra un mensaje de Tarea en progreso
  #y en el de Cancelar saldra un mensaje y una pregunta de si se desea continuar con la tarea previamente detrnida.
  #Ademas la tercer funcion es la que lleva la cuenta del temporizador y la barra de carga
  def OnOk(self, e):      
    if self.count >= rangoTiempo:
        return
    self.timer.Start(100)
    self.text.SetLabel('\t\tTarea en progeso...')
    hilo(diccionarioElegidos)
    
  def OnStop(self, e):      
    if self.count == 0 or self.count >= rangoTiempo or not self.timer.IsRunning():
        return
    self.timer.Stop()
    self.text.SetLabel('\t\tTAREA INTERRUMPIDA\n  Presione Aceptar para continuarla')
        
  def OnTimer(self, e):        
    self.count = self.count + 1
    self.gauge.SetValue(self.count)
    if self.count == rangoTiempo:
        self.timer.Stop()
        self.Close()
        
#Llamada a la ventana de carga
def CargaTarea():    
  ejecutaTareas = wx.App()
  Tarea(None)
  ejecutaTareas.MainLoop()

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
    
    self.cb = wx.CheckBox(ventanaCasillas, -1, '', (120, 130))
    self.cb.SetValue(True)
    
    #Inserto botones adicionales con metodo wx.Button que la liga al panel y le da nombre, tamano y posicion
    #con EVT_BUTTON comprube si el boton se a clickado
    self.botonLimpiar = wx.Button(ventanaCasillas, -1, 'Limpiar', size=(60,30), pos=(20,120))
    self.Bind(wx.EVT_BUTTON, self.CLEAR, self.botonLimpiar)

    self.botonEjecutar = wx.Button(ventanaCasillas, -1, 'Ejecutar', size=(70,30), pos=(90,120))
    self.Bind(wx.EVT_BUTTON, self.Ejecutar, self.botonEjecutar)
    
    self.botonAyuda = wx.Button(ventanaCasillas, -1, 'Ayuda', size=(60,30), pos=(170,120))
    self.Bind(wx.EVT_BUTTON, self.Ayuda, self.botonAyuda)

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
            
  def boolDisk(self, event):
    global banderaDisk
    if self.cb.GetValue():
      banderaDisk = not banderaDisk
      diccionarioElegidos["disk"] = banderaDisk
      
  def boolMemory(self, event):
    global banderaMem
    if self.cb.GetValue():
      banderaMem = not banderaMem
      diccionarioElegidos["memory"] = banderaMem

  def boolProcess(self, event):
    global banderaProc
    if self.cb.GetValue():
      banderaProc = not banderaProc
      diccionarioElegidos["process"] = banderaProc

  def boolCpu(self, event):
    global banderaCpu
    if self.cb.GetValue():
      banderaCpu = not banderaCpu
      diccionarioElegidos["cpu"] = banderaCpu
      
  def boolColor(self, event):
    global banderaColor
    if self.cb.GetValue():
      banderaColor = not banderaColor
      diccionarioElegidos["color"] = banderaColor

  #Funciones ligadas a los botones de limpiar y ejecutar
  def CLEAR(self,event):
    global semaforo
    semaforo.acquire()
    os.system("clear")
    semaforo.release()

  def Ejecutar(self,event):
    CargaTarea()
    hilo(diccionarioElegidos)
    
  def Ayuda(self,event):
    global semaforo
    semaforo.acquire()
    print chr(27)+"[1;31m"+"===>",
    print chr(27)+"[3;33m"+"AYUDA",
    print chr(27)+"[1;31m"+"<===\n"
    print chr(27)+"[1;32m"+ "=>Para hacer uso del monitor, es necesario seleccionar las casillas deseadas (se considera seleccionada"
    print " cuando este con una flecha en el recuadro) y dar ejecutar para ver la informacion elegida en la terminal\n\n"
    print "=>El boton limpiar, borra todo lo anterior en pantalla\n\n"
    print "=>En caso de no ver la informacion completa, desplazese con las barras de los costados en la terminal, fijandose en el titulo"
    print "que se presenta, para poder distinguir la informacion solicitada\n\n"
    print "=>El nombre de la casilla define que tipo de informacion de monitoreo se le presentara, cada una tiene un"
    print "nombre intuitivo para usuarios no tan familiarizados\n\nMonitor de Sistema version 1.0"
    semaforo.release()

#Variables que me indican si la casilla se a seleccionado
banderaSys = True
banderaDisk = True
banderaMem = True
banderaProc = True
banderaCpu = True
banderaColor = True
'------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'

 #Funciones que ejecutan los comandos seleccionados mediante la libreria os
 #os.system("comando"), cada comando tiene una pequena explicacion.
 #El 'print chr(27)+"[x;3xm" +...' da formato al print en la terminal, cada que cambias x el color y tipo de letra cambiara
 #Cada funcion pide el 'semaforo' para evitar fallos al ejecutarse
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

#Funcion que lanza los hilos de los comandos seleccionados basandose en la seleccion de las casillas de la ventana
#Cuando el hilo es lanzado tomara posesion del mutex para evitar cruce de informacion, al final de la ejecucion, lo 'soltara'
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

'------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
#Ejecucion de la ventana principal mediante el metodo App y la funcion OpcionesMonitor
casillasBooleanas = wx.App()
OpcionesMonitor(None, -1, 'Monitor de Sistema')
casillasBooleanas.MainLoop()