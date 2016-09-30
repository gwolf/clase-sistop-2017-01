from PyQt4 import QtCore
import psutil

class cputhread(QtCore.QThread):
    def __init__(self,parent=None):
        QtCore.QThread.__init__(self,parent)

    def __del__(self):
        self.wait()

    def porcentaje(self):
        cpus=psutil.cpu_percent(.5,True)
        resul=0
        for elem in cpus:
            resul+=elem
        resul=resul/len(cpus)
        return resul

    def run(self):
        while True:
            a=self.porcentaje()
            self.emit(QtCore.SIGNAL('Cpu_Val'),a)


class ramThread(QtCore.QThread):
    def __init__(self,parent=None):
        QtCore.QThread.__init__(self,parent)

    def __del__(self):
        self.wait()

    def GetMemory(self):
        res=psutil.virtual_memory()
        return res.percent

    def run(self):
        while True:
            mem=self.GetMemory()
            self.emit(QtCore.SIGNAL('Mem_Val'),mem)