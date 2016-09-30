#include <QProcess>

#include "string"
#include "consultar_info.h"

#define STAT_PROPS 7

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

    propiedades_meminfo[0] = "MemTotal";
    propiedades_meminfo[1] = "MemFree";
    propiedades_meminfo[2] = "Cached";
    propiedades_meminfo[3] = "SwapCached";
    propiedades_meminfo[4] = "Active";
    propiedades_meminfo[5] = "Inactive";
    propiedades_meminfo[6] = "Active(anon)";
    propiedades_meminfo[7] = "Inactive(anon)";
    propiedades_meminfo[8] = "Active(file)";
    propiedades_meminfo[9] = "Inactive(file)";
    propiedades_meminfo[10] = "SwapTotal";
    propiedades_meminfo[11] = "SwapFree";
    propiedades_meminfo[12] = "Dirty";
    propiedades_meminfo[13] = "Writeback";
    propiedades_meminfo[14] = "Mapped";
    propiedades_meminfo[15] = "Shmem";
    propiedades_meminfo[16] = "KernelStack";
    propiedades_meminfo[17] = "WritebackTmp";
    propiedades_meminfo[18] = "CommitLimit";
    propiedades_meminfo[19] = "Committed_AS";
    propiedades_meminfo[20] = "VmallocTotal";
    propiedades_meminfo[21] = "VmallocUsed";
    propiedades_meminfo[22] = "VmallocChunk";

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
    QList<QByteArray> propiedades = info.split('\n');   // Separamos la informacion por lineas, una linea es una propiedad

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

// Nos permite procesar la informacion obtenida de leer /proc/meminfo
struct_MEMINFO consultar_info::procesar_meminfo(QByteArray info){
    int contador;
    struct_MEMINFO meminfo;         // Entidad individual para almacenar temporalmente los datos de la memoria
    QList<QByteArray> propiedades = info.split('\n');   // Separamos la informacion por lineas, una linea es una propiedad

    contador = 0;
    // Para cada propiedad que tenemos disponibles, verificamos si es una propiedad de las que
    // queremos consultar
    foreach( const QByteArray &propiedad, propiedades)
    {
        // verificamos si la propiedad actual esta en la lista de propiedades que queremos
        if(propiedad.toStdString().find(propiedades_meminfo[contador]) != string::npos){
            // Aqui asignamos el valor obtenido a una estructura que simula "meminfo"
            meminfo.asignarValor(contador,propiedad.toStdString());
            contador++;
            if(contador >= num_props_meminfo){
                return meminfo;   // retornamos toda la info deseada
            }
        }
    }
    return meminfo;   // retornamos toda la info deseada
}

// Nos permite procesar la informacion obtenida de leer /proc/stat
string consultar_info::procesar_stat(QByteArray info){
    int contador;
    string stat;         // Entidad individual para almacenar temporalmente los datos del stat
    QList<QByteArray> propiedades = info.split('\n');   // Separamos la informacion por lineas, una linea es una propiedad

    stat.append("cpu\tuser\tnice\tsystem\tidle\tiowait\tirq\n\n");
    contador = 0;
    // Para cada propiedad que tenemos disponibles, verificamos si es una propiedad de las que
    // queremos consultar
    foreach( const QByteArray &propiedad, propiedades)
    {
        // verificamos si la propiedad actual esta en la lista de propiedades que queremos
        if(propiedad.toStdString().find("cpu") != string::npos){
            QList<QByteArray> valor_propiedad = propiedad.split(' ');
            for(int i = 0; i < STAT_PROPS; i++){
                stat.append(valor_propiedad[i].toStdString());
                stat.append("\t");
            }
            stat.append("\n");
        }
    }
    return stat;   // retornamos toda la info deseada
}
