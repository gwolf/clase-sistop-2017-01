# Monitor de RAM para Linux exclusivamente.

## Requisitos para compilar.

* [Qt] (https://www.qt.io/download-open-source/)
* Instalacion con GCC y Qt Charts
* Requisitos para compilar:

* ``sudo apt-get update && sudo apt-get install gcc g++ libgl1-mesa-dev -y``

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
