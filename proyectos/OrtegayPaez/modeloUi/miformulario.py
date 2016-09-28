import sys
from monitor import *
from barThreads import *


class formu(QtGui.QTabWidget,QtGui.QMainWindow):
    def __init__(self,parent=None):
        QtGui.QWidget.__init__(self,parent)
        self.ui= Ui_TabWidget()
        self.ui.setupUi(self)
        self.cthread=cputhread()
        self.rthread = ramThread()
        self.cthread.start()
        self.rthread.start()
        self.connect(self.cthread, QtCore.SIGNAL('Cpu_Val'),self.ui.CpuBar.setValue)
        self.connect(self.rthread, QtCore.SIGNAL('Mem_Val'),self.ui.RamBar.setValue)


if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    myapp = formu()
    myapp.show()
    sys.exit(app.exec_())
