#ifndef CONSULTAR_INFO_H
#define CONSULTAR_INFO_H

#include <QProcess>

#include "string"
#include "struct_cpuinfo.h"

using namespace std;

class consultar_info
{

public:
    // Aqui definimos que propiedades de /proc/cpuinfo queremos leer
    string propiedades_cpuinfo[num_props_cpuinfo];

    consultar_info();

    // Nos permite enviar comandos al sistema
    QByteArray ejecutar_comando(string comando);

    // Nos permite procesar la informacion obtenida de leer /proc/cpuinfo
    vector<struct_CPUINFO> procesar_cpuinfo(QByteArray info);
};

#endif // CONSULTAR_INFO_H
