/**********************************************************************
Funcion para conseguir numero de proceso
Copyright (C) 2016  Erik Sanabria esanabria136@gmail.com
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

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
                //i->set_PID();
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
