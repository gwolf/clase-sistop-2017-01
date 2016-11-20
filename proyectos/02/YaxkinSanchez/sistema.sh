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

#Carga la Lista de Asignación en tmp si no se encuentra
function cargar_lista() {
		unzip -uq FAULT.zip rootlist -d tmp
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
cargar_lista
echo "Utilice el comando $(tput bold)help$(tput sgr0) para más información."
echo -e "Utilice el comando $(tput bold)exit$(tput sgr0) para salir de la aplicación.\n"
while :; do
	prompt="\E[0;36mLocation: \E[0;32mroot/ \E[0;37m>\E[0m "
	echo -en "$prompt"
	read comando
	read -r arg0 arg1 <<< "$comando"
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
			if [[ $(archivo_existe) -eq 1 ]]; then
				echo "Ya existe un archivo con este nombre"
			else
				touch "tmp/$arg1"
				echo $arg1 >> tmp/rootlist
				cd tmp
				zip -q ../FAULT.zip "$arg1" rootlist
				cd ..
			fi
			;;

		#Lectura de un nuevo archivo:
		#Se verifica si la Lista de Asignacion contiene una entrada para el nombre del archivo:
		#	- Si existe, carga el archivo y lo imprime en la salida estándar
		#	- Si no existe, notifica al usuario
		read )			
			if [[ $(archivo_existe) -ne 1  ]]; then
				echo "No existe un archivo con este nombre"
			else
				unzip -uq FAULT.zip $arg1 -d tmp
				while read line; do
					echo "$line"
				done <"tmp/$arg1"
			fi
			;;

		#Lectura de un nuevo archivo:
		#Se verifica si la Lista de Asignacion contiene una entrada para el nombre del archivo:
		#	- Si existe, carga el archivo y lo abre con el editor de texto vi
		#	- Si no existe, notifica al usuario
		edit )			
			if [[ $(archivo_existe) -ne 1  ]]; then
				echo "No existe un archivo con este nombre"
			else
				unzip -uq FAULT.zip $arg1 -d tmp
				vi "tmp/$arg1"
				cd tmp
				zip -q ../FAULT.zip "$arg1"
				cd ..
			fi
			;;

		#Lectura de un nuevo archivo:
		#Se verifica si la Lista de Asignacion contiene una entrada para el nombre del archivo:
		#	- Si existe, elimina su entrada correspondiente en la Lista de Asignación
		#	- Si no existe, notifica al usuario
		del )			
			if [[ $(archivo_existe) -ne 1  ]]; then
				echo "No existe un archivo con este nombre"
			else
				sed -i "/$arg1/d" tmp/rootlist
				cd tmp
				zip -q ../FAULT.zip rootlist
				cd ..
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
			echo -e "\tedit\t\tEdita un archivo en vi"
			echo -e "\t\t\tSintáxis: edit <archivo>\n"
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