# Monitor de Sistema

## Licencia:

* GPL v3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

## Autor:
* Paul Sebastian Aguilar Enriquez a.k.a Penserbjorne

## Entorno de desarrollo.

* El proyecto fue desarrollado con [Qt Creator 4.1.0] (https://www.qt.io/download-open-source/).
* Qt 5.7-0
* GCC y G++ 4.9.1
* Lubuntu 14.04 para arquitectura x64

## Funcion:
* Mostrar informacion basica del sistema: Sistema Operativo (/proc/version_signature), versiond del Kernel Linux (/proc/version), CPU's (/proc/cpuinfo).
* Monitoreo en tiempo real de: CPU's (/proc/stat), Memoria (/proc/meminfo), Disco (/proc/diskstats).

## Procedimiento para abrir proyecto en Qt Creator:
(Instrucciones basadas en las de [erlogerik] (https://github.com/erlogerik/clase-sistop-2017-01/tree/proyecto/proyectos/Proyecto_Erik_Sebastian))

* Abrir Qt Creator.
* Seleccionar "Open Project".
* Navegar a ubicacion del proyecto. Posteriormente navegar a ``.../clase-sistop-2017-01/proyectos/Penserbjorne/MonitorSistema/MonitorSistema_Aplicacion``.
* En esta carpeta se encuentra un archivo con nombre: ``MonitorSistema.pro`` seleccionarlo y dar click en ``Open``.
* Si aparece un mensaje de los settings del proyecto, que no se han generado dar click en "No". El proyecto ya esta abierto.
* Para compilar presionar el martillo en la esquina inferior izquierda ó usar ``Ctrl + B``.
* Si marca este error al compilar ``cannot find -lGL`` asegurarse de que ``libgl1-mesa-dev`` ó ``mesa-libGL-devel`` este instalado.
* Para ejecutar el programa dar click en la flecha verde que no tiene un bug ó usar ``Ctrl + R``.
