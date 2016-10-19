#ifndef ROUNDR
#define ROUNDR
#include <deque>
#include <vector>
using namespace std;

class roundR
{
    private: 
        struct proceso
        {   
            float TiempoLlega;
            float TiempoReq;
            float TiempoResp=0;
            float TiempoEsp=0;
            float PropPenal=0;
            float PropResp=0;
            int TiempoEx=0;
            bool added=false;
            proceso(int start,int t)
            {
                TiempoLlega=start;
                TiempoReq= t;
            }
};
        deque <proceso> presentes;
        vector <proceso> Procs;
        vector <proceso> ended;
        int Tiempo=0;
        int quantum=1;


    public:
        roundR (vector <float>*);
        void round();
        void construct(vector <float>*);
        void Promedios();
};

#endif