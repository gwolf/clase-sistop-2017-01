#ifndef PROCESS_H
#define PROCESS_H

#include "colib.h"

class Process
{
public:
    Process();

    ~Process();

    Process(int m_P, int m_C, float m_MP);

    FORCEINLINE void set_PID(int P);

    bool get_RAM();

    bool set_Color(int val);

private:
    int m_PID;
    int m_Color;
    float m_MemPerc;
};

#endif // PROCESS_H
