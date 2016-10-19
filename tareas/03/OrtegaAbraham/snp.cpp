/*Clase encargada de algoritmo Round Robin
Se presta para posibles minimización a distitnas funciones*/

#include <vector>//para la utilizacion de vectores
#include <iostream>//para la salida a consola
#include <string>//uso de strings superfluo
#include <algorithm>//para el ordenamiento de los vectores
#include "snp.h"//header donde se declara la clase
using namespace std;//Se utiliza para sencillez en la sintaxis y omitir el std::
/*Metodo constructor de la clase Recibe un a putador de vector para facilitar el paso 
de datos desde el main*/
snP::snP(vector <float>* data)
{   
    construct(data);
   
}


/*Funcion que crea las estructuras necesarias y las mete en un vector para su utilizacion
recibe apuntador a vector para facilitar paso de datos desde main*/
void snP::construct(vector <float> *data)
{   
    
    for (int conta=0; conta< data->size();conta+=2)
    {
        Procs.push_back(proceso((*data)[conta],(*data)[conta+1])); 
        
    }
}

/*Método principal de la clase, esta realiza el algoritmo de planificación (simulado)
y no recibe parametros. pues oslo utiliza los atributos del objeto mismo*/
void snP::shortP()
{       
        int auxcont=1;//contador auxiliar para no entrar en el bucle siempre
        int conta=0;//contador para iterar sobre un vector
        int limit=Procs.size();//Limite para no llamar a size() tantas veces
        proceso *use=0;//apuntador a estructura para poder recibir y encolar de nuevo
//--------------------------------------------Aquí empieza---------------------------------------

        presentes.push_back(Procs[0]);//se mete el primer proceso a la cola de presentes
        use= &(presentes.front());//obtenemos el primer proceso y se "ejecuta"
        while(ended.size()<limit)//mientras la cola de terminados no es del tamaño que la de procesos
        {       
            Tiempo= Tiempo+1;//el tiempo corre
            use->TiempoEx=use->TiempoEx+1;// y se ejecuta el proceso

            //Esta condicional es para que na vez que se alcanze el limite de agregados no se netre al ciclo
            if(auxcont<limit)
                {//este bucle es para recorrer la cola de procesos  para ver si ya llegaron
                    for (conta=1;conta<limit;conta++)
                    {   //si ya llegaron
                        if(Tiempo==Procs[conta].TiempoLlega && Procs[conta].added==false)
                        {//se les agrega a la cola de presentes
                            presentes.push_back(Procs[conta]);
                            Procs[conta].added==true;
                            auxcont=auxcont+1;
                        }
                        else//si no solo se continua
                        {
                            continue;
                        }
                    }
                }

            if ( use->TiempoEx <  use->TiempoReq)//si no se ha ejecutado completo se continua
            {   
                
                 continue;
            }
            else//si no se calculan todos los valores vistos en clases
            {   
                 use->TiempoResp =Tiempo -  use->TiempoLlega;
                 use->TiempoEsp =  use->TiempoResp -  use->TiempoReq;    
                 use->PropPenal = use->TiempoResp /  use->TiempoReq;
                 use->PropResp = 1/ use->PropPenal ;
                 ended.push_back(*use);//se empuja a la cola de terminados
                 presentes.pop_front();//se saca de la cola de presentes por que ya acabo
                 //aqui es  donde la cola se acomoda segun su duracion
                 sort(presentes.begin(),presentes.end(),[](const proceso & a, const proceso & b) -> bool{  return a.TiempoReq < b.TiempoReq; });//si profe use una función lambda por flojo ...
                 //se obtiene el proximo proceso mas corto
                 use= &(presentes.front());
                

            }
    
        }
    use=0;
    delete use;

    Promedios();
}

/*
Esta funcion lo unico que hace es imprimir en consola los datos en una especie de 
"tabla" asi como se vio en la clase. la cola de terminados se ordena segun como llegaron
para no perder la pista.Ademas obtiene los promedios .Esta funcion es la misma para todos los algoritmos
*/
void snP::Promedios()
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