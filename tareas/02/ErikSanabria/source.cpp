/****************************************
ERIK RODRIGO SANABRIA BETANCOURT
Implementacion del problema Matt Welsh 2007 en c++
Hay un cruce de caminos sin señalamiento vial
El cruce se representa mediante las siguientes variables:

       A1 A2
    B0 B1 B2 B3
    C0 C1 C2 C3
       D1 D2

El transito puede llegar desde cualquier lugar (C0, D2, B3, A1) y en cualquier momento. ¿Como aseguramos que no haya choques?
B1, B2, C1 y C2 son el crucero y C0, D2, B3y A1 son entradas al crucero.
B0, D1, C3 Y A2 son salidas del crucero.
*******************************************/

#include <iostream>
#include <thread>
#include <atomic>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <ctime>

using std::cout;
using std::endl;
using std::thread;
using std::atomic;
using std::vector;

atomic<bool> A1{ false };   //false => representa que no hay vehiculo
atomic<bool> A2{ false };   //true => representa que hay vehiculo
atomic<bool> B0{ false };
atomic<bool> B1{ false };
atomic<bool> B2{ false };
atomic<bool> B3{ false };
atomic<bool> C0{ false };
atomic<bool> C1{ false };
atomic<bool> C2{ false };
atomic<bool> C3{ false };
atomic<bool> D1{ false };
atomic<bool> D2{ false };


void vehiculo(size_t count)         //funcion que simula un vehiculo, solo pueden ir defrente
{
    size_t num{};

    srand(static_cast<unsigned int>(time(0)));      //aleatoriamente decidir por donde va a entrar el vehiculo

    for(int i{}; i < 100; ++i)
    {
        num = rand();                               //obteniendo numero aleatorio

        size_t n{ (num % 4) +1 };                   //consiguiendo numero entre 1 y 4

        switch(n)
        {
            case 1:
            //entrar por C0
            cout << endl << "Hilo " << count << " entrando por C0...";

            if(!C0)
            {
                C0 = true;

                if(!C1)
                {
                    cout << endl <<"Hilo " << count << " avanzando a C1...";
                    C0 = false;
                    C1 = true;

                    if(!C2)
                    {
                        cout << endl <<"Hilo " << count << " avanzando a C2...";
                        C1 = false;
                        C2 = true;

                        if(!C3)
                        {
                            cout << endl <<"Hilo " << count << " avanzando a C3...";
                            C2 = false;
                            C3 = true;
                            sleep(0.5);
                            C3 = false;
                            cout << endl <<"Hilo " << count << " saliendo de C3...";

                            break;
                        }
                    }
                }
            }
            break;
            case 2:
            //entrar por D2
            cout << endl << "Hilo " << count <<" entrando por D2...";

            if(!D2)
            {
                D2 = true;

                if(!C2)
                {
                    cout << endl <<"Hilo " << count << " avanzando a C2...";
                    D2 = false;
                    C2 = true;

                    if(!B2)
                    {
                        cout << endl <<"Hilo " << count << " avanzando a B2...";
                        C2 = false;
                        B2 = true;

                        if(!A2)
                        {
                            cout << endl <<"Hilo " << count << " avanzando a A2...";
                            B2 = false;
                            A2 = true;
                            sleep(0.5);
                            A2 = false;
                            cout << endl <<"Hilo " << count <<" saliendo de A2...";

                            break;
                        }
                    }
                }
            }

            break;
            case 3:
            //entrar por B3

            cout << endl << "Hilo " << count <<" entrando por B3...";

            if(!B3)
            {
                B3 = true;

                if(!B2)
                {
                    cout << endl <<"Hilo " << count << " avanzando a B2...";
                    B3 = false;
                    B2 = true;

                    if(!B1)
                    {
                        cout << endl <<"Hilo " << count << " avanzando a B1...";
                        B2 = false;
                        B1 = true;

                        if(!B0)
                        {
                            cout << endl <<"Hilo " << count << " avanzando a B0...";
                            B1 = false;
                            B0 = true;
                            sleep(0.5);
                            B0 = false;
                            cout << endl <<"Hilo " << count <<" saliendo de B0...";

                            break;
                        }
                    }
                }
            }
            break;
            case 4:
            //entrar por A1

            cout << endl << "Hilo " << count <<" entrando por A1...";

            if(!A1)
            {
                A1 = true;

                if(!B1)
                {
                    cout << endl <<"Hilo " << count << " avanzando a B1...";
                    A1 = false;
                    B1 = true;

                    if(!C1)
                    {
                        cout << endl <<"Hilo " << count <<" avanzando a C1...";
                        B1 = false;
                        C1 = true;

                        if(!D1)
                        {
                            cout << endl << "Hilo " << count <<" avanzando a D1...";
                            C1 = false;
                            D1 = true;
                            sleep(0.5);
                            D1 = false;

                            cout << endl <<"Hilo " << count <<" saliendo de D1...";

                            break;
                        }
                    }
                }
            }
            break;
            default:
            continue;
        }
    }
    
    return;
}

int main()
{
    vector<thread> hilos;

    for(int g{} ; g < 10; ++g)		//creando 10 hilos
    {
        hilos.push_back(thread(vehiculo, g));
    }
    
    for(auto &i : hilos)		//uniendo los 10 hilos a main()
    {
        i.join();
    }

    cout << endl;

    return 0;
}
