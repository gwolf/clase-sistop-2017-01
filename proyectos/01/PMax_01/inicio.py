#menu principal 
from lib import *
import threading
from os import system

cond=True
while cond:
	os.system("clear")
	print("\nIMPORTANTE: PARA EL MEJOR  FUNCIONAMIENTO DE ESTE  PROGRAMA  ES  RECOMENDABLE")
	print("QUE SE EJECUTE EN LA ALGUNA TERMINAL QUE TENGA LA VENTANA DE TAMANIO COMPLETO")
	print("ADEMAS  SE  RECOMIENDA  SEA  EJECUTADO  EN LA CARPETA DE ORIGEN  DEL PROGRAMA")
	print("\nIMPORTANTE 2: EL SISTEMA DONDE  VAYA A SER  EJECUTADO  DEBE  TENER  INSTALADO")
	print("PYTHON3 EL CUAL  SE PUEDE INSTALAR USANDO:")
	print("su -c \"apt-get install python3\"  o usando ")
	print("su -c \"aptitude install python3\"")
	print ("\n\t\tEste es el menu principal, elige alguna opcion: \n")
	print ("\t1) monitor del historial de procesos ")
	print ("\t2) monitor especifico de procesos")
	print ("\t3) depliegue de procesos actuales")
	print ("\t4) informacion actual tiempo real (no interrumpir)")
	print ("\t5) salir")
	opcion=input("\t\tOpcion: ")
	if opcion=='1':
		opc=threading.Thread(target=monH)
		opc.start()
		opc.join()
	elif opcion=='2':
		opc=threading.Thread(target=infoEsp)
		opc.start()
		opc.join()
	elif opcion=='3':
		opc=threading.Thread(target=monAct)
		opc.start()
		opc.join()
	elif opcion=='4':
		opc=threading.Thread(target=infoTR)
		opc.start()
		opc.join()
	elif opcion=='5':
		print("Es probable que durante la ejecucion de este programa")
		opcion=input("se crearan archivos extra, quieres eliminarlos?(s/n): ")
		if opcion.lower()=='s':
			os.system("rm  *.txt")
		cond=False
	else:
		print("Opcion no valida ")