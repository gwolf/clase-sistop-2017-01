#!/usr/bin/python
# -*- Encoding: utf-8 -*-
import time
from asciimatics.screen import Screen

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
i = 0
	
def demo(screen):
	while True:
		for x in xrange(1,23):
			screen.print_at('|                                                                              |',0,x, COLOUR_GREEN, A_BOLD)
		screen.print_at('+------------------------------------------------------------------------------+',0,0, COLOUR_GREEN, A_BOLD)
		screen.print_at('Mini Monitor',34,1, COLOUR_RED, A_BOLD)
		screen.print_at('+------------------------------------------------------------------------------+',0,2, COLOUR_GREEN, A_BOLD)
		screen.print_at('Uso de CPU:', 2, 3, COLOUR_YELLOW, A_BOLD)
		screen.print_at('Total procesos', 40, 3, COLOUR_YELLOW, A_BOLD)
		screen.print_at('+------------------------------------------------------------------------------+',0,4, COLOUR_GREEN, A_BOLD)
		screen.print_at('Memoria:', 2, 5, COLOUR_BLUE, A_BOLD)
		screen.print_at('Libre:', 2, 6, COLOUR_BLUE, A_BOLD)
		screen.print_at('Total:', 22, 6, COLOUR_BLUE, A_BOLD)
		screen.print_at('En uso:',42, 6, COLOUR_BLUE, A_BOLD)
		screen.print_at('Swap:',62, 6, COLOUR_BLUE, A_BOLD)
		screen.print_at('+------------------------------------------------------------------------------+',0,7, COLOUR_GREEN, A_BOLD)
		screen.print_at('Procesos:', 2, 8, COLOUR_CYAN, A_BOLD)
		screen.print_at('PID', 2, 9, COLOUR_CYAN, A_BOLD)
		screen.print_at('Nombre', 22, 9, COLOUR_CYAN, A_BOLD)
		screen.print_at('Estado', 42, 9, COLOUR_CYAN, A_BOLD)
		screen.print_at('Algo mas', 62, 9, COLOUR_CYAN, A_BOLD)
		screen.print_at('+------------------------------------------------------------------------------+',0,20, COLOUR_GREEN, A_BOLD)
		screen.print_at('Dispositivos externos:', 2, 21, COLOUR_MAGENTA, A_BOLD)
		screen.print_at('+------------------------------------------------------------------------------+',0,23, COLOUR_GREEN, A_BOLD)
		screen.print_at(str(i),0,0)
		screen.refresh()

Screen.wrapper(demo)
