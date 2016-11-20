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

function cargar_lista() {
	if [[ ! -f tmp/list.txt ]]; then
		unzip -o FAULT.zip list.txt -d tmp
	fi
}

function guardar_lista() {
	zip FAULT.zip list.txt
}

echo -e `clear` 
origen=`echo "$PWD/funciones"`
echo "Utilice el comando $(tput bold)help$(tput sgr0) para más información."
echo -e "Utilice el comando $(tput bold)exit$(tput sgr0) para salir de la aplicación.\n"
while :; do
	prompt="\E[0;36m$USER \e[0;30m\\ \E[0;32m$PWD:\E[0m "
	echo -en "$prompt"
	read comando
	read -r arg0 arg1 <<< "$comando"
	case $arg0 in
		list )			#Listar
			cargar_lista
			while read line; do
				if [[ $line != "list.txt" ]]; then
					echo "$line"
				fi
			done <tmp/list.txt
			;;
		create )		#Crear
			if [[ ! -d tmp ]]; then
				mkdir tmp
			fi
			touch "tmp/$arg1"
			cargar_lista
			echo $arg1 >> tmp/list.txt
			cd tmp
			zip ../FAULT.zip "$arg1" list.txt
			cd ..
			;;
		open )			#Leer
			;;
		edit )			#Editar
			;;
		del )			#Borrar
			cargar_lista
			sed -i "/$arg1/d" tmp/list.txt &&	zip -d FAULT.zip $arg1
			cd tmp
			zip ../FAULT.zip list.txt
			cd ..
			;;
		help )			#Ayuda
			echo "Aquí va la ayuda";;
		exit )
			rm -rf tmp
			exit 0;;
		* )
			echo "Comando no reconocido";;
	esac
done