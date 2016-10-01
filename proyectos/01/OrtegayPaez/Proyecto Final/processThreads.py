import threading #importa la libreria de herramientas multi-hilos nativas de python
import psutil
from PyQt4 import QtCore, QtGui #importa las clases para heredar a la nueva clase de hilos y manejo de datos
'''
Clase encargada de mostrar en pantalla los procesos existentes el equipo.
utiliza solo un hilo con el cual envia la informacíon a la clase monitor para que esta
la muestre en pantalla
'''
class procThread(QtCore.QThread):

    def __init__(self,parent=None):
        QtCore.QThread.__init__(self,parent)

    def __del__(self):
        self.wait()
    '''
    Método que itera sobre los procesos qeu estan actualmente "vivos" para asi  solo mostrar aquellos qeu esten,
    activos y no correr riesgo de que hayan finalizado
    '''
    def escritor(self):
        self.emit(QtCore.SIGNAL('Listo4'))
        for proc in psutil.process_iter():
            try:
                pinfo = proc.as_dict(attrs=['pid','name','status','username'])#Función que itera sobre procesos vivos, y transforma sus elementos de un diccionario
            except psutil.NoSuchProcess:
                pass
            else:
                word = "PID: "+str(pinfo['pid'])+", NAME: "+str(pinfo['name'])+", STATUS: "+str(pinfo['status'])+", USERNAME: "+str(pinfo['username']) #convierte cada elemento del dict a string por medio del constructor de string y lo concatena en la cadena item
                item=QtGui.QListWidgetItem(word)#Transforma el strng en QString para utilizacion en la GUI
                self.emit(QtCore.SIGNAL('PROC'), item)#Emite la señal y envia el dato a la clase monitor
    '''
    Método run sobre-escrito para ejecucion del hilo Qthread. en este método se invoca un hilo nativo de python
    sobre el metodo escritor
    '''
    def run(self):
        threading.Thread(target=self.escritor,args=()).start()
    

