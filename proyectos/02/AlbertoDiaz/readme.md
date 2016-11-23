# MiniSistemaArchivos
##Autor
Carlos Alberto Díaz Olivares
##Lenguaje Implementado
Python
##Version de Python
Este programa funciona con la versión 3 de Python
##Problema a resolver
Este programa busca implementar un Mini Sistema de Archivos dentro de un archivo del sistema
##Logica de Operacion
Se maneja creacion de "archivos" dentro de bloques de tamaño definido dentro de un archivo comun y corriente. Para pruebas de ejecucion se establecio como limite 20 caracteres para el nombre de los archivos y 50 caracteres para el contenido de los archivos. Para la implementación se opto por guardar la ubicacion de cada archivo en 4 partes: Inicio del nombre, fin del nombre, inicio del contenido, fin del contenido, de cada "archivo".
Limitantes:
A pesar de que se tiene una funcion para el borrado de archivos, esta unicamente borra sus referencias, quedando la informacion escrita dentro del archivo. Esto nos pone en una situacion incomoda ya que mientras se van creando y eliminando archivos el archivo contenedor siguie creciendo.
##Ejecucion
Solo basta con la ejecucion del siguiente comando en una terminal Linux con python 3
	python3 miniSistemaArchivos.py
##Sitios de Consulta
http://sistop.gwolf.org/ | Para la comprension del manejo de memoria y de archivos.
https://docs.python.org/3 | Para la comprension del manejo de archivos en lenguaje Python
