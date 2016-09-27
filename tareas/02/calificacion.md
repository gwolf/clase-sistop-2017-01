# Calificación de la tarea 2 (*Problemas de sincronización*)

## Erik Sanabria

* **Archivos:** [ErikSanabria/source.cpp](Fuente C++), [ErikSanabria/Makefile](Makefile)
* **Problema elegido:** Cruce de caminos
* **Calificación:** 6
* **Comentarios:** Si bien aparentemente la resolución es
  correcta... No cumple con lo que solicité.

  La comunicación entre hilos no se realiza mediante primitivas de
  sincronización. Esto significa que una vez cada tanto tiempo te vas
  a encontrar con que un hilo fue detenido justo después de evaluar
  una condición como verdadera... Y otro hilo hará lo mismo, con lo
  que tendrás dos hilos marcando como verdadera a la misma celda.

  Eso, en buen español, se llama *choque* o *colisión*. Claro, en el
  lenguaje propio de nuestra materia se llama *condición de carrera no
  resuelta*.

  Además de todo... Resolver esto con semáforos resulta *mucho* más
  sencillo. Siguiendo tu notación, si tienes un auto llegando por `A1`
  que va hacia `D1`, no tiene que verificar nada — Basta con que haga:

		print "Hilo %d entrando por A1..." % thread_id
		semaf_B1.acquire()
		print "Hilo %d avanzando a B1..." % thread_id
		semaf_B1.release()
		semaf_C1.acquire()
		print "Hilo %d avanzando a C1..." % thread_id
		semaf_C1.release()
		print "Hilo %d avanzando a D1..." % thread_id

  Y ya está del otro lado. Claro, no estoy protegiendo de bloqueo
  mutuo (que puede ocurrir).

## Abraham Ortega y Bidkar Páez

* **Archivos:** [AbrahamOrtega_y_BidkarPaez.py](Fuente Python)
* **Problema elegido:** El cruce del río
* **Calificación:** 10
* **Comentarios:** Buena implementación. Logró soportar que le metiera
  el pie varias veces; una vez logré un par de balsas no balanceadas:

		La balsa  4 se ha ido
		acabo de abordar y soy un hacker mi numero es 23
		acabo de abordar y soy un hacker mi numero es 11
		acabo de abordar y soy un serf mi numero es 23
		acabo de abordar y soy un hacker mi numero es 24
		La balsa  5 se ha ido
		acabo de abordar y soy un hacker mi numero es 28
		acabo de abordar y soy un serf mi numero es 24
		acabo de abordar y soy un serf mi numero es 25
		acabo de abordar y soy un serf mi numero es 27
		La balsa  6 se ha ido

   ...Pero la implementación es claramente correcta :) Debe haber sido
   alguna de las meneadas que yo le puse.

## Yaxkin Sánchez

* **Archivos:** [ProblemaSanta_YaxkinSanchez.py](Fuente Python)
* **Problema elegido:** Santa Claus
* **Calificación:** 10
* **Comentarios:** ¡Interesante implementación! Creo que nunca lo
  había visto basado en contadores en vez de multiplexes :-) ¡Da gusto
  leer ideas frescas!

  Ojo: Receurda incluir tu nombre en los comentarios del fuente, para
  evitar problemas.

## Josué Quiñones y Ángel Vázquez

* **Archivos:** [QuiñonesRivera_y_VazquezAlvarez.py](Fuente Python)
* **Problema elegido:** El cruce del río
* **Calificación:** 8
* **Comentarios:** La implementación clásica. Les di la resolución
  como referencia por si se atoraban irremisiblemente, ¡sería mejor
  ser menos directos en la copia! :)

## Max Sánchez

* **Archivos:**  [balsasHacker&Windows.py](Fuente Python)
* **Problema elegido:** El cruce del río
* **Calificación:** 9
* **Comentarios:** Buena implementación, aunque le falta algo de
  manejo de errores. Un ejemplo:
    Si obligo a que haya balsas sin balance, permite zarpar a una
    balsa desbalanceada. Pude observar lo siguiente de forma repetida:

			$ python balsasHacker\&Windows.py 
			Cuantos programadores de linux tienes: 3
			Cuantos programadores de windows tienes: 1
			Aqui va una balsa: 
			['linux_2', 'win_0', 'linux_1', 'linux_0']
			Estos fueron los que quedaron 
			[]
			[]
			[]

	Esto es consistente, siendo 3/1, 1/3, 5/3, y demás
    combinaciones. Eso sí, curiosamente parece que balancea bien
    siempre que tiene la posibilidad.

