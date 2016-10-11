#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<cmath>
#define MAX 5

struct Procesos{
	int t_llegada;
	float duracion;
	float duracion2;
	int num_proceso;
	float T; //tiempo total 
	int ne; //numero de ejecuciones que lleva el proceso
	//bool terminado;
};
//int tiempo=0;
typedef struct Nodo nodo;;
struct Nodo{
	Procesos proc;
	nodo *next;
};
struct lista
{
	nodo *inicio,*fin;
};

Procesos cola[MAX];

class FCFS{

private:
	int num_proceso;
	//Procesos cola[MAX];

public:
	Procesos p[MAX];
	//Constructor
	//FCFS(num,t) : num_proceso(num) {}

	//Metodos

	void setNumProc(int num){
		this->num_proceso = num;
		p[num_proceso].num_proceso = num_proceso;
	}
	void formarProceso(int llegada, int duracion){
		p[num_proceso].t_llegada = llegada;
		p[num_proceso].duracion = duracion;
		std::cout << "Llego el proceso: " << num_proceso << " con un tiempo de llegada de " << llegada <<
		" con una duracion de " << duracion << std::endl;
		//p[num_proceso].terminado = false;
	}
	void ejecutarProcesos(){
		int a=0;
		Procesos aux;
		/*while(a==0){
			if(p[0]->t_llegada < p[1]->t_llegada)
				if(p[0]->t_llegada < p[2]->t_llegada)
					if(p[0]->t_llegada < p[3]->t_llegada)
						if(p[0]->t_llegada < p[4]->t_llegada){
							p[0]->terminado = true;
							std::cout << "Termino el proceso " + 
							}
		}
		*/
		//cola[i] = p[a];
		for (int i = 0; i < 4; i++){
			for (int j = i+1; j < 5; j++)
			{
				if(p[i].t_llegada > p[j].t_llegada){
					aux = p[i];
					p[i] = p[j];
					p[j] = aux;
				}else{}
				}
			//cola[i] = p[i];
		}
	}
	void mostrar(){
		std::cout << "\nCon FCFS:\n" << std::endl;
		for (int i = 0; i < 5; i++)
		{
		std::cout << "Termino el proceso " << p[i].num_proceso << " con una duracion de " << p[i].duracion << std::endl;
		}
	}


};

class FB{

private:
	int n1,n2,n3; //numero de ejecuciones para bajar nivel de cola de prioridad
	int q1,q2,q3,tick,QBase;
	int cont2,cont3;
	float duracion[MAX];
	int tiempo=0;
	lista *ls,*ls2,*ls3; //ls es la cola con mayor prioridad
public:
	FB(int c2=0, int c3=0) : cont2(c2), cont3(c3) {
		ls = new lista;
		ls->inicio = NULL;
		ls->fin = NULL;
		ls2 = new lista;
		ls2->inicio = NULL;
		ls2->fin = NULL;
		ls3 = new lista;
		ls3->inicio = NULL;
		ls3->fin = NULL;
	}
	void setq(){
		q1 = pow(2,(n1*QBase));
		q2 = pow(2,(n2*QBase));
		q3 = pow(2,(n3*QBase));
	}
	void setN(int n1, int n2, int n3){ 
		this->n1 = n1;
		this->n2 = n2;
		this->n3 = n3;
	}
	void setQBase(int QBase){
		this->QBase = QBase;
	}
	void formarProceso(Procesos proce){
		//for (int i = 0; i < MAX; i++)
		//{
			nodo *n = new nodo;
			n->proc = proce;
			//std::cout << "se forma el proceso " << n->proc.num_proceso << std::endl;
			if(ls->fin == NULL){
				ls->inicio = n;
				ls->fin = n;
				ls->inicio->proc.T = 0;
				ls->inicio->proc.ne = 0;
			//	std::cout << "se formo el proceso 0" << std::endl;
			} else{
				ls->fin->next = n;
				ls->fin = n;
				ls->fin->proc.T = 0;
				ls->fin->proc.ne = 0;
			//	std::cout << "se formo el proceso " << ls->fin->proc.num_proceso << std::endl;
			}
			ls->fin->proc.duracion2 = ls->fin->proc.duracion;
			cont2++;
		//}
	}
	void cambioCola(lista *l, nodo *n, lista *aux){
		if(l->fin == NULL){
				l->inicio = n;
				l->fin = n;
			} else{
				l->fin->next = n;
				l->fin = n;
			}
		l->fin->proc.ne = 0;
		borrar(aux, n->proc.num_proceso);
	}
	nodo *BuscarAnterior(lista *l, int num_proceso){
		nodo *i = new nodo;
		i = l->inicio;
		if(i->proc.num_proceso == num_proceso){
			return NULL;
		}
		while(i!= l->fin){
			if(i->next->proc.num_proceso == num_proceso){
				return i;
			}
			i = i->next;
		}
		return NULL;
	}
	void borrar(lista *l, int num_proceso){
		nodo *anterior = new nodo;
		nodo *aux = new nodo;
		anterior = BuscarAnterior(l,num_proceso);
		if(anterior==NULL){
			aux = l->inicio;
			if(l->inicio == l->fin){
				l->inicio = NULL;
				l->fin = NULL;
			}else	l->inicio = l->inicio->next;
		}else{
			aux = anterior->next;
			if(aux == l->fin)
				l->fin = anterior;
			anterior->next = aux->next;
		}
	}
	void mostrar(int num_proceso, float total, float E, float P){
		std::cout << "Termino el proceso: " << num_proceso << " con un tiempo Total de " << total << ", una espera de: " << E << " y una penalizacion de: " << P << std::endl;
		//std::cout << "q1 q2 q3: " << q1 << " " << q2 << " " << q3 << std::endl;
	}
	void ejecutarProcesos(){
		nodo *i = new nodo;
		int total=0;
		//std::cout << "se" << std::endl;
		//int tiempo=0;
		//bool salida=true;
		//while(salida){
			if(ls->fin != NULL){
				cont3=0;
			for (i = ls->inicio; i != NULL; i=i->next)
			{
				tiempo++;
				//tiempo++;
				//i->proc.T += q1;
				total += q1;
				//tiempo += q1;
				if(i->proc.ne == n1){
					cambioCola(ls2, i,ls);
				}else{
				i->proc.ne++;
				if(i->proc.duracion <= 0){
					i->proc.T += i->proc.duracion;
					total -= i->proc.duracion;
					mostrar(i->proc.num_proceso, i->proc.T, (i->proc.T-i->proc.duracion2), (i->proc.T/i->proc.duracion2));
					borrar(ls,i->proc.num_proceso);
				} else{
					i->proc.duracion -= q1;
					i->proc.T += q1;
					//i->proc.T += total;
				}
				}
				cont3++;
			}
			}else{
				if(ls2->fin != NULL){
				for (i = ls2->inicio; i != NULL; i=i->next)
				{
					//tiempo++;
					//tiempo++;
					//tiempo++;
					//tiempo++;
					//tiempo += q2;
					i->proc.T += q2;
					total += q2;
				if(i->proc.ne == n2){
					cambioCola(ls3, i,ls2);
				} else{
				i->proc.ne++;
				if(i->proc.duracion <= 0){
					i->proc.T += i->proc.duracion;
					total -= i->proc.duracion;
					mostrar(i->proc.num_proceso, i->proc.T, (i->proc.T-i->proc.duracion2), (i->proc.T/i->proc.duracion2));
					borrar(ls2,i->proc.num_proceso);
				} else{
					//i->proc.T += q2;
					i->proc.duracion -= q2;
				}
				}
				}
				} else{
					for (i = ls3->inicio; i != NULL; i=i->next)
			{
				//tiempo += q3;
				i->proc.T += q3;
				total += q3;
				i->proc.ne++;
				if(i->proc.duracion <= 0){
					i->proc.T += i->proc.duracion;
					total -= i->proc.duracion;
					mostrar(i->proc.num_proceso, i->proc.T, (i->proc.T-i->proc.duracion2), (i->proc.T/i->proc.duracion2));
					borrar(ls3,i->proc.num_proceso);
				} else{
					//i->proc.T += q3;
					i->proc.duracion -= q3;
				}
			}
					//salida = false;
				}
			}
			//if(cola[MAX-1].duracion)
			//	salida = false;
			//tiempo++;
		//}
	//return salida;
	}

};

class Round{
private:
	lista *colaListos;
	int tiempo=0;
public:
	Round(){
		colaListos = new lista;
		colaListos->inicio = NULL;
		colaListos->fin = NULL;
	}
	void formarProceso(Procesos process){
		nodo *n = new nodo;
			n->proc = process;
			//std::cout << "se forma el proceso " << n->proc.num_proceso << std::endl;
			if(colaListos->fin == NULL){
				colaListos->inicio = n;
				colaListos->fin = n;
				colaListos->inicio->proc.T = 0;
				colaListos->inicio->proc.ne = 0;
			//	std::cout << "se formo el proceso 0" << std::endl;
			} else{
				colaListos->fin->next = n;
				colaListos->fin = n;
				colaListos->fin->proc.T = 0;
				colaListos->fin->proc.ne = 0;
			//	std::cout << "se formo el proceso " << ls->fin->proc.num_proceso << std::endl;
			}
			colaListos->fin->proc.duracion2 = colaListos->fin->proc.duracion;
	}
	nodo *BuscarAnterior(lista *l, int num_proceso){
		nodo *i = new nodo;
		i = l->inicio;
		if(i->proc.num_proceso == num_proceso){
			return NULL;
		}
		while(i!= l->fin){
			if(i->next->proc.num_proceso == num_proceso){
				return i;
			}
			i = i->next;
		}
		return NULL;
	}
	void borrar(lista *l, int num_proceso){
		nodo *anterior = new nodo;
		nodo *aux = new nodo;
		anterior = BuscarAnterior(l,num_proceso);
		if(anterior==NULL){
			aux = l->inicio;
			if(l->inicio == l->fin){
				l->inicio = NULL;
				l->fin = NULL;
			}else	l->inicio = l->inicio->next;
		}else{
			aux = anterior->next;
			if(aux == l->fin)
				l->fin = anterior;
			anterior->next = aux->next;
		}
	}
	void mostrar(int num_proceso, float total, float E, float P){
		std::cout << "Termino el proceso: " << num_proceso << 
		" con un tiempo Total de " << total << ", una espera de: " << E << 
		" y una penalizacion de: " << P << std::endl;
		//std::cout << "q1 q2 q3: " << q1 << " " << q2 << " " << q3 << std::endl;
	}
	void ejecutarProcesos(){
		nodo *i = new nodo;
		for (i = colaListos->inicio; i != NULL; i = i->next){
			tiempo++;
			if(i->proc.duracion == 0){
				i->proc.T += tiempo;
				i->proc.T -= i->proc.t_llegada;
				std::cout << "D: " << i->proc.duracion2 << std::endl;
				mostrar(i->proc.num_proceso, i->proc.T, (i->proc.T-i->proc.duracion2), (i->proc.T/i->proc.duracion2));
				borrar(colaListos,i->proc.num_proceso);
			} else{
			//i->proc.T++;
			i->proc.duracion--;
		}
		//tiempo++;
		}
	}
};

int main(){
	
	int llegada, duracion,suma=0;
	FCFS fcfs;
	//int tiempo=0;
	bool salida=true;
	int tiempo=0;

	srand(time(0));


	for (int i = 0; i < MAX; i++)
	{
		llegada = rand() %5 + 1;
		//llegada = i;
		duracion = rand() %10+1;
		if(i==0){
			fcfs.setNumProc(i);
			fcfs.formarProceso(0,duracion);
		}else{
			fcfs.setNumProc(i);
			fcfs.formarProceso(llegada,duracion);
		}
	}

	fcfs.ejecutarProcesos();
	fcfs.mostrar();
	for (int i = 0; i < MAX; i++)
	{
		cola[i] = fcfs.p[i];
	}

	FB retro;

	std::cout << "\nCon Retroalimentacion multinivel:\n " << std::endl;

	for (int i = 0; i < MAX; i++)
	{
		suma += cola[i].duracion;
	}

	retro.setN(1,2,4);
	retro.setQBase(1);
	retro.setq();
	while(tiempo <= (suma*2)){
		for (int i = 0; i < MAX; i++){
		if(cola[i].t_llegada == tiempo){
			//std::cout << "tiempo: " << tiempo << std::endl;
			retro.formarProceso(cola[i]);
		}
	}
		retro.ejecutarProcesos();
		//std::cout << "tiempo: " << tiempo << std::endl;
		tiempo++;
	}

	tiempo=0;

	Round ronda;

	std::cout << "\nCon Round Robin:\n " << std::endl;
	while(tiempo <= (suma*2)){
		for (int i = 0; i < MAX; i++){
		if(cola[i].t_llegada == tiempo){
			//std::cout << "tiempo: " << tiempo << std::endl;
			ronda.formarProceso(cola[i]);
		}
	}
		ronda.ejecutarProcesos();
		//std::cout << "tiempo: " << tiempo << std::endl;
		tiempo++;
	}

	//std::cout << "suma: " << suma << std::endl;

	return 0;
}