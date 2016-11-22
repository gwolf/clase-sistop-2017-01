#!/bin/bash

#####################################################################
#																	#
#	sistema.sh 														#
#	Autor: David Yaxkin Sanchez Neri								#
#																	#
#	Script en Bash que implementa una shell interactiva			 	#
#	para la simulación de un sistema de archivos 					#
#	FAULT (File Allocation Using List of Text)						#
#																	#
#####################################################################

#Verifica si el sistema de archivos y la Lista de Asignación existe y carga la Lista en tmp
function cargar_sistema() {
	if [[ ! -f FAULT.zip ]]; then
		echo "Error: Sistema de archivos FAULT no encontrado :<"
		exit 1
	else
		unzip -uq FAULT.zip rootlist -d tmp
		if [[ $? -ne 0 ]]; then
			echo "Error: No se encuentra la Lista de Asignación :<"
			exit 1
		fi
	fi
}

#Verifica si a un archivo le corresponde una entrada en la Lista de Asignación
function archivo_existe() {
	existe=0
	while read line; do
		if [[ $line = $arg1 ]]; then
			existe=1
		fi
	done <tmp/rootlist
	echo $existe
}

#Interfaz de usuario
cargar_sistema
echo "Utilice el comando $(tput bold)help$(tput sgr0) para más información."
echo -e "Utilice el comando $(tput bold)exit$(tput sgr0) para salir de la aplicación.\n"
while :; do
	prompt="\E[0;36mLocation: \E[0;32mroot/ \E[0;37m>\E[0m "
	echo -en "$prompt"
	read comando
	read -r arg0 arg1 arg2 <<< "$comando"
	case $arg0 in

		#Listado de los contenidos del directorio raíz:
		#Se realiza la lectura de la Lista de Asignación que contiene los nombres de los archivos,
		#dicha lista está contenida en el mismo sistema de archivos
		list )			
			while read line; do
				if [[ $line != "rootlist" ]]; then
					echo "$line"
				fi
			done <tmp/rootlist
			;;

		#Creación de un nuevo archivo:
		#Se verifica si la Lista contiene una entrada para el nombre del archivo:
		#	- Si existe, notifica al usuario
		#	- Si no existe, crea el archivo y una entrada en la Lista de Asignación en tmp
		#	  y hace la respectiva escritura en el sistema de archivos
		create )
			if [[ $arg1 = "" ]]; then
				echo "Faltan argumentos. Sintáxis: create <archivo>"
	 		elif [[ $(archivo_existe) -eq 1 ]]; then
				echo "Ya existe un archivo con este nombre."
			elif [[ "${#arg1}" -gt 12 ]]; then
				echo "Longitud máxima de nombre de archivo (incluyendo extensión): 12."
				echo "Intente de nuevo."
			else
				touch "tmp/$arg1"
				echo $arg1 >> tmp/rootlist
				zip -qj FAULT.zip "tmp/$arg1" tmp/rootlist
			fi
			;;

		#Lectura de un nuevo archivo:
		#Se verifica si la Lista de Asignacion contiene una entrada para el nombre del archivo:
		#	- Si existe, carga el archivo y lo imprime en la salida estándar
		#	- Si no existe, notifica al usuario
		read )
			if [[ $arg1 = "" ]]; then
				echo "Faltan argumentos. Sintáxis: read <archivo>"
			elif [[ $(archivo_existe) -ne 1  ]]; then
				echo "No existe un archivo con este nombre."
			else
				unzip -uq FAULT.zip $arg1 -d tmp
				echo -e "\n   $arg1 "
				for (( i = 0; i < `expr ${#arg1} + 6`; i++ )); do
					echo -n "-"
				done
				echo
				while read line; do
					echo "$line"
				done <"tmp/$arg1"
				echo
			fi
			;;

		#Escritura en un archivo:
		#Se verifica si la Lista de Asignacion contiene una entrada para el nombre del archivo:
		#	- Si existe, carga el archivo y escribe la cadena pasada como parámetro en el archivo
		#	- Si no existe, notifica al usuario
		#Nota: este método sobreescribe el archivo
		write )
			if [[ $arg1 = "" && $arg2 = "" ]]; then
				echo "Faltan argumentos. Sintáxis: write <archivo> <cadena>"
			elif [[ $(archivo_existe) -ne 1  ]]; then
				echo "No existe un archivo con este nombre."
			else
				unzip -uq FAULT.zip $arg1 -d tmp
				echo -e "$arg2" > "tmp/$arg1"
				zip -uqj FAULT.zip "tmp/$arg1"
			fi
			;;


		#Agregar en un archivo:
		#Se verifica si la Lista de Asignacion contiene una entrada para el nombre del archivo:
		#	- Si existe, carga el archivo y agrega la cadena pasada como parámetro en el archivo
		#	- Si no existe, notifica al usuario
		#Nota: este método sobreescribe el archivo
		append )
			if [[ $arg1 = "" && $arg2 = "" ]]; then
				echo "Faltan argumentos. Sintáxis: append <archivo> <cadena>"
				
			elif [[ $(archivo_existe) -ne 1  ]]; then
				echo "No existe un archivo con este nombre."
			else
				unzip -uq FAULT.zip $arg1 -d tmp
				echo -e "$arg2" >> "tmp/$arg1"
				zip -uqj FAULT.zip "tmp/$arg1"
			fi
			;;

		#Eliminación de un archivo:
		#Se verifica si la Lista de Asignacion contiene una entrada para el nombre del archivo:
		#	- Si existe, elimina su entrada correspondiente en la Lista de Asignación
		#	- Si no existe, notifica al usuario
		del )
			if [[ $arg1 = "" ]]; then
				echo "Faltan argumentos. Sintáxis: del <archivo>"
			elif [[ $(archivo_existe) -ne 1  ]]; then
				echo "No existe un archivo con este nombre."
			else
				sed -i "/\<$arg1\>/d" tmp/rootlist
				zip -uqj FAULT.zip tmp/rootlist
			fi
			;;

		#Lista con los comandos disponibles
		help )			
			echo -e "\n\t$(tput bold)COMANDO\t\tDESCRIPCIÓN$(tput sgr0)\n"
			echo -e "\tlist\t\tLista el contenido del directorio\n"
			echo -e "\tcreate\t\tCrea un archivo nuevo"
			echo -e "\t\t\tSintáxis: create <archivo>\n"
			echo -e "\tread\t\tLee un archivo"
			echo -e "\t\t\tSintáxis: read <archivo>\n"
			echo -e "\twrite\t\tEscribe <cadena> en <archivo>."
			echo -e "\t\t\tNota: Este comando realiza sobreescritura"
			echo -e "\t\t\tSintáxis: write <archivo>\n"
			echo -e "\tappend\t\tAgrega <cadena> en <archivo>."
			echo -e "\t\t\tSintáxis: append <archivo>\n"
			echo -e "\tdel\t\tElimina un archivo"
			echo -e "\t\t\tSintáxis: del <archivo>\n"
			echo -e "\thelp\t\tMuestra esta ayuda\n"
			echo -e "\texit\t\tSalir de la aplicación\n"
			;;

		#Al salir:
		#	- "Limpia la basura": Elimina los archivos que no contienen una entrada en la Lista de Asignación
		#	- Remueve tmp
		exit )
			unzip -l FAULT.zip | while read c1 c2 c3 c4; do echo $c4; done | sed '/Name/d;/----/d;/^$/d' > tmp/fs-content
			grep -v -Ff tmp/rootlist tmp/fs-content > tmp/garbage-collector
			while read line; do
				zip -dq FAULT.zip $line
			done <tmp/garbage-collector
			rm -rf tmp
			exit 0;;
		* )
			echo "Comando no reconocido";;
	esac
done