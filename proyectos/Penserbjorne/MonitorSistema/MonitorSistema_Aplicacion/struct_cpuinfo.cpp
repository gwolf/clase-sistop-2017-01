#include "struct_cpuinfo.h"

void struct_CPUINFO::asignarValor(int index, string valor){
    switch (index) {
    case 0:
       processor = valor;
        break;
    case 1:
       vendor_id = valor;
        break;
    case 2:
       cpu_family = valor;
        break;
    case 3:
       model = valor;
        break;
    case 4:
       model_name = valor;
        break;
    case 5:
       stepping = valor;
        break;
    case 6:
       cpu_MHz = valor;
        break;
    case 7:
       cache_size = valor;
        break;
    case 8:
       physical_id = valor;
        break;
    case 9:
       siblings = valor;
        break;
    case 10:
       core_id = valor;
        break;
    case 11:
       cpu_cores = valor;
        break;
    default:
        break;
    }
}

string struct_CPUINFO::obtenerValor(int index){
    switch (index) {
    case 0:
       return processor;
        break;
    case 1:
       return vendor_id;
        break;
    case 2:
       return cpu_family;
        break;
    case 3:
       return model;
        break;
    case 4:
       return model_name;
        break;
    case 5:
       return stepping;
        break;
    case 6:
       return cpu_MHz;
        break;
    case 7:
       return cache_size;
        break;
    case 8:
       return physical_id;
        break;
    case 9:
       return siblings;
        break;
    case 10:
       return core_id;
        break;
    case 11:
       return cpu_cores;
        break;
    default:
        return "Valor sin definidir";
        break;
    }
}
