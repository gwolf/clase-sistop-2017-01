/**********************************************************************
Funcion principal del programa
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

#include "mainwindow.h"
#include "process.h"
#include "pidlib.h"
#include <QApplication>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char *argv[])
{  
    vector<string> test2;
    //vector<Process> proceso;
    size_t line{};

//    if(!PIDLIB::getProcessesInfo(&proceso, &test2, &line))
//    {
//        return 1;
//    }

    PIDLIB::parseSysInfo_CPP(&test2, &line);

    --line;

    vector<Process> proceso(line);

    cout << endl << line;

    /*for(auto y : test2)
    {
        cout << endl << y;
    }*/

    if(!PIDLIB::set_PIDs(&proceso, &test2, &line))
    {
        return 1;
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int ret{ a.exec() };

    test2.clear();
    test2.shrink_to_fit();
    proceso.clear();
    proceso.shrink_to_fit();
    return ret;
}
