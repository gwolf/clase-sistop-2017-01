#include <omp.h>
#include <iostream>
omp_lock_t lock;

int main(int argc, char **argv)
{
    using namespace std;
	omp_set_num_threads(4);
	
	#pragma omp parallel 
    {
        omp_set_lock(&lock);
        for(int n=0; n<10; ++n)
        cout<< n <<" Del hilo "<< omp_get_thread_num()<<" "<<endl;
        omp_unset_lock(&lock);
    }
	
	return 0;
}