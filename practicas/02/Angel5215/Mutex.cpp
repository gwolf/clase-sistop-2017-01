
// Vazquez Alvarez Angel Eduardo

#include <iostream>	//	std::cout
#include <thread>	//	std::thread
#include <mutex>	//	std::mutex

//	Mutex para sección crítica
std::mutex m; 

void printNumbersWithoutMutex(int last, int thread_id)
{
	std::cout << "Thread: " << thread_id << std::endl;
	for(int i = 0; i <= last; i++)
	{
		std::cout << i << " "; 
	}	
	std::cout << std::endl;
}

void printNumbersWithMutex(int last, int thread_id)
{
	m.lock();

	std::cout << "Thread: " << thread_id << std::endl;
	for(int i = 0; i <= last; i++)
	{
		std::cout << i << " "; 
	}

	std::cout << std::endl;
	
	m.unlock();
}

int main()
{

	// Ejecución del código sin mutex.
	std::thread thread1 (printNumbersWithoutMutex, 10, 1);
	std::thread thread2 (printNumbersWithoutMutex, 20, 2);

	thread1.join();
	thread2.join();

	//	Ejecución del código con mutex.
	std::thread thread3 (printNumbersWithMutex, 10, 3);
	std::thread thread4 (printNumbersWithMutex, 20, 4);
	thread3.join();
	thread4.join();

	return 0;
}