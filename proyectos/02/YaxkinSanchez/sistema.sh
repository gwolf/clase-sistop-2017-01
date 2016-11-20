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
	if [[ ! -f tmp/rootlist ]]; then
		unzip -o FAULT.zip rootlist -d tmp
	fi
}

function guardar_lista() {
	zip FAULT.zip rootlist
}


function archivo_existe() {
	existe=0
	while read line; do
		if [[ $line = $arg1 ]]; then
			existe=1
		fi
	done <tmp/rootlist
	echo $existe
}

echo "Utilice el comando $(tput bold)help$(tput sgr0) para más información."
echo -e "Utilice el comando $(tput bold)exit$(tput sgr0) para salir de la aplicación.\n"
while :; do
	prompt="\E[0;36mLocation: \E[0;32mroot/ \E[0;37m>\E[0m "
	echo -en "$prompt"
	read comando
	read -r arg0 arg1 <<< "$comando"
	case $arg0 in
		list )			#Listar
			cargar_lista
			while read line; do
				if [[ $line != "rootlist" ]]; then
					echo "$line"
				fi
			done <tmp/rootlist
			;;
		create )		#Crear
			cargar_lista
			if [[ $(archivo_existe) -eq 1 ]]; then
				echo "Ya existe un archivo con este nombre"
			else
				touch "tmp/$arg1"
				echo $arg1 >> tmp/rootlist
				cd tmp
				zip ../FAULT.zip "$arg1" rootlist
				cd ..
			fi
			;;
		read )			#Leer
			cargar_lista
			if [[ $(archivo_existe) -ne 1  ]]; then
				echo "No existe un archivo con este nombre"
			else
				unzip -o FAULT.zip $arg1 -d tmp
				while read line; do
					echo "$line"
				done <"tmp/$arg1"
			fi
			;;
		edit )			#Editar
			cargar_lista
			if [[ $(archivo_existe) -ne 1  ]]; then
				echo "No existe un archivo con este nombre"
			else
				unzip -o FAULT.zip $arg1 -d tmp
				vi "tmp/$arg1"
				cd tmp
				zip ../FAULT.zip "$arg1"
				cd ..
			fi
			;;
		del )			#Borrar
			cargar_lista
			if [[ $(archivo_existe) -ne 1  ]]; then
				echo "No existe un archivo con este nombre"
			else
				sed -i "/$arg1/d" tmp/rootlist && zip -d FAULT.zip $arg1
				cd tmp
				zip ../FAULT.zip rootlist
				cd ..
			fi
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