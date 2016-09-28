#Miguel Angel Vargas Espinosa SISTEMAS OPERATIVOS
import threading
import queue
import time

Llegaron = threading.Semaphore(0)
Subir = threading.Semaphore(0)
cola_linux = queue.Queue()
cola_microsoft = queue.Queue()
num_programadores=20 #Este numero puede variar 
loop=0

class programadores:
    def __init__(self,tipo,num): #constructor de la clase nos genera objetos del tipo programador
        self.num = num
        self.tipo = tipo
        self.evento = threading.Event() # Event funciona como el mutex
        #wait marca la bandera como true, y clear limpia dicha bandera y la regresa a false
    def fila(self):
        print("El programador del %s Numero %i espera en la fila"%(self.tipo,self.num))
        self.evento.wait()
        self.evento.clear()
    def run(self):
        self.fila()

class barco:
    def __init__(self): #Init es nuestro constructor de la clase Barco
        self.abordo = []
    def abordar(self):
        global loop
        global num_programadores
        print('\n El barco llega y Abordan 4 programadores')
        while len(self.abordo) != 4:
            L = cola_linux.get()
            W = cola_microsoft.get()
            L.evento.set()
            W.evento.set()
            self.abordo.append(L)
            self.abordo.append(W)
            loop +=1
        print("El barco llega al evento, descargando...")
        for pas in self.abordo:
            pas.evento.set()
        self.abordo = []
        print("Regresando a la orilla...")
        time.sleep(2)     
    def run(self):
        while not cola_linux.empty() and not cola_microsoft.empty():
            self.abordar()
            print('Han cruzado %i programadores hasta ahora...' % int(loop*2))
        print("Han pasado todos los programadores sin peleas ni arañazos")

if (num_programadores % 2 == 0):
    for i in range(num_programadores):
        L = programadores("TeamLinux",i)
        M = programadores("TeamWindos",i)
        cola_linux.put(L)
        cola_microsoft.put(M)
        threading.Thread(target=L.run).start()
        threading.Thread(target=M.run).start()
if (num_programadores % 2 != 0):       
    print ("Intente con un número par de programadores para no volcar el barco")

Barco = barco()
time.sleep(3)
threading.Thread(target=Barco.run).start()
input('\n Eleven Anclas \n\n')
