#include "struct_meminfo.h"

// setter general para la estructura basado en indices
void struct_MEMINFO::asignarValor(int index, string valor){
    switch (index) {
    case 0:
        MemTotal = valor;
        break;
    case 1:
        MemFree = valor;
        break;
    case 2:
        Cached = valor;
        break;
    case 3:
        SwapCached = valor;
        break;
    case 4:
        Active = valor;
        break;
    case 5:
        Inactive = valor;
        break;
    case 6:
        Active_anon = valor;
        break;
    case 7:
        Inactive_anon = valor;
        break;
    case 8:
        Active_file = valor;
        break;
    case 9:
        Inactive_file = valor;
        break;
    case 10:
        SwapTotal = valor;
        break;
    case 11:
        SwapFree = valor;
        break;
    case 12:
        Dirty = valor;
        break;
    case 13:
        Writeback = valor;
        break;
    case 14:
        Mapped = valor;
        break;
    case 15:
        Shmem = valor;
        break;
    case 16:
        KernelStack = valor;
        break;
    case 17:
        WritebackTmp = valor;
        break;
    case 18:
        CommitLimit = valor;
        break;
    case 19:
        Committed_AS = valor;
        break;
    case 20:
        VmallocTotal = valor;
        break;
    case 21:
        VmallocUsed = valor;
        break;
    case 22:
        VmallocChunk = valor;
        break;
    default:
        break;
    }
}

// getter general para la estructura basado en indices
string struct_MEMINFO::obtenerValor(int index){
    switch (index) {
    case 0:
        return MemTotal;
        break;
    case 1:
        return MemFree;
        break;
    case 2:
        return Cached;
        break;
    case 3:
        return SwapCached;
        break;
    case 4:
        return Active;
        break;
    case 5:
        return Inactive;
        break;
    case 6:
        return Active_anon;
        break;
    case 7:
        return Inactive_anon;
        break;
    case 8:
        return Active_file;
        break;
    case 9:
        return Inactive_file;
        break;
    case 10:
        return SwapTotal;
        break;
    case 11:
        return SwapFree;
        break;
    case 12:
        return Dirty;
        break;
    case 13:
        return Writeback;
        break;
    case 14:
        return Mapped;
        break;
    case 15:
        return Shmem;
        break;
    case 16:
        return KernelStack;
        break;
    case 17:
        return WritebackTmp;
        break;
    case 18:
        return CommitLimit;
        break;
    case 19:
        return Committed_AS;
        break;
    case 20:
        return VmallocTotal;
        break;
    case 21:
        return VmallocUsed;
        break;
    case 22:
        return VmallocChunk;
        break;
    default:
        return "Valor sin definidir";
        break;
    }
}

string struct_MEMINFO::toStdString(){
    string meminfo;
    meminfo.append(MemTotal);
    meminfo.append("\n");
    meminfo.append(MemFree);
    meminfo.append("\n");
    meminfo.append(Cached);
    meminfo.append("\n");
    meminfo.append(SwapCached);
    meminfo.append("\n");
    meminfo.append(Active);
    meminfo.append("\n");
    meminfo.append(Inactive);
    meminfo.append("\n");
    meminfo.append(Active_anon);
    meminfo.append("\n");
    meminfo.append(Inactive_anon);
    meminfo.append("\n");
    meminfo.append(Active_file);
    meminfo.append("\n");
    meminfo.append(Inactive_file);
    meminfo.append("\n");
    meminfo.append(SwapTotal);
    meminfo.append("\n");
    meminfo.append(SwapFree);
    meminfo.append("\n");
    meminfo.append(Dirty);
    meminfo.append("\n");
    meminfo.append(Writeback);
    meminfo.append("\n");
    meminfo.append(Mapped);
    meminfo.append("\n");
    meminfo.append(Shmem);
    meminfo.append("\n");
    meminfo.append(KernelStack);
    meminfo.append("\n");
    meminfo.append(WritebackTmp);
    meminfo.append("\n");
    meminfo.append(CommitLimit);
    meminfo.append("\n");
    meminfo.append(Committed_AS);
    meminfo.append("\n");
    meminfo.append(VmallocTotal);
    meminfo.append("\n");
    meminfo.append(VmallocUsed);
    meminfo.append("\n");
    meminfo.append(VmallocChunk);
    return meminfo;
}
