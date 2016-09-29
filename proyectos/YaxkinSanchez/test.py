#!/usr/bin/python
# -*- Encoding: utf-8 -*-
#
#	MiniMonitor.py
#	Autor: David Yaxkin Sanchez Neri
#	
#	Script en Python que implementa un pequeño monitor de sistema.
#	

from asciimatics.screen import Screen
import time
import sys
import threading
import test2

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

#Cambia el tamaño de la terminal para su visualización
sys.stdout.write("\x1b[8;{rows};{cols}t".format(rows=ALTURA, cols=ANCHO))
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
	screen.print_at(margen_horizontal,0,ALTURA-7,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,ALTURA-3,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,ALTURA-1,COLOUR_GREEN,A_BOLD)

#Coloca datos en la interfaz
def colocaDatos(screen):
	test2.cpuModelo(screen)
	test2.kernel(screen)
	test2.cpuUsuario(screen)
	test2.cpuSistema(screen)
	test2.cpuInactivo(screen)
	test2.memTotal(screen)
	test2.memLibre(screen)
	test2.memDisponible(screen)
	test2.memUso(screen)
	test2.memSwapTotal(screen)
	test2.memSwapLibre(screen)
	test2.memSwapUso(screen)
	test2.tiempoFuncionamiento(screen)
	test2.tiempoInactivo(screen)
	test2.numProcesos(screen)
	test2.numProcesosEjecucion(screen)
	
#Función que describe el contenido de la interfaz
def demo(screen):
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
		screen.print_at('PID', 2, 18, COLOUR_CYAN, A_BOLD)
		screen.print_at('Nombre', 12, 18, COLOUR_CYAN, A_BOLD)
		screen.print_at('Estado', 32, 18, COLOUR_CYAN, A_BOLD)
		screen.print_at('PID', 62, 18, COLOUR_CYAN, A_BOLD)
		screen.print_at('Nombre', 72, 18, COLOUR_CYAN, A_BOLD)
		screen.print_at('Estado', 92, 18, COLOUR_CYAN, A_BOLD)
		screen.print_at('Dispositivos externos:', 2, 34, COLOUR_MAGENTA, A_BOLD)
		screen.print_at('Presione q (minuscula) para salir.',2, ALTURA-2, COLOUR_RED, A_BOLD)
		colocaDatos(screen)
		time.sleep(1)
		screen.refresh()

#Inicialización de la interfaz
def main():
	Screen.wrapper(demo)

main()
