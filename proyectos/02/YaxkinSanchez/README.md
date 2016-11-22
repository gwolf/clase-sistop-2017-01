#FAULT

## Versión
1.0

## Autor
David Yaxkin Sánchez Neri

## Descripción
FAULT (File Allocation Using List of Text) es un sistema de archivos que hace uso de una lista de texto que contiene los nombres de los archivos existentes en el sistema. FAULT soporta las siguientes operaciones con archivos:
* Lectura de archivos
* Creación de archivos
* Eliminación de archivos
* Escritura en un archivo
* Adición a un archivo

Límites:
* Longitud máxima para nombre de archivo: 12 incluyendo extensión
* Límite de tamaño de archivos: Ninguno
* Límite de tamaño total: Ninguno
* No soporta el uso de directorios.

## Modo de operación
El sistema está conformado por un archivo zip, que hará de dispositivo de almacenamiento para nuestros archivos.

Al cargar el sistema (ejecutando la shell), se generará un directorio temporal, el cual hará de buffer para las operaciones de lectura y escritura, y en dicho directorio se almacenará un archivo de texto que contiene la lista de asignación, la cual contiene los nombres de los archivos que están contenidos en nuestro sistema. 

Al crear un archivo nuevo, se creara en el buffer y se generará una entrada en la lista de asignación, para guardarse inmediatamente en el dispositivo.

Al hacer una petición para una operación de lectura o escritura, la lista de asignación será consultada para así evitar accesos innecesarios al dispositivo. Si el archivo se encuentra en el sistema, éste se cargara en el buffer para su manipulación.

Al terminar cualquier operación de escritura, el archivo se guardará inmediatamente en el dispositivo.

Al eliminar un archivo, simplemente se eliminará su entrada de la lista de asignación, y se guardará en el dispositivo de manera inmediata.

Al salir del sistema (cierre de shell), un "recolector de basura" eliminará aquellos archivos que no contengan una entrada en la Lista de Asignación, y se eliminará nuestro directorio temporal.


## Entorno
FAULT fue programado y probado en una distro Xubuntu, por lo que debería ser funcional para cualquier sistema Linux basado en Debian, o en su defecto, Ubuntu.

FAULT está programado en Bash, por lo que será necesario tener esta shell instalada. Dependiendo del lugar donde se encuentre instalada, puede que sea necesario cambiar el shabang en el programa para asegurar su ejecución.

## Bibliotecas/paquetes necesarios
FAULT hace uso de las siguientes utilerías: zip, unzip, sed y grep. Por si se da el caso en que tengan que ser instaladas.

## Ejecución
Una vez teniendo todo lo necesario y estando en una shell Bash, se introduce el siguiente comando para ingresar a la shell que interactúa con el sistema de archivos:

`./fault.sh`

Nota: puede ser necesario dar permisos de ejecucion al archivo.

## Comandos
Del comando *help*:
* list:	Lista el contenido del directorio
* create: Crea un archivo nuevo. Sintáxis: create <archivo>
* read:	Lee un archivo. Sintáxis: read <archivo>
* write: Escribe <cadena> en <archivo>.	Nota: Este comando realiza sobreescritura. Sintáxis: write <archivo>
* append: Agrega <cadena> en <archivo>.	Sintáxis: append <archivo>
* del: Elimina un archivo. Sintáxis: del <archivo>
* help:	Muestra esta ayuda
* exit: Salir de la aplicación

