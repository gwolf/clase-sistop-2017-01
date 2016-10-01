from PyQt4 import QtCore
import psutil

'''
Clase de hilos que se encargaran de obtener el porcentaje de uso de los cpus
para mandarlo ala clase monitor y que lo despliegue en una barra de progreso
'''
class cputhread(QtCore.QThread):
    def __init__(self,parent=None):
        QtCore.QThread.__init__(self,parent)

    def __del__(self):
        self.wait()

    '''
    Método que obtiene los usos porcentuales de los nucleos y los promedia para obtener un aproximado total
    '''
    def porcentaje(self):
        cpus=psutil.cpu_percent(.5,True)
        resul=0
        for elem in cpus:
            resul+=elem
        resul=resul/len(cpus)
        return resul
    '''
    En este caso el método run se es el qeu emite la señal, ya que este hilo no termina, s emantiene constantementa
    enviando señales a la clase monitor y pasandole el valor. el método run de la clase ramthread es identico
    '''
    def run(self):
        while True:
            a=self.porcentaje()
            self.emit(QtCore.SIGNAL('Cpu_Val'),a)


class ramThread(QtCore.QThread):
    def __init__(self,parent=None):
        QtCore.QThread.__init__(self,parent)

    def __del__(self):
        self.wait()
    '''
    Método que obtiene el porcentaje de uso de la memoria
    '''
    def GetMemory(self):
        res=psutil.virtual_memory()
        return res.percent

    '''
    En este caso el método run se es el qeu emite la señal, ya que este hilo no termina, s emantiene constantementa
    enviando señales a la clase monitor y pasandole el valor
    '''
    def run(self):
        while True:
            mem=self.GetMemory()
            self.emit(QtCore.SIGNAL('Mem_Val'),mem)