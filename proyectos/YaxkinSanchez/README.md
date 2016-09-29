# Mini Monitor

## Version
1.0

## Autor
David Yaxkin Sánchez Neri

## Descripción
Mini Monitor es una aplicación que hace de un monitor básico de recursos:
* Uso de CPU.
* Tiempo de funcionamiento (uptime)
* Uso de Memoria.
También monitorea el estado de los procesos, dando prioridad a mostrar los procesos no "dormidos".

La interfaz de Mini Monitor es muy sencilla, tan sencilla que el usuario solo tiene que observar y cuando esté satisfecho, salir (presionando q).

<img src="./screenshot1.png" alt="Ventana 01" style= "width: 100px;">

## Ejecución
Para su ejecución, basta con colocarse en el directorio donde se encuentra el archivo con el código fuente, y escribir el comando:
`$ python MiniMonitor.py`
## Controles
q - Sale de Mini Monitor

## Descripción del problema a tratar con Mini Monitor
Para cumplir los objetivos del proyecto, se "rompió" el programa (recuerdo que cambié el orden de unas instrucciones pero ya no recuerdo cuáles) haciendo que la concurrencia de la impresión de los datos en pantalla fuera visible. Dicha concurrencia provocaba que algunos datos se mostraran a medias (por ejemplo, el tiempo de funcionamiento podría tener uno de sus campos vacíos) o que se perdiera la impresión. El problema se soluciona mediante una multiplex implementada con un mutex y un contador (inspirado en la resolución del problema de Santa Claus), permitiendo que todos los hilos impriman en pantalla antes de que la interfaz se refresque.

Sin embargo un problema surgió al añadir la funcionalidad de monitoreo de procesos y quedará sin resolver (por ahora): La inconsistencia entre el dato de número de procesos activos con los procesos activos mostrados, aunque es muy probable que éste último sea el causante, al tener una implementación completamente diferente e independiente al resto de funciones.

## Entorno
Mini Monitor fue programado y probado en una distro Xubuntu, por lo que debería ser funcional para cualquier sistema Linux basado en Debian, o en su defecto, Ubuntu.

Mini Monitor está programado en Python 2.7, por lo que es necesario tener Python 2.7 instalado para poder ejecutarlo. Está disponible para su descarga en: https://www.python.org/downloads/, o bien, con el comando:
`$ sudo apt-get install python2.7`

## Bibliotecas/paquetes necesarios

-asciimatics: Necesario para la interfaz gráfica. Se puede instalar mediante el comando:
`$ pip install asciimatics`
Puede ser necesario actualizar pip.

-psutil: Necesaria para la "interacción" con los procesos. Para Mini Monitor se utiliza la version 1.1.0, la cual puede ser obtenida en la direccion: https://pypi.python.org/pypi?:action=display&name=psutil#downloads. Al descargar el archivo, se descomprime y se instala con el comando:
`$ sudo python setup.py install`
