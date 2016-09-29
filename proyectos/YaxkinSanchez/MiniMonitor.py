#!/usr/bin/python
# -*- Encoding: utf-8 -*-
#####################################################################
#																	#
#	MiniMonitor.py 													#
#	Autor: David Yaxkin Sanchez Neri								#
#																	#
#	Script en Python que implementa un pequeño monitor de sistema.	#
#																	#
#####################################################################

from asciimatics.screen import Screen
import commands
import time
import sys
import threading
import psutil

#################
#	Variables	#
#################

#Variables para el manejo de la interfaz gráfica
ANCHO = 120
ALTURA = 40
COLOUR_BLACK = 0
COLOUR_RED = 1
COLOUR_GREEN = 2
COLOUR_YELLOW = 3
COLOUR_BLUE = 4
COLOUR_MAGENTA = 5
COLOUR_CYAN = 6
COLOUR_WHITE = 7
A_BOLD = 1
A_NORMAL = 2
A_REVERSE = 3
A_UNDERLINE = 4

#Variables útiles para algunas funciones
no_nucleos = int(commands.getoutput("grep processor /proc/cpuinfo | wc -l"))
no_funciones_monitor = 15

#Mutex que hace de multiplex junto con un contador para el contador de procesos e impresion
mutex_contador = threading.Semaphore(1)
global contador_procesos
contador_procesos = 0

#Señal para el proceso principal
senal_padre = threading.Semaphore(0)

#########################
#	Funciones útiles	#
#########################

#Funcion que lleva a cabo la sincronización para las funciones monitor
#Indicando que todas ya terminaron su función e impresión en pantalla,
#para evitar que la pantalla se refresque sin haberse impreso.
def sincronizaProcesos():
	global contador_procesos
	mutex_contador.acquire()
	contador_procesos += 1
	if contador_procesos == no_funciones_monitor:
		senal_padre.release()
	mutex_contador.release()

#Pequeña función para convertir de segundos a formato HH:MM:SS
def calculaHora(segundos):
	horas = segundos / 3600
	if horas < 10:
		horas = '0' + str(horas)
	minutos = (segundos % 3600) /60
	if minutos < 10:
		minutos = '0' + str(minutos)
	segundos = (segundos % 3600) % 60
	if segundos < 10:
		segundos = '0' + str(segundos)
	return str(horas) + ":" + str(minutos) + ":" + str(segundos)


#############################
#	Funciones decorador 	#
#############################

#Obtiene el modelo del CPU
def cpuModelo(screen):
	modelo = commands.getoutput("cat /proc/cpuinfo | grep -e 'model\ name*'")
	modelo = modelo.replace("model name	: ","")
	screen.print_at(modelo,14,3)
#Obtiene el kernel del SO
def kernel(screen):
	version_so = commands.getoutput("cat /proc/version | while read c1 c2 c3 c4; do echo $c1 $c2 $c3; done")
	screen.print_at(version_so,14,4)


#########################
#	Funciones monitor 	#
#########################

#Obtiene el uso del CPU por parte del usuario
def cpuUsuario(screen):
	cpu_estado_1 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3; do echo $c2; done")
	time.sleep(0.0)
	cpu_estado_2 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3; do echo $c2; done")
	cpu_uso = (int(cpu_estado_2) - int(cpu_estado_1))/no_nucleos
	screen.print_at(str(cpu_uso) + "%",11,7)
	sincronizaProcesos()

#Obtiene el uso del CPU por parte del sistema
def cpuSistema(screen):
	cpu_estado_1 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3 c4 c5; do echo $c4; done")
	time.sleep(0.0)
	cpu_estado_2 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3 c4 c5; do echo $c4; done")
	cpu_uso = (int(cpu_estado_2) - int(cpu_estado_1))/no_nucleos
	screen.print_at(str(cpu_uso) + "%",41,7)
	sincronizaProcesos()

#Obtiene el porcentaje de inactividad del CPU
def cpuInactivo(screen):
	cpu_estado_1 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3 c4 c5 c6; do echo $c5; done")
	time.sleep(0.0)
	cpu_estado_2 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3 c4 c5 c6; do echo $c5; done")
	cpu_uso = (int(cpu_estado_2) - int(cpu_estado_1))/no_nucleos
	screen.print_at(str(cpu_uso) + "%",72,7)
	sincronizaProcesos()

#Obtiene la cantidad de memoria principal total
def memTotal(screen):
	mem_total =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '1 p'")
	screen.print_at(mem_total,11,13)
	sincronizaProcesos()

#Obtiene la cantidad de memoria principal libre
def memLibre(screen):
	mem_libre =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '2 p'")
	screen.print_at(mem_libre,42,13)
	sincronizaProcesos()

#Obtiene la cantidad de memoria principal disponible
def memDisponible(screen):
	mem_disponible =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '3 p'")
	screen.print_at(mem_disponible,42,14)
	sincronizaProcesos()

#Obtiene la cantidad de memoria principal en uso
def memUso(screen):
	mem_uso =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '7 p'")
	screen.print_at(mem_uso,11,14)
	sincronizaProcesos()

#Obtiene la cantidad de memoria swap total
def memSwapTotal(screen):
	mem_swap =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '19 p'")
	screen.print_at(mem_swap,71,13)
	sincronizaProcesos()

#Obtiene la cantidad de memoria swap libre
def memSwapLibre(screen):
	mem_swaplibre =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '20 p'")
	screen.print_at(mem_swaplibre,102,13)
	sincronizaProcesos()

#Obtiene la cantidad de memoria swap en uso
def memSwapUso(screen):
	mem_swapuso =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '6 p'")
	screen.print_at(mem_swapuso,71,14)
	sincronizaProcesos()

#Obtiene el numero total de procesos
def numProcesos(screen):
	num_procesos = commands.getoutput("cat /proc/loadavg | grep -o '/[0-9]*'")
	num_procesos = num_procesos[1:]
	screen.print_at(num_procesos,21,16)
	sincronizaProcesos()

#Obtiene el numero de procesos en estado de ejecución
def numProcesosEjecucion(screen):
	num_procesos = commands.getoutput("cat /proc/loadavg | grep -o '[0-9]*/'")
	num_procesos = num_procesos[:-1]
	screen.print_at(num_procesos,80,16)
	sincronizaProcesos()

#Obtiene el tiempo de funcionamiento (uptime) del sistema
def tiempoFuncionamiento(screen):
	t_funcionamiento = commands.getoutput("cat /proc/uptime | while read c1 c2; do echo $c1; done")
	t_funcionamiento = int(t_funcionamiento[:-3])
	t_funcionamiento = calculaHora(t_funcionamiento)
	screen.print_at(t_funcionamiento,28,9)
	sincronizaProcesos()

#Obtiene el tiempo de inactividad del sistema
def tiempoInactivo(screen):
	t_inactivo = commands.getoutput("cat /proc/uptime | while read c1 c2; do echo $c2; done")
	t_inactivo = int(t_inactivo[:-3])
	t_inactivo = calculaHora(t_inactivo)
	screen.print_at(t_inactivo,19,10)
	sincronizaProcesos()

#Obtiene una lista de unos cuantos procesos
def procesos(screen):
	i = 0
	for item in psutil.get_pid_list():
		try:
			p = psutil.Process(item)
			if p.status != 'sleeping':
				if i >= 0 and i <=16:
					screen.print_at(str(p.pid),2,20+i)
					screen.print_at(str(p.name),10,20+i)
					screen.print_at(str(p.status),27,20+i)
				elif i>16 and i <=33:
					screen.print_at(str(p.pid),42,i+3)
					screen.print_at(str(p.name),50,i+3)
					screen.print_at(str(p.status),67,i+3)
				elif i>33 and i <=50:
					screen.print_at(str(p.pid),82,i-14)
					screen.print_at(str(p.name),90,i-14)
					screen.print_at(str(p.status),107,i-14)
				i += 1
		except:
			pass
	for item in psutil.get_pid_list():
		try:
			p = psutil.Process(item)
			if p.status == 'sleeping':
				if i >= 0 and i <=16:
					screen.print_at(str(p.pid),2,20+i)
					screen.print_at(str(p.name),10,20+i)
					screen.print_at(str(p.status),27,20+i)
				elif i>16 and i <=33:
					screen.print_at(str(p.pid),42,i+3)
					screen.print_at(str(p.name),50,i+3)
					screen.print_at(str(p.status),67,i+3)
				elif i>33 and i <=50:
					screen.print_at(str(p.pid),82,i-14)
					screen.print_at(str(p.name),90,i-14)
					screen.print_at(str(p.status),107,i-14)
				i += 1
		except:
			pass		
	sincronizaProcesos()


#########################
#	Funciones interfaz	#
#########################

#Función que define los márgenes de la interfaz
def margen(screen):
	#Margenes verticales y limpieza de pantalla:
	margen_vertical = '|'
	for x in range(1,ANCHO-1):
		margen_vertical += ' '
	margen_vertical += '|'
	for x in range(1,ALTURA-1):
		screen.print_at(margen_vertical,0,x, COLOUR_GREEN, A_BOLD)
	#Divisiones horizontales:
	margen_horizontal = '+'
	for x in range(1,ANCHO-1):
		margen_horizontal += '-'
	margen_horizontal += '+'
	screen.print_at(margen_horizontal,0,0,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,2,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,5,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,11,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,15,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,17,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,ALTURA-3,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,ALTURA-1,COLOUR_GREEN,A_BOLD)
	#Divisione extra
	screen.print_at('+',60,11,COLOUR_GREEN,A_BOLD)
	for x in range(12,15):
		screen.print_at('|',60,x,COLOUR_GREEN,A_BOLD)
	screen.print_at('+',60,15,COLOUR_GREEN,A_BOLD)
	screen.print_at('+',40,17,COLOUR_GREEN,A_BOLD)
	for x in range(18,ALTURA-3):
		screen.print_at('|',40,x,COLOUR_GREEN,A_BOLD)
	screen.print_at('+',40,ALTURA-3,COLOUR_GREEN,A_BOLD)
	screen.print_at('+',80,17,COLOUR_GREEN,A_BOLD)
	for x in range(18,ALTURA-3):
		screen.print_at('|',80,x,COLOUR_GREEN,A_BOLD)
	screen.print_at('+',80,ALTURA-3,COLOUR_GREEN,A_BOLD)

#Hilos que colocan los datos en la interfaz
def lanzaHilos(screen):
	threading.Thread(target=cpuUsuario, args=[screen]).start()
	threading.Thread(target=cpuSistema, args=[screen]).start()
	threading.Thread(target=cpuInactivo, args=[screen]).start()
	threading.Thread(target=memTotal, args=[screen]).start()
	threading.Thread(target=memLibre, args=[screen]).start()
	threading.Thread(target=memDisponible, args=[screen]).start()
	threading.Thread(target=memUso, args=[screen]).start()
	threading.Thread(target=memSwapTotal, args=[screen]).start()
	threading.Thread(target=memSwapLibre, args=[screen]).start()
	threading.Thread(target=memSwapUso, args=[screen]).start()
	threading.Thread(target=tiempoFuncionamiento, args=[screen]).start()
	threading.Thread(target=tiempoInactivo, args=[screen]).start()
	threading.Thread(target=numProcesos, args=[screen]).start()
	threading.Thread(target=numProcesosEjecucion, args=[screen]).start()
	threading.Thread(target=procesos, args=[screen]).start()

#Función que crea la estructura de la interfaz
def interfaz(screen):
	global contador_procesos
	while str(screen.get_event()) != 'KeyboardEvent: 113':
		margen(screen)
		screen.print_at('Mini Monitor',54,1, COLOUR_RED, A_BOLD)
		screen.print_at('Procesador:', 2, 3, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Kernel SO:', 2, 4, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Uso de CPU', 2, 6, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Usuario:', 2, 7, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Sistema:', 32, 7, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Inactivo:', 62, 7, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Tiempo de funcionamiento:',2, 9, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Tiempo inactivo:',2, 10, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Memoria', 2, 12, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Total:', 2, 13, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Libre:', 29, 13, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Activa:',2, 14, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Disponible:',29, 14, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Swap', 62, 12, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Total:', 62, 13, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Libre:', 89, 13, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Activa:',62, 14, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Total de procesos:', 2, 16, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Procesos activos:', 62, 16, COLOUR_YELLOW, A_BOLD)
		for i in range(3):
			screen.print_at('PID', 3+40*i, 18, COLOUR_CYAN, A_BOLD)
			screen.print_at('Nombre', 12+40*i, 18, COLOUR_CYAN, A_BOLD)
			screen.print_at('Estado', 27+40*i, 18, COLOUR_CYAN, A_BOLD)
		screen.print_at('Presione q (minuscula) para salir.',2, ALTURA-2, COLOUR_RED, A_BOLD)
		cpuModelo(screen)
		kernel(screen)
		lanzaHilos(screen)
		
		senal_padre.acquire()
		mutex_contador.acquire()
		contador_procesos -= no_funciones_monitor
		mutex_contador.release()
		screen.refresh()

#Función de interfaz dummy para permitir que la interfaz real pueda visualizarse correctamente.
def carga(screen):
	screen.refresh()


#################
#	Ejecución 	#
#################

#Cambia el tamaño de la terminal para la correcta visualización del programa.
sys.stdout.write("\x1b[8;{rows};{cols}t".format(rows=ALTURA, cols=ANCHO))
Screen.wrapper(carga)
time.sleep(0.01)

#Inicialización de la interfaz
Screen.wrapper(interfaz)
