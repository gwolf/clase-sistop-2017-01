import threading
import time
from Tkinter import *
import re

def myfunction(event):
    canvas.configure(scrollregion=canvas.bbox("all"),width=600,height=600)

root = Tk()
sizex = 800
sizey = 600
posx  = 100
posy  = 100
root.wm_geometry("%dx%d+%d+%d" % (sizex, sizey, posx, posy))

myframe=Frame(root,relief=GROOVE,width=50,height=100,bd=1)
myframe.place(x=10,y=10)

canvas=Canvas(myframe)
frame=Frame(canvas)
myscrollbar=Scrollbar(myframe,orient="vertical",command=canvas.yview)
canvas.configure(yscrollcommand=myscrollbar.set)

myscrollbar.pack(side="right",fill="y")
canvas.pack(side="left")
canvas.create_window((0,0),window=frame,anchor='nw')
frame.bind("<Configure>",myfunction)

update = threading.Semaphore(0)

def mem():
    memState = open("/proc/meminfo","r")
    memInfo = memState.read()
    memState.close()
    memStats = Label(frame,text=memInfo,justify=LEFT).grid(row=1,column=0)
    

def monitor():
 threading.Thread(target=disk,args=[]).start()
 threading.Thread(target=mem,args=[]).start()

def disk():
    discState = open("/proc/diskstats","r")
    infoDisk = discState.read()
    discState.close()
    diskStates(infoDisk)

def diskStates(infoDisk):
    diskLabel = Label(frame,text=infoDisk,justify=LEFT).grid(row=0,column=0)
    root.after(1000,monitor)


threading.Thread(target=monitor,args=[]).start()

root.mainloop()
