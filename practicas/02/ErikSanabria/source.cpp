#include <iostream>
#include <vector>
#include <thread>

using std::vector;
using std::cout;
using std::endl;
using std::thread;

void funcionHilo(int n)
{
	cout << endl <<"Hola desde hilo "<< n << endl;

	return;
}

int main()
{
	cout <<"Trabajando en el hilo principal" << endl;

	const size_t max{ 10 };
	vector<thread> hilos;

	for(int i{ 0 }; i < max; ++i)
	{
		hilos.push_back(thread(funcionHilo, i));
	}

	cout << endl <<"Ya inicialize " << max <<" hilos desde main" << endl;

	for(int i{ 0 }; i < hilos.size(); ++i)
	{
		hilos.at(i).join();
	}

	return 0;
}

