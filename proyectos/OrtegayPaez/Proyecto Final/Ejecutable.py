import sys #libreria necesaria para la limpieza despues de la ejecución
from monitor import * #importa el codigo y clases de Gui
from barThreads import *#importa los hilos creadosa partir de la API PyQT, encargados de las barras de progreso
from MemThread import *#importa la clase de hilo encargado de la información de memoria
from InterruptThread import *
from processThreads import *
'''
Clase principal de nombre Monitor, la cual hereda de la Gui ara poder invocarla.
En ella se crean hilos de varios tipos que llevaran a cabo las distintas tareas de actualizacion en la ventana
creada.
La palabra Self es utilizada a lo largo de todas las clases definidas para denotar una instancia del objeto en si mismo
'''
class Monitor(QtGui.QTabWidget):#Definicion de la clase
    def __init__(self,parent=None):#constructor de la clase
        QtGui.QWidget.__init__(self,parent)#constructor de la Gui para poderla utilizar
        self.ui= Ui_TabWidget()#Instancia de la Gui
        self.ui.setupUi(self)#preparacion de la GUI segun las especificaciones
        self.cthread=cputhread()
        self.rthread = ramThread()
        self.mthread = Mthread()
        self.ithread=InterruptThread()
        self.pthread=procThread()
        self.cthread.start()
        self.pthread.start()
        self.rthread.start()
        self.mthread.start()
        self.ithread.start()
        self.timer = QtCore.QTimer()#este objeto delcarado es un temporizador para lanzar el hilo cada cierto tiempo
        self.timer2 = QtCore.QTimer()
        self.timer3= QtCore.QTimer()
        self.timer.timeout.connect(self.mthread.start)#aqui se asocia el temporizador a la función que lanzara
        self.timer2.timeout.connect(self.ithread.start)
        self.timer3.timeout.connect(self.pthread.start)
        self.timer.start(5000)#se delimita el intervalo en el qeu se lanzara el hilo
        self.timer2.start(2000)
        self.timer3.start(15000)
        '''
        Banco de REceptores de Señales atrapadas por la Gui para realizar a cabo una tarea especifica
        Estas señales se emiten desde las distintas clasesde hilos qeu se crearon para que interactuen
        con las acciones mostradas en la GUI.
        Algunas de estas señales pueden enviar un valor. En este caso todas ellas reciben
        la estructura es
        Encargado de cachar(quein la envia, QtCore.SIGNAL("nombre de la señal"), que es lo que se hara con lo proporcionado)
        '''
        self.connect(self.mthread, QtCore.SIGNAL('Listo1'), self.ui.listMem.clear)
        self.connect(self.mthread, QtCore.SIGNAL('Listo2'), self.ui.listMem2.clear)
        self.connect(self.mthread, QtCore.SIGNAL('Listo3'), self.ui.listMem3.clear)
        self.connect(self.mthread, QtCore.SIGNAL('Data1'), self.ui.listMem.addItem)
        self.connect(self.mthread, QtCore.SIGNAL('Data2'), self.ui.listMem2.addItem)
        self.connect(self.mthread, QtCore.SIGNAL('Data3'), self.ui.listMem3.addItem)
        self.connect(self.ithread, QtCore.SIGNAL('ListINT'), self.ui.ListaInter.clear)
        self.connect(self.ithread, QtCore.SIGNAL('INTER'), self.ui.ListaInter.addItem)
        self.connect(self.pthread, QtCore.SIGNAL('Listo4'), self.ui.ListProc.clear)
        self.connect(self.pthread, QtCore.SIGNAL('PROC'), self.ui.ListProc.addItem)
        self.connect(self.cthread, QtCore.SIGNAL('Cpu_Val'),self.ui.CpuBar.setValue)
        self.connect(self.rthread, QtCore.SIGNAL('Mem_Val'),self.ui.RamBar.setValue)



'''
Ejecución principal del programa aqui se lleva a cabo la instancia  de la clase de monitor
para ser ejecutada.
'''

if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    myapp = Monitor()
    myapp.show()
    sys.exit(app.exec_())
