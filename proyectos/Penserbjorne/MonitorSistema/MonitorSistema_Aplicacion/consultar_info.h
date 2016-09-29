#ifndef CONSULTAR_INFO_H
#define CONSULTAR_INFO_H

#include <QProcess>

#include "string"
#include "struct_cpuinfo.h"

using namespace std;

class consultar_info
{

public:
    string propiedades_cpuinfo[num_props_cpuinfo];

    consultar_info();
    QByteArray ejecutar_comando(string comando);
    vector<struct_CPUINFO> consultar_cpuinfo(QByteArray info);
};

#endif // CONSULTAR_INFO_H
