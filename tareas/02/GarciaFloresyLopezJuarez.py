#Elaborado por Garcia Flores y Lopez Juarez
#con vase a la explicacion y codigo de
#http://www.esi.uclm.es/www/dvallejo/pctr/slides/t2_semaforos.2x4.pdf

#http://sopa.dis.ulpgc.es/fso/teoria/FSO-03-Receta%20para%20resolver%20problemas%20de%20sincronizacion.pdf

#Agregamos las bibliotecas que vamos a usar 
import threading
import time
import random
#Declaran las variables globales en este caso contadores para renos
#y para elfos 
global contareno,contaelfi
#iniciamos las variables en 0
contareno=0
contaelfi=0
#Agragamos el mutex estar revisando los contadores.
contamux=threading.Semaphore(1)
#Senal para elfos que seran atendidos
senelfi=threading.Semaphore(0)
#Senal para renos para que vayan a descansar 
senenos=threading.Semaphore(0)
#Agregamos un mutex para limitar y proteger el grupo de elfos.
elfigrume=threading.Semaphore(1)
#Senal para despertar a Santa.
senasanta=threading.Semaphore(0)
#Definimos las funciones 
def ayuelfi():
	print "***Santa esta apoyando a los elfos :)***"
	time.sleep(0.5)
	print "***Santa ha terminado con los elgos u.uzzzZZZ***"
def esnavidadsanta():
	print "***Santa sale volando por el mundo con los juguetes***"
	time.sleep(2.5)
	print "***Santa esta de vuelta***"
def renodesca(num):
	print "***El reno con el numero %d se va de vacaciones***" % num
	time.sleep(random.random()*9)
def elfi(num):
	print "***El elfo %d pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***" % num
	#El elfo adquiere proteccion por el mutex para evitar que mas elfos se acumulen por si ya son 3.
	elfigrume.acquire()
	#despues el mutex para aumentar el su contador.
	contamux.acquire()
	contaelfi=contaelfi+1
	#Si contaelfi es = 3 entonces despertamos a santa
	if contaelfi == 3: #condicional if para contador de elfos
		print "***Ya somos 3 elfos Despierten al patron***"
		senasanta.release()	
	else :

#Si es falso se libera el mutex para recibir elfos.
                elfigrume.release()
#Y esta libre el mutex contador.
                contamux.release()
#El elfo notifica que fue atendido 
                senelfi.acquire()
        print "***El elfo %d esta atendido***" % num
	#Bajamos el contador.
	contamux.acquire()
	contaelfi=contaelfi-1
	#El ultimo elfo libera el mutex
	if contaelfi == 0:
		elfigrume.release()
	#Y libera el mutex para el contador
	contamux.release()

def reno(num):
	while True: 
		#El reno regresa de su descnaso.
		print "***El reno %d ha regresado***." % num
		#Adquiere el mutex para aumentar su contador.
		contamux.acquire()
                contareno=0
		contareno=contareno+1
#Si los 9 renos estan de regreso, despiertan a Santa para salir.
		if contareno == 9: #condicional para salir si estan los 9
	         print "***Estan los 8 renos con Rodolfo llamar al jefazo***"
		 senasanta.release()
		#Y se libera el mutex para el contador y esperan pacientemente
		 contamux.release()
		#Los renos adquieren la senal de regreso.
		 sennenos.acquire()
		
		#Y se toman sus merecidas vacaciones se van a Miami :9
		 renodesca(num)

def santa():
	while True:
		#Santa despierta al ser llamado por los elfos o los renos pobre santa u.u
		senasanta.acquire()
		#Santa adquiere el mutex para revisar a los contadores
		contamux.acquire()
		#Si lo llaman los renos tendra que despertar u.u
		if  contareno== 9:
			#Sale a repartir juguetes por el mundo \n.n/
			esnavidadasanta()
			#Modifica el contador de los renos.
			contareno=contareno-9
			#Y manda una senal de que ya regresaron
			for i in range(9):
				senenos.release()
		#Si lo llaman los elfos....
		elif contador_elfos == 3:
			#Les ayuda.
			ayudar_elfos()
			#Y manda una senal de que han sido despachados.
			for i in range(3):
				senenos.release()
#Al terminar su labor, libera el mutex y regresa a dormir n.nzzZ
		contamux.release()
elfihilo = 0
renohilo = 0
# Creacion de hilo unico para Santa.
threading.Thread(target=santa, args=[]).start()

#creacion de los 9 hilos para renos.
for i in range(1,10):
	threading.Thread(target=reno, args=[i]).start()

#Hilos para los elfos.
while True:
	time.sleep(0.3)
	if random.random() < 0.90:
		threading.Thread(target=elfi, args=[elfihilo]).start()
		elfihilo=elfihilo+1

