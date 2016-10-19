#include "fcfs.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;
    
fcfs::fcfs(vector <float>* data)
{   
    construct(data);
   
}


void fcfs::construct(vector <float> *data)
{   
    for (int i=0; i< data->size();i=i+2)
    {
        Procs.push_back(proceso((*data)[i],(*data)[i+1]));   
    }
    
}


void fcfs::fifo()
{
        int i=0;
        int temporal=0;
        while(i<Procs.size())
        {
            if (Tiempo<Procs[i].TiempoReq+temporal && Procs[i].Termino==false)
            {
                this->Tiempo+=1;
            }
            else
            {
                Procs[i].TiempoResp = this->Tiempo - Procs[i].TiempoLlega;
                Procs[i].TiempoEsp = Procs[i].TiempoResp - Procs[i].TiempoReq;
                if(Procs[i].TiempoLlega<1)
                {
                    Procs[i].PropPenal =1;
                }
                else
                {
                    Procs[i].PropPenal =Procs[i].TiempoResp / Procs[i].TiempoReq;
                }
                Procs[i].PropResp = 1/Procs[i].PropPenal ;
                Procs[i].Termino=true;
                temporal=Tiempo;
                i++;
            }
    
        }
        

    Promedios();
}

void fcfs::Promedios()
{   
    float totalProc=Procs.size();
    int conta=0;
    float Promedios[3]={0,0,0};
    string palabras[5]={"A      ","B      ","C      ","D      ","E      "};
    for (conta=0;conta<Procs.size();conta++)
    {
        Promedios[0]+=Procs[conta].TiempoResp;
        Promedios[1]+=Procs[conta].TiempoEsp;
        Promedios[2]+=Procs[conta].PropPenal;

    }
    Promedios[0]/=totalProc;
    Promedios[1]/=totalProc;
    Promedios[2]/=totalProc;

    cout<<"Proceso\t   Ini\t   Treq\t     T\t     E\t     P"<<endl;
    for(conta=0;conta<totalProc;conta++)
    {
        cout<<palabras[conta]<<"\t     "<<Procs[conta].TiempoLlega<<"\t     "<<Procs[conta].TiempoReq<<"\t     "<<Procs[conta].TiempoResp<<"\t     "<<Procs[conta].TiempoEsp<<"\t     "<<Procs[conta].PropPenal<<endl;
    }
    cout<<"Promedio\t       \t    "<<Promedios[0]<<"\t    "<<Promedios[1]<<"\t    "<<Promedios[2]<<endl;
}
