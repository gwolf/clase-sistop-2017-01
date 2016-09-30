import threading #importa la libreria de herramientas multi-hilos nativas de python
from PyQt4 import QtCore, QtGui #importa las clases para heredar a la nueva clase de hilos y manejo de datos
'''
Clase de hilo encargado de la lectura del archivo meminfo, ubicado de /proc/ el cual al ser ejecutado lanza otros
2 hilos uno de lectura y otro de escritura
Lector: Hilo único que leerá un archivo y lo transformará en una lista de strings para su posterior utilización
Escritor: Hilo que se encarga unica y exlusivamente de envair los items par aingresar a la GUI
'''
class InterruptThread(QtCore.QThread):
    let=[]#lista declarada para uso "global" de esta clase únicamente
    mutexx=threading.Semaphore(1)#mutex para asegurar la lectura del archivo y la conversion a lista
    locks = threading.Semaphore(0)#este semaforo se utilizara como señal para asegurar la lectura antes de la escritura

    def __init__(self,parent=None,):
        QtCore.QThread.__init__(self,parent)

    def __del__(self):
        self.wait()

    '''
    Método encargado de la lectura del archivo meminfo, alojado en /proc/, y transformacion a una lista de strings
    '''
    def lector(self):
        self.mutexx.acquire()#adqueire el mutex para no permitir que otro hilo entre
        try:#intenta abrir el archivo y llerlo
            self.f = open('/proc/interrupts', mode='rt', encoding='utf-8')
            self.let = self.f.readlines()#lectura y transformacion a lista
            self.f.close()
        except (OSError, IOError):
            print("no se pudo abrir archivo")
        finally:
            self.mutexx.release()#libera el mutex
            self.locks.release()#envia una señal al hilo escritor para que proceda. así aseguramos que primero se haga la lectura

    '''
    Método que se encarga de pasar los datos a la Gui para que esta los muestre en las listas y apartado de información
    de memoria.
    El hilo encargado de realizar esta tarea, recibirá una señal del hilo de lectura para proceder.
    '''
    def escritor(self):
        self.locks.acquire()#recibe la señal de lector
        self.emit(QtCore.SIGNAL('ListINT'))
        for cad in self.let[21:]:
            la = cad.rstrip()
            item = QtGui.QListWidgetItem(la)
            self.emit(QtCore.SIGNAL('INTER'), item)



    '''
    Método Run sobreescrito (Al estilo Java xD) es la función principal del hilo, en este caso lo único a realizar es
    lanzar 2 hilos que iran a ejecutar las funciones, escritor y lector respectivamente.
    '''
    def run(self):
        threading.Thread(target=self.lector,args=()).start()
        threading.Thread(target=self.escritor, args=()).start()
