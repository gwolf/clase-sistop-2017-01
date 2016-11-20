#
#MICRO SISTEMA DE ARCHIVOS
#participantes:
	# Max Armando Sanchez Hernandez
	# Perez Martinez David Antonio

#Este programa es un micro sistema de archivos que permite las siguientes operaciones:
# -anadir
# -listar directorio
# -crear archivo
# -borrar archivo
# Para esto se usara una tabla de equivalencia de operaciones
# 	Comando 				Proposito
# 	lsd						Lista directorio
# 	add cadena > archivo 	anade a un archivo una cadena, borra todo y lo agrega, si no existe lo crear
# 	add cadena >> archivo 	anade a un archivo una cadena, la anade al final sin modificar lo anterior, si no existe el archivo lo crea
# 	new archivo 			crea un archivo
# 	del archivo 			borra archivo
# 	cat archivo 			muestra lo que contiene un archivo
# 	exit 					sale del programa
from lib import *
def main():
	impPresentacion()
	comando=input(">: ").split(" ")
	dicOpe={"lsd":lsd,"add":add,"new":new,"del":dele,"cat":cat,"help":hel}
	while comando[0] != "exit":
		try:
			func=dicOpe[comando[0]]
			func(comando)
		except KeyError:
			print("comando errorneo")
		comando=input(">: ").split(" ")
main()