#Me reservo los comentarios debido a que aun no se como funciona del todo cada metodo usado, sin embargo en el archivo final
#se mencionara el uso que tienen para ayudar en la seleccion de los hilos a lanzar

import wx

class OpcionesMonitor(wx.Frame):
  def __init__(self, parent, id, title):
    wx.Frame.__init__(self, parent, id, title, size=(250, 170))

    ventanaCasillas = wx.Panel(self, -1)
    self.cb = wx.CheckBox(ventanaCasillas, -1, 'system', (10, 10))
    self.cb.SetValue(False)
    wx.EVT_CHECKBOX(self, self.cb.GetId(), self.boolSystem)

    self.cb = wx.CheckBox(ventanaCasillas, -1, 'disk', (120, 10))
    self.cb.SetValue(False)
    wx.EVT_CHECKBOX(self, self.cb.GetId(), self.boolDisk)

    self.cb = wx.CheckBox(ventanaCasillas, -1, 'memory', (10, 45))
    self.cb.SetValue(False)
    wx.EVT_CHECKBOX(self, self.cb.GetId(), self.boolMemory)
    
    self.cb = wx.CheckBox(ventanaCasillas, -1, 'process', (120, 45))
    self.cb.SetValue(False)
    wx.EVT_CHECKBOX(self, self.cb.GetId(), self.boolProcess)
    
    self.cb = wx.CheckBox(ventanaCasillas, -1, 'cpu', (10, 80))
    self.cb.SetValue(False)
    wx.EVT_CHECKBOX(self, self.cb.GetId(), self.boolCpu)

    self.Show()
    self.Centre()

  def boolSystem(self, event):
    if self.cb.GetValue():
      print "System"
      
  def boolDisk(self, event):
    if self.cb.GetValue():
      print "Disk"
      
  def boolMemory(self, event):
    if self.cb.GetValue():
      print "Memory"

  def boolProcess(self, event):
    if self.cb.GetValue():
      print "Process"

  def boolCpu(self, event):
    if self.cb.GetValue():
      print "Cpu"

casillasBooleanas = wx.App()
OpcionesMonitor(None, -1, 'Monitor de Sistema')
casillasBooleanas.MainLoop()