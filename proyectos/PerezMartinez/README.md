MONITOR DE SISTEMA
PÉREZ MARTINEZ DAVID ANTONIO

OBJETIVO

Este Sistema monitorea algunos de sus recursos a través de hilos, en los cuáles se pretende eliminar algún problema
como concurrencia, espera activa etc. 

EJECUCIÓN DEL MONITOR

Para su correcto funcionamiento se requiere python 2.7
Para ejecutar el código basta con teclear desde la terminal
	
	$ python monitor.py

El cual desplegará una ventana con los datos del monitor del sistema

CARACTERISTICA DEL MONITOR

Este monitor trabaja abriendo directamente los directorios de /proc, donde se obtendrá la información de cada recurso, al ejecutar
cada hilo se resolvió el problema de la inanición y la concurrencia, ya que al abrir un archivo solo uno puede trabajar a la vez sobre el, así que se 
implementaron semaforos para tener un orden en la obtención de cada recurso deseado, así pues este monitor trabaja de fomra en que primero hace llamda
al estado del disco seguido por memoria, cpu y por ultimo se agrega detalles de cada una de las columnas del disco.

Nota: El monitor de sistema depnderá de la arquitectura del sistema proc de linux ya que algunas rutas a las cuales se accede podría teenr conflictos al intentar encontrar un archivo con ese nombre, este monitor fue probado en debian y opensuse




