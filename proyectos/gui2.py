import threading
from Tkinter import *
import datetime

root = Tk()

update = threading.Semaphore(0)

scale = Scale(root, from_=0, to=42)
scale.pack()

def mem():
    update.acquire()
    memState = open("/proc/meminfo","r")
    memInfo = memState.read()
    memState.close()
    diskLabel = Label(root,text=memInfo,justify=LEFT)
    
    

def trigger():
 threading.Thread(target=disk,args=[]).start()
 threading.Thread(target=mem,args=[]).start()

def disk():
    discState = open("/proc/diskstats","r")
    infoDisk = discState.read()
    discState.close()
    diskState(infoDisk)

def diskState(infoDisk):
    diskLabel = Label(root,text=infoDisk,justify=LEFT)
    update.release()
    root.after(1000,trigger)

threading.Thread(target=trigger,args=[]).start()


root.mainloop()
