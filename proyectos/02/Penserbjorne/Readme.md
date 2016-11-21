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

- Compilar y ejecutar -> ``./build.sh``
- Compilar -> ``make -f makefile.mk``
- Ejecutar -> ``./dfs``

##Descripcion del sistema

El programa emula un micro sistema de archivos apoyado por un pequeño "interprete de comandos" (que realmente no es un interprete, pero al usuario se le presenta como tal).

Se requiere ingresar un usuario para poder operar sobre el sistema de ficheros.
Como interfaz se muestra un contador de lineas introducidas, el usuario actual y se espera la entrada de un comando. Dependiendo del comando instroducido se muestra una respuesta en pantalla.

Los comandos disponibles son:
- exit - Sale del sistema.
- help - Comando que despliega la ayuda general del sistema.
- usage - Pequeño tutorial de como usar el sistema de ficheros.
