# Monitor de RAM para Linux exclusivamente.

## Requisitos para compilar.

* [Qt] (https://www.qt.io/download-open-source/). Qt requiere una cuenta pra activar el Qt Open Source en la instalacion. Es gratis.
* Instalacion con GCC. Asegurarse de seleccionar ``Desktop gcc 64-bit`` en la ventana de "Select Components" abriendo la pestaña de "Qt 5.7" También asegurarse de que "Tools" este seleccionado ya que este proporciona el editor qtcreator. Todos los demás componentes dejarlos como estan.
* GCC y G++ mayor o igual al 4.8.4
* ``sudo apt-get update && sudo apt-get install gcc g++ libgl1-mesa-dev -y``
* Este programa ha sido probado en Ubuntu 14.04 y Mint 18.

## Licenciamiento:

-> Este proyecto esta regido por los términos y condiciones del [GPL v3] (https://www.gnu.org/licenses/gpl-3.0.en.html)

## Participante:
* Erik Rodrigo Sanabria Betancourt

## Problema que se busca resolver:
* Se busca poder visualizar los programas en ejecucion, sus PIDs; el usuario que los esta ejecutando, el porcentaje de RAM que esta utilizando y el directorio del ejecutable mencionado.
* Se busca mostrar dicha informacion en una tabla con GUI para el usuario.

## Lógicas de operación:
* Primero ejecuta el programa ``ps aux > procesos2.txt`` mediante ``system()`` para conseguir informacion de los procesos en ejecucion y guardarlos en un archivo de texto.
* Después el programa lee este archivo de texto y lo guarda en un ``vector<string>`` de C++ por renglones. Cada renglon del archivo es un elemento del vector.
* Posteriormente varias funciones leen el ``vector<string>`` y extraen la informacion del PID, usuario, porcentaje de RAM y la ubicacion del ejecutable y la guardan en un ``vector<Process>``.
* Todos estos pasos se realizan en un hilo diferente de la GUI.
* El hilo principal se encarga de la GUI.
* Cada que se finaliza la obtencion de la informacion el hilo debe de actualizar los resultados en la GUI y volver a realizar los mismos pasos. Esto se ejecuta mientras el programa este en ejecucion.

## Procedimiento para abrir proyecto en Qt:
* Primero abrir Qt.
* Segundo, seleccionar "Open Project".
* Navegar a ubicacion del repositorio en el disco. Posteriormente navegar a ``.../clase-sistop-2017-01/proyectos/Proyecto_Erik_Sebastian/MonitorRAM``.
* En esta carpeta se encuentra un archivo con nombre: ``MonitorRAM.pro`` seleccionarlo y dar click en ``Open``.
* El proyecto ya esta abierto.
* Para compilar presionar el martillo en la esquina inferior izquierda de Qt ó usar ``Ctrl + B``.
* Para ejecutar el programa dar click en la flecha verde que no tiene un bug ó usar ``Ctrl + R``.
