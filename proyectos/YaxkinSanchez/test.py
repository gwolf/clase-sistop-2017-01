#!/usr/bin/python2.7
# -*- Encoding: utf-8 -*-
#
#	Mini Monitor.py
#	Autor: David Yaxkin Sanchez Neri
#	
#	Script en Python que implementa un pequeño monitor de sistema.
#	

import time
import sys
from asciimatics.screen import Screen

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
	#Margenes verticales:
	for x in xrange(1,ALTURA-1):
		screen.print_at('|',0,x, COLOUR_GREEN, A_BOLD)
		screen.print_at('|',ANCHO-1,x, COLOUR_GREEN, A_BOLD)
	#Margenes horizontales:
	margen_horizontal = '+'
	for x in range(1,ANCHO-1):
		margen_horizontal += '-'
	margen_horizontal += '+'
	screen.print_at(margen_horizontal,0,0,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,2,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,6,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,9,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,12,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,ALTURA-7,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,ALTURA-3,COLOUR_GREEN,A_BOLD)
	screen.print_at(margen_horizontal,0,ALTURA-1,COLOUR_GREEN,A_BOLD)
	
#Función que describe el contenido de la interfaz
def demo(screen):
	while str(screen.get_event()) != 'KeyboardEvent: 113':
		margen(screen)
		screen.print_at('Mini Monitor',54,1, COLOUR_RED, A_BOLD)
		screen.print_at('Procesador:', 2, 3, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Uso de CPU:', 2, 4, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Memoria:', 2, 7, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Libre:', 2, 8, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Total:', 22, 8, COLOUR_YELLOW, A_BOLD)
		screen.print_at('En uso:',42, 8, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Swap:',62, 8, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Tiempo de funcionamiento:',2, 10, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Tiempo inactivo:',2, 11, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Total de procesos:', 2, 13, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Procesos activos:', 62, 13, COLOUR_YELLOW, A_BOLD)
		screen.print_at('PID', 2, 15, COLOUR_CYAN, A_BOLD)
		screen.print_at('Nombre', 12, 15, COLOUR_CYAN, A_BOLD)
		screen.print_at('Estado', 32, 15, COLOUR_CYAN, A_BOLD)
		screen.print_at('PID', 62, 15, COLOUR_CYAN, A_BOLD)
		screen.print_at('Nombre', 72, 15, COLOUR_CYAN, A_BOLD)
		screen.print_at('Estado', 92, 15, COLOUR_CYAN, A_BOLD)
		screen.print_at('Dispositivos externos:', 2, 34, COLOUR_MAGENTA, A_BOLD)
		screen.print_at('Presione q (minuscula) para salir.',2, ALTURA-2, COLOUR_RED, A_BOLD)
		screen.refresh()

#Inicialización de la interfaz
Screen.wrapper(demo)
