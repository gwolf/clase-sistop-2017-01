import sys
from monitor import *

class MiFormulario(QtGui.QTabWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.ui = Ui_TabWidget()
        self.ui.setupUi(self)





if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    myapp = MiFormulario()
    myapp.show()
    sys.exit(app.exec_())
"""
import sys
from priminterfaz import *


class MiFormulario(QtGui.QMainWindow):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.ui = Ui_Dialog()
        self.ui.setupUi(self)



if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    myapp = Ejemplo()
    myapp.show()
    sys.exit(app.exec_())
"""