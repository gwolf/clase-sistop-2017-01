# Calificación de la tarea 3 (*Algoritmos de planificación*)

## Ángel Vázquez
* **Archivos:** [./Angel5215/Planificacion.swift](Fuente en Swift),
  [./Angel5215/001.png](Captura de pantalla 1),
  [./Angel5215/002.png](Captura de pantalla 2),
  [./Angel5215/003.png](Captura de pantalla 3),
  [./Angel5215/004.png](Captura de pantalla 4),
  [./Angel5215/005.png](Captura de pantalla 5),
  [./Angel5215/006.png](Captura de pantalla 6)
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
* **Archivos:** [./MaxSanchez/main.py](Lanzador),
  [./MaxSanchez/bib.py](Biblioteca con la lógica)
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
* **Archivos:** [./QuiñonesJosue/algoritmos.cpp](Código en C++),
  [./QuiñonesJosue/prueba1.png](Captura de pantalla 1),
  [./QuiñonesJosue/prueba2.png](Captura de pantalla 2),
  [./QuiñonesJosue/prueba3.png](Captura de pantalla 3)
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
* **Archivos:** [./YaxkinSanchez/AlgoritmosPlanificacion.py](Código en
  Python)
* **Calificación:** 10
* **Comentarios:**
  - Implementación simple de seguir, ejecución correcta. ¡Bien!
  - Lo único en que te desviaste de mi sugerencia fue en que el total
    de procesos debía ser también variable — pero es un punto muy
    menor.

## Miguel Vargas
* **Archivos:** [./MiguelVargas/tarea3.py](Código en Python)
* **Calificación:** 6
* **Comentarios:**
  - Cuando voy comenzando a disfrutar de un programa escrito de forma
    corta y simple de leer, se termina... ¡demasiado pronto!
  - Implementaste únicamente `FCFS`, no `RR` ni `SPN`.

