# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'monitor.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_TabWidget(object):
    def setupUi(self, TabWidget):#metodo de preparacion de la GUI
        TabWidget.setObjectName(_fromUtf8("TabWidget"))
        TabWidget.resize(705, 433)
        TabWidget.setTabPosition(QtGui.QTabWidget.North)
        TabWidget.setTabShape(QtGui.QTabWidget.Rounded)
        TabWidget.setElideMode(QtCore.Qt.ElideLeft)
        TabWidget.setTabsClosable(False)
        TabWidget.setMovable(False)
        self.tabProc = QtGui.QWidget()
        self.tabProc.setObjectName(_fromUtf8("tabProc"))
        self.gridLayout = QtGui.QGridLayout(self.tabProc)
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.labelProc = QtGui.QLabel(self.tabProc)
        self.labelProc.setObjectName(_fromUtf8("labelProc"))
        self.gridLayout.addWidget(self.labelProc, 0, 0, 1, 1)
        self.ListaMem = QtGui.QListWidget(self.tabProc)
        self.ListaMem.setObjectName(_fromUtf8("ListaMem"))
        self.gridLayout.addWidget(self.ListaMem, 1, 0, 1, 1)
        TabWidget.addTab(self.tabProc, _fromUtf8(""))
        self.tabCPU = QtGui.QWidget()
        self.tabCPU.setObjectName(_fromUtf8("tabCPU"))
        self.gridLayout_2 = QtGui.QGridLayout(self.tabCPU)
        self.gridLayout_2.setObjectName(_fromUtf8("gridLayout_2"))
        self.labelCPU = QtGui.QLabel(self.tabCPU)
        self.labelCPU.setObjectName(_fromUtf8("labelCPU"))
        self.gridLayout_2.addWidget(self.labelCPU, 0, 0, 1, 1)
        self.CpuBar = QtGui.QProgressBar(self.tabCPU)
        self.CpuBar.setProperty("value", 24)
        self.CpuBar.setObjectName(_fromUtf8("CpuBar"))
        self.gridLayout_2.addWidget(self.CpuBar, 0, 1, 1, 1)
        self.labelMem = QtGui.QLabel(self.tabCPU)
        self.labelMem.setObjectName(_fromUtf8("labelMem"))
        self.gridLayout_2.addWidget(self.labelMem, 1, 0, 1, 1)
        self.RamBar = QtGui.QProgressBar(self.tabCPU)
        self.RamBar.setProperty("value", 24)
        self.RamBar.setObjectName(_fromUtf8("RamBar"))
        self.gridLayout_2.addWidget(self.RamBar, 1, 1, 1, 1)
        TabWidget.addTab(self.tabCPU, _fromUtf8(""))
        self.tab = QtGui.QWidget()
        self.tab.setObjectName(_fromUtf8("tab"))
        self.gridLayout_3 = QtGui.QGridLayout(self.tab)
        self.gridLayout_3.setObjectName(_fromUtf8("gridLayout_3"))
        self.listMem = QtGui.QListWidget(self.tab)
        self.listMem.setObjectName(_fromUtf8("listMem"))
        self.gridLayout_3.addWidget(self.listMem, 1, 0, 1, 1)
        self.label = QtGui.QLabel(self.tab)
        self.label.setObjectName(_fromUtf8("label"))
        self.gridLayout_3.addWidget(self.label, 0, 0, 1, 1)
        self.listMem2 = QtGui.QListWidget(self.tab)
        self.listMem2.setObjectName(_fromUtf8("listMem2"))
        self.gridLayout_3.addWidget(self.listMem2, 1, 1, 1, 1)
        self.listMem3 = QtGui.QListWidget(self.tab)
        self.listMem3.setObjectName(_fromUtf8("listMem3"))
        self.gridLayout_3.addWidget(self.listMem3, 1, 2, 1, 1)
        TabWidget.addTab(self.tab, _fromUtf8(""))

        self.retranslateUi(TabWidget)
        TabWidget.setCurrentIndex(2)
        QtCore.QMetaObject.connectSlotsByName(TabWidget)

    def retranslateUi(self, TabWidget):
        TabWidget.setWindowTitle(_translate("TabWidget", "Monitor", None))
        self.labelProc.setText(_translate("TabWidget", "Procesos", None))
        TabWidget.setTabText(TabWidget.indexOf(self.tabProc), _translate("TabWidget", "&Procesos", None))
        TabWidget.setTabToolTip(TabWidget.indexOf(self.tabProc), _translate("TabWidget", "Procesos", None))
        self.labelCPU.setText(_translate("TabWidget", "Promedio de uso CPU", None))
        self.labelMem.setText(_translate("TabWidget", "Uso de Memoria", None))
        TabWidget.setTabText(TabWidget.indexOf(self.tabCPU), _translate("TabWidget", "&CPU y Ram", None))
        self.label.setText(_translate("TabWidget", "Información de Memoria", None))
        TabWidget.setTabText(TabWidget.indexOf(self.tab), _translate("TabWidget", "Mem. info", None))

