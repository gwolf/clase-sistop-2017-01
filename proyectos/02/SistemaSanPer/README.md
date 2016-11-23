FORMA DE EJECUTAR

$python3 MicroSistemaSanchezPerez.py

###Para detalles de cada función se tipea la función help

>: help


ESPECIFICACIONES DE PROGRAMA
El programa fue realizado sobre python 3
El sistema fue probado en OpenSuse y Ubuntu

ESPECIFIFICACIONES DE FUNCIONES PARA SU CORRECTO FUNCIONAMIENTO
1)El límite de archivos que se pueden crear es de 10
2)El el tamaño del nombre de un archivo a agregar es de máximo 10 caracteres
3)El tamaño máximo de todos los archivos es de 1000 caracteres
4)No pueden existir nombres de archivo que contengan el caracter 0

COMO SE RESUELVE
se crea un directorio base como un disco virtual donde se van poner direcciones de
acceso, estas direcciones apuntan a datos en otro archivo que contiene los datos 
asociados al archivo en esta direccion. 
Las operaciones de añadir (add),nuevo(new) y eliminar(del) actuan sobre estos archivos
modificandolos para que reflejen cambios en el documento ejemploTabla.txt. 