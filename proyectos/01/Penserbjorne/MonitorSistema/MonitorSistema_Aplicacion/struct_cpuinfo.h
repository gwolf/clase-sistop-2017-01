#ifndef STRUCT_CPUINFO_H
#define STRUCT_CPUINFO_H

#include "string"

#define num_props_cpuinfo 12

using namespace std;

// Estructura que simula "cpuinfo"
struct struct_CPUINFO{
    string processor;
    string vendor_id;
    string cpu_family;
    string model;
    string model_name;
    string stepping;
    string cpu_MHz;
    string cache_size;
    string physical_id;
    string siblings;
    string core_id;
    string cpu_cores;

    void asignarValor(int index, string valor);
    string obtenerValor(int index);
};

#endif // STRUCT_CPUINFO_H
