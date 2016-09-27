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
    def setupUi(self, TabWidget):
        TabWidget.setObjectName(_fromUtf8("TabWidget"))
        TabWidget.resize(592, 408)
        TabWidget.setTabPosition(QtGui.QTabWidget.North)
        TabWidget.setTabShape(QtGui.QTabWidget.Rounded)
        TabWidget.setElideMode(QtCore.Qt.ElideLeft)
        TabWidget.setTabsClosable(False)
        TabWidget.setMovable(False)
        self.tabProc = QtGui.QWidget()
        self.tabProc.setObjectName(_fromUtf8("tabProc"))
        self.listWidget = QtGui.QListWidget(self.tabProc)
        self.listWidget.setGeometry(QtCore.QRect(30, 40, 381, 301))
        self.listWidget.setObjectName(_fromUtf8("listWidget"))
        self.stopButton = QtGui.QPushButton(self.tabProc)
        self.stopButton.setGeometry(QtCore.QRect(450, 40, 95, 30))
        self.stopButton.setObjectName(_fromUtf8("stopButton"))
        self.infoButton = QtGui.QPushButton(self.tabProc)
        self.infoButton.setGeometry(QtCore.QRect(450, 120, 95, 30))
        self.infoButton.setObjectName(_fromUtf8("infoButton"))
        self.labelProc = QtGui.QLabel(self.tabProc)
        self.labelProc.setGeometry(QtCore.QRect(50, 10, 67, 20))
        self.labelProc.setObjectName(_fromUtf8("labelProc"))
        TabWidget.addTab(self.tabProc, _fromUtf8(""))
        self.tabCPU = QtGui.QWidget()
        self.tabCPU.setObjectName(_fromUtf8("tabCPU"))
        self.CpuBar = QtGui.QProgressBar(self.tabCPU)
        self.CpuBar.setGeometry(QtCore.QRect(230, 50, 271, 31))
        self.CpuBar.setProperty("value", 24)
        self.CpuBar.setObjectName(_fromUtf8("CpuBar"))
        self.RamBar = QtGui.QProgressBar(self.tabCPU)
        self.RamBar.setGeometry(QtCore.QRect(230, 210, 271, 31))
        self.RamBar.setProperty("value", 24)
        self.RamBar.setObjectName(_fromUtf8("RamBar"))
        self.labelCPU = QtGui.QLabel(self.tabCPU)
        self.labelCPU.setGeometry(QtCore.QRect(60, 50, 81, 20))
        self.labelCPU.setObjectName(_fromUtf8("labelCPU"))
        self.labelMem = QtGui.QLabel(self.tabCPU)
        self.labelMem.setGeometry(QtCore.QRect(60, 210, 111, 20))
        self.labelMem.setObjectName(_fromUtf8("labelMem"))
        TabWidget.addTab(self.tabCPU, _fromUtf8(""))

        self.retranslateUi(TabWidget)
        TabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(TabWidget)

    def retranslateUi(self, TabWidget):
        TabWidget.setWindowTitle(_translate("TabWidget", "Monitor", None))
        self.stopButton.setText(_translate("TabWidget", "Detener", None))
        self.infoButton.setText(_translate("TabWidget", "Info", None))
        self.labelProc.setText(_translate("TabWidget", "Procesos", None))
        TabWidget.setTabText(TabWidget.indexOf(self.tabProc), _translate("TabWidget", "&Procesos", None))
        TabWidget.setTabToolTip(TabWidget.indexOf(self.tabProc), _translate("TabWidget", "Procesos", None))
        self.labelCPU.setText(_translate("TabWidget", "Uso de CPU", None))
        self.labelMem.setText(_translate("TabWidget", "Uso de Memoria", None))
        TabWidget.setTabText(TabWidget.indexOf(self.tabCPU), _translate("TabWidget", "&CPU y Ram", None))

