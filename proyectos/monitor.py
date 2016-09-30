import threading
from Tkinter import *
import datetime

root = Tk()

update = threading.Semaphore(0)

lab = Label(root,width=100,justify= LEFT)
lab.pack()

def memInfo():
    update.acquire()
    print("por fin")
  #  memState = open("/proc/meminfo","r")
    
    

def trigger():
 threading.Thread(target=disk,args=[]).start()
 threading.Thread(target=memInfo,args=[]).start()

def disk():
    #update.acquire()
    discState = open("/proc/diskstats","r")
    infoDisk = discState.read()
    discState.close()
    diskState(infoDisk)

def diskState(infoDisk):
    lab.config(text=infoDisk)
    update.release()
    root.after(1000,trigger)

threading.Thread(target=trigger,args=[]).start()


root.mainloop()
