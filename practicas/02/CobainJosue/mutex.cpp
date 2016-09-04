//Quiñones Rivera Josué Emanuel

#include<iostream>
#include<mutex>
#include<thread>

using namespace std;

mutex Mutex;

void usoDeMutex(int a, int no_hilo){

	Mutex.lock();

	cout << "Imprimiendo desde el hilo " << no_hilo << endl;
	for(int i=0; i<a; i++){
		cout << i << " ";
	}
	cout << endl;

	Mutex.unlock();

}

int main(){

	thread hilo1(usoDeMutex, 5, 1);
	thread hilo2(usoDeMutex, 3, 2);
	thread hilo3(usoDeMutex, 7, 3);
	thread hilo4(usoDeMutex, 10, 4);

	hilo1.join();
	hilo2.join();
	hilo3.join();
	hilo4.join();

	return 0;
}