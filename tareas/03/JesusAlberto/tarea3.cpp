#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<cmath>
#define MAX 12
//Maestro la verdad me base en algoritmos que estaban en internet
//en la teroria es facil entenderle pero en la practica esta algo dificil
//Declaramos el struct para manejar las variables a utilizar 
struct proci{
	int t_llegada;  //tiempo de llagada
	float dura; // Duracion 1
	float dura2; //Duracion 2
	int nproce; //Numero de proceso 
	float tiemt; //tiempo total 
	int nejecu; //numero de ejecuciones que lleva el proceso activo 
};
typedef struct Nodo nodo;; // typedef Estructura Nodo nodo 
struct Nodo{   //estructura nodo
	proci proc;
	nodo *next;
};
struct lista
{
	nodo *inicio,*fin;
};

proci cola[MAX];

class FCFS{

private:
	int nproce;
	//Procesos cola[MAX];

public:
	proci p[MAX];
	//Constructor
	//FCFS(num,t) : num_proceso(num) {}

	//Metodos

	void setNumProc(int num){
		this-> nproce = num;
		p[nproce].nproce=nproce;
	}
	void formarProceso(int llegada, int dura){
		p[nproce].t_llegada = llegada;
		p[nproce].dura = dura;
		std::cout << "Llego el proceso: " << nproce << " con un tiempo de llegada de " << llegada <<
		" con una duracion de " << dura << std::endl;
		//p[num_proceso].terminado = false;
	}
	void ejecutarProcesos(){
		int a=0;
		proci aux;
	
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
		std::cout << "Termino el proceso " << p[i].nproce << " con una duracion de " << p[i].dura << std::endl;
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
	void formarProceso(proci proce){
		//for (int i = 0; i < MAX; i++)
	//{
			nodo *n = new nodo;
		n->proc = proce;
		//std::cout << "se forma el proceso " << n->proc.num_proceso << std::endl;
			if(ls->fin == NULL){
				ls->inicio = n;
			ls->fin = n;
			ls->inicio->proc.tiemt = 0;
				ls->inicio->proc.nejecu = 0;
			//	std::cout << "se formo el proceso 0" << std::endl;
			} else{
				ls->fin->next = n;
			ls->fin = n;
			ls->fin->proc.tiemt = 0;
				ls->fin->proc.nejecu = 0;
			//	std::cout << "se formo el proceso " << ls->fin->proc.num_proceso << std::endl;
			}
			ls->fin->proc.dura2 = ls->fin->proc.dura;
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
	l->fin->proc.nejecu = 0;
		borrar(aux, n->proc.nproce);
	}
	nodo *BuscarAnterior(lista *l, int nproce){
		nodo *i = new nodo;
		i = l->inicio;
	if(i->proc.nproce == nproce){
			return NULL;
		}
		while(i!= l->fin){
	if(i->next->proc.nproce == nproce){
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
				if(i->proc.nejecu == n1){
					cambioCola(ls2, i,ls);
				}else{
				i->proc.nejecu++;
				if(i->proc.dura <= 0){
					i->proc.tiemt += i->proc.dura;
					total -= i->proc.dura;
					mostrar(i->proc.nproce, i->proc.tiemt, (i->proc.tiemt-i->proc.dura2), (i->proc.tiemt/i->proc.dura2));
					borrar(ls,i->proc.nproce);
				} else{
					i->proc.dura -= q1;
					i->proc.tiemt += q1;
					//i->proc.T += total;
				}
				}
				cont3++;
			}
			}else{
				if(ls2->fin != NULL){
				for (i = ls2->inicio; i != NULL; i=i->next)
				{
					
					i->proc.tiemt += q2;
					total += q2;
				if(i->proc.nejecu == n2){
				cambioCola(ls3, i,ls2);
				} else{
				i->proc.nejecu++;
				if(i->proc.dura <= 0){
					i->proc.tiemt += i->proc.dura;
					total -= i->proc.dura;
				mostrar(i->proc.nproce, i->proc.tiemt, (i->proc.tiemt-i->proc.dura2), (i->proc.tiemt/i->proc.dura2));
					borrar(ls2,i->proc.nproce);
				} else{
					//i->proc.T += q2;
					i->proc.dura -= q2;
			}
				}
				}
				} else{
					for (i = ls3->inicio; i != NULL; i=i->next)
			{
				//tiempo += q3;
				i->proc.tiemt += q3;
				total += q3;
				i->proc.nejecu++;
				if(i->proc.dura <= 0){
					i->proc.tiemt += i->proc.dura;
					total -= i->proc.dura;
					mostrar(i->proc.nproce, i->proc.tiemt, (i->proc.tiemt-i->proc.dura2), (i->proc.tiemt/i->proc.dura2));
				borrar(ls3,i->proc.nproce);
			} else{
					//i->proc.T += q3;
					i->proc.dura -= q3;
				}
			}
					//salida = false;
				}
			}
			
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
	void formarProceso(proci process){
		nodo *n = new nodo;
			n->proc = process;
			//std::cout << "se forma el proceso " << n->proc.num_proceso << std::endl;
			if(colaListos->fin == NULL){
				colaListos->inicio = n;
				colaListos->fin = n;
				colaListos->inicio->proc.tiemt = 0;
				colaListos->inicio->proc.nejecu = 0;
			//	std::cout << "se formo el proceso 0" << std::endl;
			} else{
				colaListos->fin->next = n;
				colaListos->fin = n;
				colaListos->fin->proc.tiemt = 0;
				colaListos->fin->proc.nejecu = 0;
			//	std::cout << "se formo el proceso " << ls->fin->proc.num_proceso << std::endl;
			}
			colaListos->fin->proc.dura2 = colaListos->fin->proc.dura;
	}
	nodo *BuscarAnterior(lista *l, int nproce){
		nodo *i = new nodo;
		i = l->inicio;
		if(i->proc.nproce == nproce){
			return NULL;
	}
		while(i!= l->fin){
			if(i->next->proc.nproce == nproce){
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
			if(i->proc.dura == 0){
				i->proc.tiemt += tiempo;
				i->proc.tiemt -= i->proc.t_llegada;
				std::cout << "D: " << i->proc.dura2 << std::endl;
				mostrar(i->proc.nproce, i->proc.tiemt, (i->proc.tiemt-i->proc.dura2), (i->proc.tiemt/i->proc.dura2));
				borrar(colaListos,i->proc.nproce);
			} else{
			//i->proc.T++;
			i->proc.dura--;
		}
		//tiempo++;
		}
	}
};

int main(){
	
	int llegada, dura,suma=0;
	FCFS fcfs;
	//int tiempo=0;
	bool salida=true;
	int tiempo=0;

	srand(time(0));


	for (int i = 0; i < MAX; i++)
	{
		llegada = rand() %5 + 1;
		//llegada = i;
		dura = rand() %10+1;
		if(i==0){
			fcfs.setNumProc(i);
			fcfs.formarProceso(0,dura);
		}else{
			fcfs.setNumProc(i);
			fcfs.formarProceso(llegada,dura);
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
	suma += cola[i].dura;
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
}; 
