/*Clase encargada de algoritmo Round Robin
Se presta para posibles minimización a distitnas funciones*/

#include <vector>//para la utilizacion de vectores
#include <iostream>//para la salida a consola
#include <string>//uso de strings superfluo
#include <algorithm>//para el ordenamiento de los vectores
#include "roundr.h"//header donde se decalra la clase
using namespace std;//Se utiliza para sencillez en la sintaxis y omitir el std::
/*Metodo constructor de la clase REcibe un a putador de vector para facilitar el paso 
de datos desde el main*/
roundR::roundR(vector <float>* data)
{   
    construct(data);
   
}


/*Funcion que crea las estructuras necesarias y las mete en un vector para su utilizacion
recibe apuntador a vector para facilitar paso de datos desde main*/
void roundR::construct(vector <float> *data)
{   
    
    for (int conta=0; conta< data->size();conta+=2)
    {
        Procs.push_back(proceso((*data)[conta],(*data)[conta+1])); 
        
    }
}

/*Método principal de la clase, esta realiza el algoritmo de planificación (simulado)
y no recibe parametros. pues oslo utiliza los atributos del objeto mismo*/
void roundR::round()
{       
        int auxcont=1;//contador auxiliar para no entrar en el bucle siempre
        int conta=0;//contador para iterar sobre un vector
        int counter=0;//contador que representa el avanze del proceso segun el quantum
        int limit=Procs.size();//Limite para no llamar a size() tantas veces
        proceso *use=0;//apuntador a estructura para poder recibir y encolar de nuevo
//--------------------------------------------Aquí empieza---------------------------------------

        presentes.push_back(Procs[0]);
        while(ended.size()<Procs.size())//mientras la cola de terminados no sea igual de grande que al de procesos
        {       
            Tiempo= Tiempo+1;//el tiempo corre
            presentes[0].TiempoEx=presentes[0].TiempoEx+1;//el proceso se ejecuta
            counter= counter+1;

            if(auxcont<limit)
                {
                    for (conta=1;conta<limit;conta++)
                    {
                        if(Tiempo==Procs[conta].TiempoLlega && Procs[conta].added==false)
                        {
                            presentes.push_back(Procs[conta]);
                            Procs[conta].added==true;
                            auxcont=auxcont+1;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }

            if (presentes[0].TiempoEx < presentes[0].TiempoReq)
            {   
                
                if (counter==quantum)//si se cumplio el quantum
                {   
                    counter=0;//contador de quantum a 0
                    use=&(presentes.front());// se obtiene la referencia al que se ejecutaba
                    presentes.pop_front();//se desencola
                    presentes.push_back(*use);// se vuelve a encolar
                }
                else continue;
            }
            else
            {   
                counter=0;//contador del quantum a cero
                //calcula promedios, tambien se desencola 1 proceso y se mete en la cola de terminados
                presentes[0].TiempoResp =Tiempo - presentes[0].TiempoLlega;
                presentes[0].TiempoEsp = presentes[0].TiempoResp - presentes[0].TiempoReq;    
                presentes[0].PropPenal =presentes[0].TiempoResp / presentes[0].TiempoReq;
                presentes[0].PropResp = 1/presentes[0].PropPenal ;
                use= &(presentes.front());
                presentes.pop_front();
                ended.push_back(*use);
                

            }
    
        }
        use=0;
delete use;
    Promedios();
}

void roundR::Promedios()
{   
    float totalProc=Procs.size();
    int conta=0;
    float Promedios[3]={0,0,0};
    string palabras[5]={"A      ","B      ","C      ","D      ","E      "};
    sort(ended.begin(),ended.end(),[](const proceso & a, const proceso & b) -> bool{  return a.TiempoLlega < b.TiempoLlega; });
    for (conta=0;conta<ended.size();conta++)
    {
        Promedios[0]+=ended[conta].TiempoResp;
        Promedios[1]+=ended[conta].TiempoEsp;
        Promedios[2]+=ended[conta].PropPenal;

    }
    Promedios[0]/=totalProc;
    Promedios[1]/=totalProc;
    Promedios[2]/=totalProc;

    cout<<"Proceso\t   Ini\t   Treq\t     T\t     E\t     P"<<endl;
    for(conta=0;conta<ended.size();conta++)
    {
        cout<<palabras[conta]<<"\t     "<<ended[conta].TiempoLlega<<"\t     "<<ended[conta].TiempoReq<<"\t     "<<ended[conta].TiempoResp<<"\t     "<<ended[conta].TiempoEsp<<"\t     "<<ended[conta].PropPenal<<endl;
    }
    cout<<"Promedio\t       \t    "<<Promedios[0]<<"\t    "<<Promedios[1]<<"\t    "<<Promedios[2]<<endl;
}