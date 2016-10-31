# Calificación de la tarea 3 (*Algoritmos de planificación*)

## Ángel Vázquez
* **Archivos:** [Fuente en Swift](./Angel5215/Planificacion.swift),
  [Captura de pantalla 1](./Angel5215/001.png),
  [Captura de pantalla 2](./Angel5215/002.png),
  [Captura de pantalla 3](./Angel5215/003.png),
  [Captura de pantalla 4](./Angel5215/004.png),
  [Captura de pantalla 5](./Angel5215/005.png),
  [Captura de pantalla 6](./Angel5215/006.png)
* **Calificación:** 10
* **Comentarios:**
  - Primera vez que un alumno me entrega código en *Swift* — Tengo que
    hacer la revisión únicamente sobre el fuente (¡pero agradezco las
    capturas! :) ) La ejecución de tu código me parece que es
    correcta.

	Me llama la atención la cantidad de casos en que te obligas a
    repetir código dependiendo del sistema operativo... Si la única
    diferencia real es la función `random`, ¿no habría resultado más
    conveniente declarar una sola vez:

	    func aleatorio(tope: int) -> Int {
		    #if os(Linux)
			return Int(random() % tope + 1)
			#else
			return Int(arc4random_uniform(10)+1)
			#endif
		}

	(escribo como *creo* que debería verse el Swift)

	Pero, en general, me gusta. Un poquito muy largo, tal vez,
    pero... bueno, también es lo que impone el estilo del lenguaje,
    probablemente.

## Max Sánchez
* **Archivos:** [Lanzador](./MaxSanchez/main.py),
  [Biblioteca con la lógica](./MaxSanchez/bib.py)
* **Calificación:** 10
* **Comentarios:**
	- ¡Bien! Me gusta la implementación. Requiere de entrada del
      usuario, que no es lo que yo quería, pero no es terrible.
	- Ya que manejas la entrada desde `main.py` y la lógica desde
      `bib.py`, tendría sentido que fuera en el primero que
      preguntaras la duración de `q`, y llamaras a
      `colaProc(num,q)`. De otro modo, la separación en archivos no
      sigue ninguna lógica clara.
    - ¡Buen detalle! Me quedé rascándome la cabeza cuando vi esto:

			Duración de cada proceso		[3, 10, 7]
			Tiempo de entrada por cada proceso	[0, 6, 7]
			
			Guia de tiempo	0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 
			FCFS	A A A Z Z Z B B B B B  B  B  B  B  B  C  C  C  C  C  C  C  --> T=9.67	E=3.00	P=1.43
			RR		A A A Z Z Z B B C C B  B  C  C  B  B  C  C  B  B  C  B  B  --> T=11.33	E=4.67	P=1.57
			SPN		A A A Z Z Z B C C C C  C  C  C  B  B  B  B  B  B  B  B  B  --> T=9.00	E=1.33	P=2.23

	  Pero usar `Z` para denotar *no tengo nada por ejecutar* es un
      buen recurso, ¡y muy importante!

	- A veces creo que me despierto más maldoso que otras... Cuando
    recibes entrada del usuario, ¡no olvides validarla! Esto no es
    terrible:

	    $ python3 main.py 
		Tarea: Realizar una prograama que simule la planeación de procesos usando un algoritmo de planeación
		algoritmos elegidos: First Come First Served (FCFS), Round Robin (RR) y Short Process Next
		
		Cuantos procesos quieres simular, recomendación 3-10: 0
		La medida de q para Round Robin: 3
		
		Duración de cada proceso		[10]
		Tiempo de entrada por cada proceso	[0]
		
		Guia de tiempo	
		FCFS		--> T=0.00	E=0.00	P=0.00
		Traceback (most recent call last):
		  File "main.py", line 18, in <module>
		    colaProc(n)
		  File "/home/gwolf/vcs/clase-sistop-2017-01/tareas/03/MaxSanchez/bib.py", line 58, in __init__
		    self.RoundRobin()
		  File "/home/gwolf/vcs/clase-sistop-2017-01/tareas/03/MaxSanchez/bib.py", line 132, in RoundRobin
		    f[i]=True
		IndexError: list assignment index out of range

	Si le digo que `N=0`, obviamente me va a dar una división entre
    cero. Sin embargo, ¿qué pasa si `q=0`?

		$ python3 main.py 
		Tarea: Realizar una prograama que simule la planeación de procesos usando un algoritmo de planeación
		algoritmos elegidos: First Come First Served (FCFS), Round Robin (RR) y Short Process Next
		
		Cuantos procesos quieres simular, recomendación 3-10: 3
		La medida de q para Round Robin: 0
		
		Duración de cada proceso		[5, 10, 1]
		Tiempo de entrada por cada proceso	[0, 1, 3]
		
		Guia de tiempo	0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
		FCFS		A A A A A B B B B B B  B  B  B  B  C  --> T=10.67	E=5.33	P=5.13

	Y tengo que matar al proceso.

## Josué Quiñones
* **Archivos:** [Código en C++](./QuiñonesJosue/algoritmos.cpp),
  [Captura de pantalla 1](./QuiñonesJosue/prueba1.png),
  [Captura de pantalla 2](./QuiñonesJosue/prueba2.png),
  [Captura de pantalla 3](./QuiñonesJosue/prueba3.png)
* **Calificación:** 10
* **Comentarios:**
  - ¡Excelente! Me da gusto que alguien se eche el trompo a la uña y
    haga una implementación de uno de los algoritmos menos
    triviales. ¡Gracias por regresarme la fé en la humanidad! ;-)
  - Tu código pide a gritos un poco más de comentarios, pues hay
    muchas tareas que no resultan obvias del contexto o de las
    variables empleadas. Tal vez ayudaría dividirlo más en funciones,
    tanto para reducir la profundidad de anidamiento como para
    explicar con un nombre amigable al humano lo que significa cada
    paso de la ejecución.
  - Indentar el código... No sólo lo hacemos por buena onda, ¡sino
  porque ayuda muchísimo a su lectura y depuración!

## Yaxkin Sánchez
* **Archivos:** [Código en
  Python](./YaxkinSanchez/AlgoritmosPlanificacion.py)
* **Calificación:** 10
* **Comentarios:**
  - Implementación simple de seguir, ejecución correcta. ¡Bien!
  - Lo único en que te desviaste de mi sugerencia fue en que el total
    de procesos debía ser también variable — pero es un punto muy
    menor.

## Miguel Vargas
* **Archivos:** [Código en Python](./MiguelVargas/tarea3.py)
* **Calificación:** 6
* **Comentarios:**
  - Cuando voy comenzando a disfrutar de un programa escrito de forma
    corta y simple de leer, se termina... ¡demasiado pronto!
  - Implementaste únicamente `FCFS`, no `RR` ni `SPN`.


## Jesús García
* **Archivos:** [Código en C++](./JesusAlberto/tarea3.cpp)
* **Calificación:** 10 × 0.8 = 8
* **Comentarios:** Calificado sobre 8 por entrega extemporánea.
  - ¡Qué bueno! Uno más que implementa un algoritmo no-tan-sencillo.
  - No hay nada de malo en referirte a recursos en línea, siempre y
    cuando los cites o los uses como inspiración/explicación. Viendo
    tu código, me parece que es verdaderamente tuyo.
  - Hiciste una pequeña omisión en FCFS, con la que únicamente muestra
    los primeros 5 procesos, en vez de los 12 con que trabajas. Se
    corrige con:

        diff --git a/tareas/03/JesusAlberto/tarea3.cpp b/tareas/03/JesusAlberto/tarea3.cpp
		index af7cf4d..8df9fed 100644
		--- a/tareas/03/JesusAlberto/tarea3.cpp
		+++ b/tareas/03/JesusAlberto/tarea3.cpp
		@@ -69,7 +69,7 @@ public:
		 }
		        void mostrar(){
                        std::cout << "\nCon FCFS:\n" << std::endl;
		-               for (int i = 0; i < 5; i++)
		+               for (int i = 0; i < MAX; i++)^M
						{
						std::cout << "Termino el proceso " << p[i].nproce << " con una duracion de " << p[i].dura << std::endl;
						}

   - Me pareció curioso que tu FCFS no entrega los resultados en un
     órden preciso, 0-1-2-3-4-..., hasta que comprendí que los
     procesos no son numerados según su órden de llegada sino que
     arbitrariamente. Es mayormente consistente y correcto (hay
     pequeñas incorrecciones), y me parece perfecto que lo manejes en
     tu código!
   - Tu estilo de código es un tanto dificil de leer; te sugiero
     trabajar en encontrar cuando estás duplicando funcionalidad y
     eliminar esta duplicidad mediante la llamada a funciones más
     cortas y claras; tu indentación no es consistente (cuesta trabajo
     ver a ojo dónde comienzan y terminan las declaraciones.
   - Lástima que no la entregaste a tiempo :-(

## Abraham Ortega
* **Archivos:** [Código global en C++](./OrtegaAbraham/Algoritmos.cpp),
  [Código de FCFS en C++](./OrtegaAbraham/fcfs.cpp),
  [Encabezados para FCFS](./OrtegaAbraham/fcfs.h),
  [Código para RR en C++](./OrtegaAbraham/roundr.cpp),
  [Encabezados para RR](./OrtegaAbraham/roundr.h),
  [Código para SPN en C++](./OrtegaAbraham/snp.cpp),
  [Encabezados para SPN](./OrtegaAbraham/snp.h)
* **Calificación:** 10 × 0.8 = 8
* **Comentarios:** Calificado sobre 8 por entrega extemporánea.
  - Entregaste un proyecto que comprende varios archivos fuente
    separados; si bien lo "obvio" es compilarlos con un `g++ fcfs.cpp
    roundr.cpp snp.cpp Algoritmos.cpp`, para evitarle problemas a
    quien lo revise, te sugiero acompañar tus entregas con un
    `Makefile` (o mínimo, un `README`)
  - Haces una bastante buena separación funcional en namespaces (no
    exactamente "clases", como lo mencionas). ¡Bien
      - Sin embargo, ¡deberías aprovechar para evitar la siempre
        nociva repetición de código! En vez de copiar y pegar
        `*::Promedios()`, debería estar en un espacio común, y
        únicamente ser invocada desde donde haga falta.
  - Me llama la atención fuertemente la falta de comentarios en
    `fcfs`, y la sobreabundancia (llega a ser demasiado, creo) en
    `roundr` y `snp`.
  - Buena implementación en general. ¡Lástima que no la entregaste en
    tiempo! :(


## Sebastián Aguilar
* **Archivos:** [Código en C](./Penserbjorne/administradores_procesos.c),
  [Captura de pantalla 1](./Penserbjorne/ronda1.png),
  [Captura de pantalla 2](./Penserbjorne/ronda3.png),
  [Captura de pantalla 3](./Penserbjorne/ronda3.png), 
* **Calificación:** 10 × 0.5 = 5
* **Comentarios:** Calificado sobre 5 por entrega *muy* extemporánea.
  - ¡Muy bonita implementación! Es la primera vez que alguien me
    entrega esta tarea donde me siento a "ver la tele" y esperar con
    ansias a que llegue `t=10` para ver cómo se resuelvae ;-)
  - Y aparte, muy bueno también que me entregues `SRR`, que se sale de
    los algoritmos base y *facilitos* ;-)
  - Me gustaría depurar un poco tu `SRR`, porque no estoy seguro que
    está admitiendo los procesos nuevos como "promete". Me parece, a
    simple ojo de resultados, que invertiste el manejo de `a` y `b`, o
    tal vez no reinicias el valor de la prioridad a cero cuando te
    quedas sin procesos en ejecución.
  - ...Lástima que entregaste la tarea tan tarde :-(

## Gerardo Mendoza
* **Archivos:** [Código de FIFO en Python](./Gerardmc95/FIFO.py),
  [Captura de pantalla de FIFO](./Gerardmc95/FIFO.png),
  [Código de RR en Python](./Gerardmc95/RR.py),
  [Captura de pantalla de RR](./Gerardmc95/RR.png),
  [Código de SPN en Python](./Gerardmc95/SPN.py),
  [Captura de pantalla de SPN](./Gerardmc95/SPN.png),
* **Calificación:** 10 × 0.5 = 5
* **Comentarios:** Calificado sobre 5 por entrega *muy* extemporánea.
  - Para FIFO y SPN imprimes la tabla de evaluación completa, pero no
    la simulación de procesos; para RR imprimes *a veces* esta
    simulación, pero no la tabla de evaluación. ¿Por qué?

  - Curioso: En RR, a veces incluyes la última línea, pero no siempre:

		$ python RR.py 
		Proceso 	Llegada 	Duracion 	
		A 		0 		3
		B 		2 		2
		C 		3 		1
		D 		2 		7
		E 		3 		4
		
		$ python RR.py 
		Proceso 	Llegada 	Duracion 	
		A 		0 		8
		B 		2 		1
		C 		2 		4
		D 		2 		6
		E 		1 		5
		
		$ python RR.py 
		Proceso 	Llegada 	Duracion 	
		A 		0 		6
		B 		2 		9
		C 		2 		4
		D 		1 		6
		E 		2 		4
		
		A A A B B B C C C D D D E E E A B B B D

  - En SPN, cuando imprimes la lista, si el proceso `a` no es el
    primero en ejecutarse, confunde los nombres de procesos al
    imprimirse:

		$ python SPN.py 
		Proceso 	Llegada 	Duracion 	Comienzo 	Finalizacion 	Espera 	
		   a 		   0 		   8 		   0 		   8 		   0 		
		   c 		   1 		   1 		   8 		   9 		   7 		
		   e 		   2 		   1 		   9 		   10 		   7 		
		   d 		   3 		   1 		   10 		   11 		   7 		
		   b 		   5 		   5 		   11 		   16 		   6 		
	    $ python SPN.py 
		Proceso 	Llegada 	Duracion 	Comienzo 	Finalizacion 	Espera 	
		   a 		   0 		   8 		   0 		   8 		   0 		
		   b 		   1 		   3 		   8 		   11 		   7 		
		   d 		   4 		   6 		   11 		   17 		   7 		
		   a 		   0 		   8 		   17 		   25 		   17 		
		   c 		   1 		   8 		   25 		   33 		   24 		
	    $ python SPN.py 
		Proceso 	Llegada 	Duracion 	Comienzo 	Finalizacion 	Espera 	
		   a 		   0 		   5 		   0 		   5 		   0 		
		   e 		   2 		   2 		   5 		   7 		   3 		
		   a 		   0 		   5 		   7 		   12 		   7 		
		   d 		   5 		   5 		   12 		   17 		   7 		
		   c 		   4 		   9 		   17 		   26 		   13 		
  - Lástima que entregaste tan tarde esta tarea.

## Bidkar Páez
* **Archivos:** [Código en Python](./PaezBidkar/algoritmosPlanificacion.py)
* **Calificación:** 10 × 0.5 = 5
* **Comentarios:** Calificado sobre 5 por entrega *muy* extemporánea.
  - Creo que el tuyo es, de los revisados, el programa que más se
    acerca al planteamiento que les hice originalmente (permitirme
    comparar entre varias ejecuciones con los distintos algoritmos)
  - Es una buena implementación, sin embargo y como le apunto a varios
    de tus compañeros, ganaría mucho si redujeras la duplicación de
    código.
  - ¡Lástima que entregaste tan tarde esta tarea!
