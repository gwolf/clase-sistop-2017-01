#!/usr/bin/python2.7
# -*- coding: UTF-8 -*-

import commands

def cpuModelo():
	modelo = commands.getoutput("cat /proc/cpuinfo | grep -e 'model\ name*'")
	modelo = modelo.replace("model name	: ","")
	return modelo

def cpuUso():
	cpu_uso = commands.getoutput("top -d 1 -b -n2 | grep 'Cpu(s)'")

 	cpu_usuario = cpu_uso[cpu_uso.find("us")-5:cpu_uso.find("us")]
 	cpu_sistema = cpu_uso[cpu_uso.find("sist")-5:cpu_uso.find("sist,")]
 	cpu_inactivo = cpu_uso[cpu_uso.find("inact")-5:cpu_uso.find("inact")]
	# eliminamos la coma decimal por un punto
	cpu_uso=cpu_uso.replace(",",".")
 
	# devolvemos el % de uso
	return float(cpu_inactivo.strip())

def cpuUso2():
	cpu_uso = commands.getoutput("top -d 1 -b -n2 | grep 'Cpu(s)'")

 	cpu_usuario = cpu_uso[cpu_uso.find("us")-5:cpu_uso.find("us")]
 	cpu_sistema = cpu_uso[cpu_uso.find("sist")-5:cpu_uso.find("sist,")]
 	cpu_inactivo = cpu_uso[cpu_uso.find("inact")-5:cpu_uso.find("inact")]
	# eliminamos la coma decimal por un punto
	cpu_uso=cpu_uso.replace(",",".")
 
	# devolvemos el % de uso
	return float(cpu_sistema.strip())

def cpuUso3():
	cpu_uso = commands.getoutput("top -d 1 -b -n2 | grep 'Cpu(s)'")

 	cpu_usuario = cpu_uso[cpu_uso.find("us")-5:cpu_uso.find("us")]
 	cpu_sistema = cpu_uso[cpu_uso.find("sist")-5:cpu_uso.find("sist,")]
 	cpu_inactivo = cpu_uso[cpu_uso.find("inact")-5:cpu_uso.find("inact")]
	# eliminamos la coma decimal por un punto
	cpu_uso=cpu_uso.replace(",",".")
 
	# devolvemos el % de uso
	return float(cpu_usuario.strip())
 
def memTotal():
	mem_total =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '1 p'")
	return mem_total

def memLibre():
	mem_libre =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '2 p'")
	return mem_libre

def memDisponible():
	mem_libre =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '3 p'")
	return mem_libre

def memUso():
	mem_uso =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '7 p'")
	return mem_uso

def memSwapTotal():
	mem_swap =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '19 p'")
	return mem_swap

def memSwapLibre():
	mem_swap =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '20 p'")
	return mem_swap

def memSwapUso():
	mem_swap =  commands.getoutput("cat /proc/meminfo | while read c1 c2; do echo $c2; done | sed -n '6 p'")
	return mem_swap

def numProcesos():
	num_procesos = commands.getoutput("cat /proc/loadavg | grep -o '/[0-9]*'")
	num_procesos = num_procesos[1:]
	return num_procesos

def numProcesosEjecucion():
	num_procesos = commands.getoutput("cat /proc/loadavg | grep -o '[0-9]*/'")
	num_procesos = num_procesos[:-1]
	return num_procesos

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
	return str(horas) + ":" + str(horas) + ":" + str(segundos)

def tiempoFuncionamiento():
	t_funcionamiento = commands.getoutput("cat /proc/uptime | while read c1 c2; do echo $c1; done")
	t_funcionamiento = int(t_funcionamiento[:-3])
	return calculaHora(t_funcionamiento)

def tiempoInactivo():
	t_inactivo = commands.getoutput("cat /proc/uptime | while read c1 c2; do echo $c2; done")
	t_inactivo = int(t_inactivo[:-3])
	return calculaHora(t_inactivo)

print "El modelo del CPU es: " + cpuModelo()
print "El uso de procesador (inact) es del: %.2f%%" % cpuUso()
print "El uso de procesador (sist) es del: %.2f%%" % cpuUso2()
print "El uso de procesador (usuario) es del: %.2f%%" % cpuUso3()
print "La memoria total del sistema es: " + memTotal()
print "La memoria libre del sistema es: " + memLibre()
print "La memoria disponible del sistema es: " + memDisponible()
print "La memoria en uso del sistema es: " + memUso()
print "La memoria swap total del sistema es: " + memSwapTotal()
print "La memoria swap libre del sistema es: " + memSwapLibre()
print "La memoria swap en uso del sistema es: " + memSwapUso()
print "El numero de procesos total es: " + numProcesos()
print "El numero de procesos en ejecucion es: " + numProcesosEjecucion()
print "El tiempo de funcionamiento del sistema es: " + tiempoFuncionamiento()
print "El tiempo inactivo del sistema es: " + tiempoInactivo()