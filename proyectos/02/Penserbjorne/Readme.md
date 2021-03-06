```
    ____                                     _______ __   
   / __ \__  ______ ___  ____ ___  __  __   / ____(_) /__
  / / / / / / / __ `__ \/ __ `__ \/ / / /  / /_  / / / _ \
 / /_/ / /_/ / / / / / / / / / / / /_/ /  / __/ / / /  __/
/_____/\__,_/_/ /_/ __/_/ /_/ /_/\__, /  /_/   /_/_/\___/
  / ___/__  _______/ /____  ____/____/                    
  \__ \/ / / / ___/ __/ _ \/ __ `__ \                     
 ___/ / /_/ (__  ) /_/  __/ / / / / /   by Penserbjorne
/____/\__, /____/\__/\___/_/ /_/ /_/                      
     /____/                                               

```

#Dummy File System

Micro sistema de archivos creado para la materia Sistemas Operativos. Facultad de Ingenieria, UNAM. Semestre 2017-1.

##Requerimientos
- C++11
- Distribucion Linux

##Compilar y Ejecutar

El archivo necesario se encuentra en la carpeta ``DummyFileSystem``.

- Compilar y ejecutar -> ``./build.sh``
- Compilar -> ``make -f makefile.mk``
- Ejecutar -> ``./dfs``

##Descripcion del sistema

El programa emula un micro sistema de archivos apoyado por un pequeño "interprete de comandos" (que realmente no es un interprete, pero al usuario se le presenta como tal).

Se requiere ingresar un usuario para poder operar sobre el sistema de ficheros.
Como interfaz se muestra un contador de lineas introducidas, el usuario actual y se espera la entrada de un comando. Dependiendo del comando instroducido se muestra una respuesta en pantalla.

Los comandos disponibles son:

- mabout   - Muestra informacion sobre FDS.

- mexit    - Sale del sistema.

- mhelp    - Despliega la ayuda general del sistema.

- mlsdisk  - (Sin parametro) Enlista todos los discos creados.

- mlsdisk  - (Con parametro) Enlista el contenido de un disco. Recibe un parametro.
    -Nombre del disco a mostrar.

    Ej: ``lsdisk disk``

- mkfile   - Permite crear un fichero en un disco. Recibe dos parametros.
    -Ruta del fichero: Iniciando por el disco, las rutas, se separan por "/" y el nombre del archivo con o sin extension.
    -Contenido del fichero: El texto que contendra el fichero.

      Ej: ``mkfile disk/dir/file.txt Content``

- mmkdir   - Permite crear un directorio en un disco. Recibe un parametro.
    -Ruta del directorio: Iniciando por el disco, las rutas, se separan por "/".

    Ej: ``mkdir disk/dir``

- mmkdisk  - Permite crear un disco para operar sobre el. Recibe dos parametros.
    -Nombre del disco: Nombre con el que se creara el fichero correspondiente.
                       No puede llevar espacios.
    -Tamaño del disco: Valor numerico en MB. No puede ser menor a 100 MB.

    Ej: ``mkdisk disk 100``

- musage   - Pequeño tutorial de como usar el sistema de ficheros.

##Uso del sistema

- Esta informacion muestra un uso basico del sistema de ficheros DFS. Se puede encontrar en el comando ``usage``.

- Primeramente hay que ingresar un nombre de usuario para la sesion.

- Crear un disco con el comando "mkdisk", enviando como parametros el nombre del disco y el tamaño.

    Ej: ``mkdisk disco1 100``

- Para enlistar los discos creados puede usar "lsdisk".

- Para crear una carpeta se usa el comando "mkdir", enviando como parametro la ruta de la carpeta iniciando por el disco, las rutas se separan por "/".

    Ej: ``mkdir disco1/directorio``

- Para mostrar el contenido de un disco puede usar "lsdisk" enviando como para metro el nombre del disco a listar.

    Ej: ``lsdisk disco1``

- Para crear un fichero se usa el comando "mkfile", enviando como parametro la ruta del fichero (son o sin extension) iniciando por el disco, las rutas se separan por "/" y como segundo parametro el contenido del fichero.

    Ej: ``mkdir disco1/directorio/fichero.txt Contenido del fichero``
