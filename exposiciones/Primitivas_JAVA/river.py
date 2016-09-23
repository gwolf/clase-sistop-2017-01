import threading
import time
global hackers
global numbal
global pa
numbal=0
hackers = 0
pa=0
serfs = 0
lock=threading.Lock()
signal=threading.Event()
hackerqueue = threading.Condition(lock)
serfqueue = threading.Condition(lock)
mutexh = threading.Semaphore(1)
mutexs = threading.Semaphore(4)
mutexh1 = threading.Semaphore(2)
mutexs1 = threading.Semaphore(2)
boat = threading.Barrier(4)

def hacker(num):
    global hackers
    global serfs
    hackerqueue.acquire()
    hackers += 1
    #print("hacker #",num)
    hackerqueue.release()
    hackerqueue.acquire()
    if hackers == 4:
        hackerqueue.notify(3)
        #print("soy lider hacker #" , num, hackers)
        hackers -= 4
    elif hackers == 2 and serfs >= 2:
        hackerqueue.notify(2)
        serfqueue.notify(2)
        hackers -= 2
        serfs -= 2
        #print("soy lider hacker #" , num, hackers)
    else:
        #print("im waiting hacker #" , num, serfs)
        while hackers != 0:
            hackerqueue.wait(timeout=.001)
        #print("vuelvo al trabajo hacker # ",num)
    if boat.broken:
        boat.reset()
    hackerqueue.release()
    boat.wait()
    hackerqueue.acquire()
    abordar("hacker",num)
    hackerqueue.release()


def serf(num):
    global hackers
    global serfs
    psaron=0
    serfqueue.acquire()
    serfs += 1
    #print("serf #",num)
    serfqueue.release()
    serfqueue.acquire()
    if serfs == 4:
        serfqueue.notify(4)
        #print("soy lider serf #" , num, serfs)
        serfs -= 4
    elif serfs == 2 and hackers >= 2:
        hackerqueue.notify(2)
        serfqueue.notify(2)
        hackers -= 2
        serfs -= 2
        #print("soy lider serf #" , num, serfs)
    else:
        #print("im waiting serf #" , num, serfs)
        while serfs != 0:
            serfqueue.wait(timeout=.001)
       # print("vuelvo al trabajo serf # ",num)
    #if serfs ==
     #   boat.reset()
    if boat.broken:
        boat.reset()
    serfqueue.release()
    boat.wait()
    serfqueue.acquire()
    abordar("Serf",num)
    serfqueue.release()

def abordar(s,num):
    global pa
    pa +=1
    print ('acabo de abordar y soy un '+s+' mi numero es', num)
    if pa==4:
        balsa()
        pa=0

def balsa():
    global numbal
    numbal += 1
    time.sleep(.5)
    print('La balsa ', numbal, 'se ha ido')
    

for i in range(20):
    threading.Thread(target = hacker, args = [i]).start()
    threading.Thread(target=serf, args = [i]).start()
