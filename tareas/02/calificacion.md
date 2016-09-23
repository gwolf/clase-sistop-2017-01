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
* **Calificación:** 
* **Comentarios:** 

## Yaxkin Sánchez

* **Archivos:** [ProblemaSanta_YaxkinSanchez.py](Fuente Python)
* **Problema elegido:** Santa Claus
* **Calificación:** 
* **Comentarios:** 

## Josué Quiñones y Ángel Vázquez

* **Archivos:** [QuiñonesRivera_y_VazquezAlvarez.py](Fuente Python)
* **Problema elegido:** El cruce del río
* **Calificación:** 
* **Comentarios:** 

## Max Sánchez

* **Archivos:**  [balsasHacker&Windows.py](Fuente Python)
* **Problema elegido:** El cruce del río
* **Calificación:** 
* **Comentarios:** 
