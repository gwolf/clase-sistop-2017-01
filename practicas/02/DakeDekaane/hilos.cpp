//g++ -std=c++0x -pthread hilos.cpp 

#include <iostream>
#include <thread>
#include <mutex>

std::mutex llave;
int i = 1;
int j = 1;

void HacerLlamadaNoMutex(const char* nombre) {
    std::cout << "Hola, soy " << nombre << ", el numero " << i << std::endl;
    i++;
}

void HacerLlamadaMutex(const char* nombre) {
      std::lock_guard<std::mutex> lock(llave);
      std::cout << "Hola, soy " << nombre << ", el número " << j << std::endl;
      j++;
}

int main() 
{
    std::cout << "\nEjecución sin mutex:" << std::endl;
    std::thread llamada1(HacerLlamadaNoMutex,"Hugo");
    std::thread llamada2(HacerLlamadaNoMutex,"Paco");
    std::thread llamada3(HacerLlamadaNoMutex,"Luis");
    std::thread llamada4(HacerLlamadaNoMutex,"Juan");
    std::thread llamada5(HacerLlamadaNoMutex,"Pedro");
    
    llamada1.join();
    llamada2.join();
    llamada3.join();
    llamada4.join();
    llamada5.join();

    std::cout << "\nEjecución con mutex:" << std::endl;
    std::thread llamada6(HacerLlamadaMutex,"Hugo");
    std::thread llamada7(HacerLlamadaMutex,"Paco");
    std::thread llamada8(HacerLlamadaMutex,"Luis");
    std::thread llamada9(HacerLlamadaMutex,"Juan");
    std::thread llamada10(HacerLlamadaMutex,"Pedro");
    
    llamada6.join();
    llamada7.join();
    llamada8.join();
    llamada9.join();
    llamada10.join();
    return 0;
}