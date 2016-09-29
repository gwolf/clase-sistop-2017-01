#!/usr/bin/python
# -*- Encoding: utf-8 -*-
#
#	MMFunciones.py
#	Autor: David Yaxkin Sanchez Neri
#	
#	Script en Python que define funciones para obtener los datos del sistema.
#	

import time
import commands
import asciimatics

#Variables útiles para algunas funciones
#Número de núcleos del procesador
no_nucleos = int(commands.getoutput("grep processor /proc/cpuinfo | wc -l"))
#Número de funciones monitor
no_funciones_monitor = 14;

#Obtiene el modelo del CPU
def cpuModelo(screen):
	modelo = commands.getoutput("cat /proc/cpuinfo | grep -e 'model\ name*'")
	modelo = modelo.replace("model name	: ","")
	screen.print_at(modelo,14,3)

#Obtiene el uso del CPU por parte del usuario
def cpuUsuario(screen):
	cpu_estado_1 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3; do echo $c2; done")
	time.sleep(1)
	cpu_estado_2 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3; do echo $c2; done")
	cpu_uso = (int(cpu_estado_2) - int(cpu_estado_1))/no_nucleos
	screen.print_at(str(cpu_uso) + "%",11,7)

#Obtiene el uso del CPU por parte del sistema
def cpuSistema(screen):
	cpu_estado_1 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3 c4 c5; do echo $c4; done")
	time.sleep(1)
	cpu_estado_2 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3 c4 c5; do echo $c4; done")
	cpu_uso = (int(cpu_estado_2) - int(cpu_estado_1))/no_nucleos
	screen.print_at(str(cpu_uso) + "%",41,7)

#Obtiene el porcentaje de inactividad del CPU
def cpuInactivo(screen):
	cpu_estado_1 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3 c4 c5 c6; do echo $c5; done")
	time.sleep(1)
	cpu_estado_2 = commands.getoutput("cat /proc/stat | grep 'cpu ' | while read c1 c2 c3 c4 c5 c6; do echo $c5; done")
	cpu_uso = (int(cpu_estado_2) - int(cpu_estado_1))/no_nucleos
	screen.print_at(str(cpu_uso) + "%",72,7)

#Obtiene el kernel del SO
def kernel(screen):
	version_so = commands.getoutput("cat /proc/version | while read c1 c2 c3 c4; do echo $c1 $c2 $c3; done")
	screen.print_at(version_so,14,4)

#Obtiene la cantidad de memoria principal total
def memTotal(screen):
	mem_total =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '1 p'")
	screen.print_at(mem_total,11,13)

#Obtiene la cantidad de memoria principal libre
def memLibre(screen):
	mem_libre =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '2 p'")
	screen.print_at(mem_libre,42,13)

#Obtiene la cantidad de memoria principal disponible
def memDisponible(screen):
	mem_disponible =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '3 p'")
	screen.print_at(mem_disponible,42,14)

#Obtiene la cantidad de memoria principal en uso
def memUso(screen):
	mem_uso =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '7 p'")
	screen.print_at(mem_uso,11,14)

#Obtiene la cantidad de memoria swap total
def memSwapTotal(screen):
	mem_swap =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '19 p'")
	screen.print_at(mem_swap,71,13)

#Obtiene la cantidad de memoria swap libre
def memSwapLibre(screen):
	mem_swaplibre =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '20 p'")
	screen.print_at(mem_swaplibre,102,13)

#Obtiene la cantidad de memoria swap en uso
def memSwapUso(screen):
	mem_swapuso =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '6 p'")
	screen.print_at(mem_swapuso,71,14)

#Obtiene el numero total de procesos
def numProcesos(screen):
	num_procesos = commands.getoutput("cat /proc/loadavg | grep -o '/[0-9]*'")
	num_procesos = num_procesos[1:]
	screen.print_at(num_procesos,21,16)

#Obtiene el numero de procesos en estado de ejecución
def numProcesosEjecucion(screen):
	num_procesos = commands.getoutput("cat /proc/loadavg | grep -o '[0-9]*/'")
	num_procesos = num_procesos[:-1]
	screen.print_at(num_procesos,80,16)

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

#Obtiene el tiempo de funcionamiento (uptime) del sistema
def tiempoFuncionamiento(screen):
	t_funcionamiento = commands.getoutput("cat /proc/uptime | while read c1 c2; do echo $c1; done")
	t_funcionamiento = int(t_funcionamiento[:-3])
	t_funcionamiento = calculaHora(t_funcionamiento)
	screen.print_at(t_funcionamiento,28,9)

#Obtiene el tiempo de inactividad del sistema
def tiempoInactivo(screen):
	t_inactivo = commands.getoutput("cat /proc/uptime | while read c1 c2; do echo $c2; done")
	t_inactivo = int(t_inactivo[:-3])
	t_inactivo = calculaHora(t_inactivo)
	screen.print_at(t_inactivo,19,10)

