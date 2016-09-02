#ifndef PIDLIB_H
#define PIDLIB_H

#include "process.h"
#include <unistd.h>
#include <vector>

using std::vector;

namespace PIDLIB
{
    bool get_PID(vector<Process> *pvP)
    {
        if(execve(ps))
        {
            for(auto i : *pvP)
            {
                i->set_PID();
            }

            return true;
        }
        else
        {
            return false;
        }
    }
}

#endif // PIDLIB_H
