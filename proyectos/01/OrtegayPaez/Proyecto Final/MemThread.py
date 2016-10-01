import threading #importa la libreria de herramientas multi-hilos nativas de python
from PyQt4 import QtCore, QtGui #importa las clases para heredar a la nueva clase de hilos y manejo de datos
'''
Clase de hilo encargado de la lectura del archivo meminfo, ubicado de /proc/ el cual al ser ejecutado lanza otros
2 hilos uno de lectura y otro de escritura
Lector: Hilo único que leerá un archivo y lo transformará en una lista de strings para su posterior utilización
Escritor: Hilo que lanza 3 hilos muy parecidos que iteran sobre la lista obtenida, trasnforman el tipo de dato
y lo regresan a la clase Monitor para la impresion de dicha información
'''
class Mthread(QtCore.QThread):
    let=[]#lista declarada para uso "global" de esta clase únicamente
    mutex=threading.Semaphore(1)#mutex para asegurar la lectura del archivo y la conversion a lista
    mutexlist=threading.Semaphore(1)#mutex que evitara que los hilos de escritura empleen la lista al mismo tiempo
    lock = threading.Semaphore(0)#este semaforo se utilizara como señal para asegurar la lectura antes de la escritura

    def __init__(self,parent=None,):
        QtCore.QThread.__init__(self,parent)

    def __del__(self):
        self.wait()

    '''
    Método encargado de la lectura del archivo meminfo, alojado en /proc/, y transformacion a una lista de strings
    '''
    def lector(self):
        self.mutex.acquire()#adqueire el mutex para no permitir que otro hilo entre
        try:#intenta abrir el archivo y llerlo
            self.f = open('/proc/meminfo', mode='rt', encoding='utf-8')
            self.let = self.f.readlines()#lectura y transformacion a lista
            self.f.close()
        except (OSError, IOError):
            print("no se pudo abrir archivo")
        finally:
            self.mutex.release()#libera el mutex
            self.lock.release()#envia una señal al hilo escritor para que proceda. así aseguramos que primero se haga la lectura

    '''
    Método que se encarga de pasar los datos a la Gui para que esta los muestre en las listas y apartado de información
    de memoria.
    El hilo encargado de realizar esta tarea, recibirá una señal del hilo de lectura para proceder.
    Este hilo a su vez lanzara 3 hilos más, estos 3 son nativos de python, para realizar la escritura en las 3 listas
    existentes
    '''
    def escritor(self):
        self.lock.acquire()#recibe la señal de lector
        #crea los 3 hilos para llamar a sus achichincles los 3 escritores
        threading.Thread(target=self.escritor1, args=()).start()
        threading.Thread(target=self.escritor2, args=()).start()
        threading.Thread(target=self.escritor3, args=()).start()

    '''
    Método declarado para escribir en la primera tabla de la GUI, El hilo que lo ejecute iterara la lista del 0 al
    elemento 16.
    Primero Emite una señal para que la lista se limpie antes de escribir en ella.
    Luego transforma los strings a Qstrings(tipo de dato utilizado por PyQt) para luego enviarlo a la GUI y que lo muestre,
    es enviado por medio de una señal.

    Los códigos con los otros 3 escritores son simetricos solo cambian los rangos de iteración
    '''
    def escritor1(self):
        self.mutexlist.acquire()#adquiere el mutex para que ningun otro hilo pueda iterar sobre la lista
        self.emit(QtCore.SIGNAL('Listo1'))#emite la primera
        for cad in self.let[:17]:#itera en la lista del 0 al 16. Por lo tanto ejecutara 17 veces lo siguiente
            la = cad.rstrip()#quita los saltos de línea de la cadena y la pasa a otro objeto
            item = QtGui.QListWidgetItem(la)#convierte el string a Qstring por medio del constructor de Qstrings
            self.emit(QtCore.SIGNAL('Data1'), item)#Emite una señal a la Gui y junto a este manda el item transformado
        self.mutexlist.release()#Libera el mutex

    def escritor2(self):
        self.mutexlist.acquire()
        self.emit(QtCore.SIGNAL('Listo2'))
        for cad in self.let[17:34]:
            la = cad.rstrip()
            item = QtGui.QListWidgetItem(la)
            self.emit(QtCore.SIGNAL('Data2'), item)
        self.mutexlist.release()

    def escritor3(self):
        self.mutexlist.acquire()
        self.emit(QtCore.SIGNAL('Listo3'))
        for cad in self.let[34:]:
            la = cad.rstrip()
            item = QtGui.QListWidgetItem(la)
            self.emit(QtCore.SIGNAL('Data3'), item)
        self.mutexlist.release()

    '''
    Método Run sobreescrito (Al estilo Java xD) es la función principal del hilo, en este caso lo único a realizar es
    lanzar 2 hilos que iran a ejecutar las funciones, escritor y lector respectivamente.
    '''
    def run(self):
        threading.Thread(target=self.lector,args=()).start()
        threading.Thread(target=self.escritor, args=()).start()
