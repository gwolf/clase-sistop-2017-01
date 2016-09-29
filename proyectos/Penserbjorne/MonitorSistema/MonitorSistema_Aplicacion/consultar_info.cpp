#include <QProcess>

#include "string"
#include "consultar_info.h"
#include "struct_cpuinfo.h"

consultar_info::consultar_info()
{
    // Aqui definimos que propiedades de /proc/cpuinfo queremos leer
    propiedades_cpuinfo[0] = "processor";
    propiedades_cpuinfo[1] = "vendor_id";
    propiedades_cpuinfo[2] = "cpu family";
    propiedades_cpuinfo[3] = "model";
    propiedades_cpuinfo[4] = "model name";
    propiedades_cpuinfo[5] = "stepping";
    propiedades_cpuinfo[6] = "cpu MHz";
    propiedades_cpuinfo[7] = "cache size";
    propiedades_cpuinfo[8] = "physical id";
    propiedades_cpuinfo[9] = "siblings";
    propiedades_cpuinfo[10] = "core id";
    propiedades_cpuinfo[11] = "cpu cores";

}

// Nos permite enviar comandos al sistema
QByteArray consultar_info::ejecutar_comando(string comando){
    // creamos un proceso para enviar comandos al sistema, simplemente
    // regresamos la salida en un arreglo de bytes
    QString qcommand = QString::fromStdString(comando);
    QProcess *myProcess = new QProcess();
    QByteArray processOutput;
    myProcess->start(qcommand);
    myProcess->waitForStarted();
    myProcess->waitForBytesWritten();
    myProcess->waitForFinished();
    myProcess->waitForReadyRead();
    processOutput = myProcess->readAll();
    return processOutput;
}

// Nos permite procesar la informacion obtenida de leer /proc/cpuinfo
vector<struct_CPUINFO> consultar_info::procesar_cpuinfo(QByteArray info){
    int contador;
    struct_CPUINFO cpuinfo;         // Entidad individual para almacenar temporalmente los datos de un solo core
    vector<struct_CPUINFO> cores;   // Aqui almacenaremos todos los datos de los cores que hay
    QList<QByteArray> propiedades = info.split('\n');   // Separamos la informacion por lineas, una linea es una propieda

    contador = 0;
    // Para cada propiedad que tenemos disponibles, verificamos si es una propiedad de las que
    // queremos consultar
    foreach( const QByteArray &propiedad, propiedades)
    {
        // verificamos si la propiedad actual esta en la lista de propiedades que queremos
        if(propiedad.toStdString().find(propiedades_cpuinfo[contador]) != string::npos){
            // En caso de que si este, obtenemos el valor de la propiedad
            QList<QByteArray> valor_propiedad = propiedad.split(':');

            // Aqui asignamos el valor obtenido a una estructura que simula "cpuinfo"
            cpuinfo.asignarValor(contador,valor_propiedad[1].toStdString());
            contador++;
            // Una vez obtenidas todas las propiedades deseadas pasamos a guardar la entidad cpuinfo
            // en el vector que almacena toda la info de los cores
            if(contador >= num_props_cpuinfo){
                cores.push_back(cpuinfo);
                contador = 0;
            }
        }
    }
    return cores;   // retornamos toda la info deseada
}
