#ifndef STRUCT_MEMINFO_H
#define STRUCT_MEMINFO_H

#include "string"

#define num_props_meminfo 23

using namespace std;

// Estructura que simula "meminfo"
struct struct_MEMINFO{
    string MemTotal;
    string MemFree;

    string Cached;
    string SwapCached;

    string Active;
    string Inactive;
    string Active_anon;
    string Inactive_anon;
    string Active_file;
    string Inactive_file;

    string SwapTotal;
    string SwapFree;

    string Dirty;
    string Writeback;

    string Mapped;
    string Shmem;

    string KernelStack;

    string WritebackTmp;
    string CommitLimit;
    string Committed_AS;

    string VmallocTotal;
    string VmallocUsed;
    string VmallocChunk;


    void asignarValor(int index, string valor);
    string obtenerValor(int index);
    string toStdString();
};


#endif // STRUCT_MEMINFO_H
