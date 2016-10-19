#ifndef FCFS
#define FCFS
#include <queue>
#include <vector>
using namespace std;

class fcfs
{
    private: 
        struct proceso
        {
            float TiempoLlega;
            float TiempoReq;
            float TiempoResp;
            float TiempoEsp;
            float PropPenal;
            float PropResp;
            bool Termino=false;
            proceso(int start,int t)
            {
                TiempoLlega=start;
                TiempoReq= t;
            }
};
      
        //queue<proceso> presentes;
        vector <proceso> Procs;
        int Tiempo=0;
        //int quantum;


    public:
        fcfs (vector <float>*);
        void fifo();
        void construct(vector <float>*);
        void Promedios();
};

#endif