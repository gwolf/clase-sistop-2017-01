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

## Gerardo Mendoza
* **Archivos:** [MendozaColmenaresAsesor.py](Fuente Python)
* **Problema elegido:** El asesor y los alumnos
* **Calificación:** 10 × 0.8 = 8
* **Comentarios:** Calificado sobre 8 por entrega extemporánea;
  lástima que no entregaste a tiempo :-(

  Bonita implementación. Hiciste un poco de truco al sistema, dado que
  quien llama a la función `asesora()` es el mismo alumno (y no el
  asesor), pero la paso por buena (puede leerse como que *el alumno se
  calla mientras recibe la sabiduría del asesor*).

  Me llama la atención la forma de comentar que sigues — y esto es
  principalmente una crítica a cómo te enseñaron. Documentas con
  comentarios (¡bien!) lo que hace cada función, incluso si es obvio,
  como las funciones `asesora()` y `pregunta()`... ¡Pero no explicas
  tu lógica cuando se pone más densa! Por ejemplo, para tu función
  `alumno()`, ¿cuál es el papel relativo de `mano` y `mutex`? ¿Por qué
  van juntos? Tuve que repasarlo un par de veces para comprenderlo.

  Otra cuestión estilística: ¿Por qué funciona así tu `dicAlumnos`?
  Siempre que te refieres a sus valores, pasas por la transformación
  del `num` numérico que recibes a un `str(unichr(num+48))`, que es la
  representación del número como cadena. Si lo necesitas como llave de
  un diccionario, ¿por qué no hacerlo una sóla vez al principio de la
  función? Y... Si quieres convertir un valor numérico en la cadena
  que lo represente, ¿no es más claro usar un `'%d' % num` por
  ejemplo?

## Jesús García y Andrés López
* **Archivos:** [Tarea2.py](Fuente Python)
* **Problema elegido:** Santa Claus
* **Calificación:** 7 × 0.5 = 3.5
* **Comentarios:** Calificado sobre 5 por entrega *muy* extemporánea
  ¡No funciona correctamente!

        $ python Tarea2.py
		***El reno 1 ha regresado***.
		***El reno 2 ha regresado***.
		***El reno 1 ha regresado***.
		***El reno 3 ha regresado***.
		***El reno 4 ha regresado***.
		***El reno 5 ha regresado***.
		***El reno 6 ha regresado***.
		***El reno 7 ha regresado***.
		***El reno 8 ha regresado***.
		***El reno 9 ha regresado***.
		
		***El elfo 0 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		***El elfo 1 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		***El elfo 2 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		***El elfo 3 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		***El elfo 4 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		***El elfo 5 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		***El elfo 6 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		***El elfo 7 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		***El elfo 8 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		***El elfo 9 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		***El elfo 10 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		***El elfo 11 pacientemente espera a que se junten mas elfos para  pedir ayuda a Santa***
		Terminated

	A ojo, la lógica se ve correcta... ¡Pero Santa nunca se despierta!
    ¿Qué le dieron al pobre viejo?

	En la función `santa()`, esperamos dos señales, tanto por
    `senasanta` como `contamux`. Esto significa que ambas tienen que
    llegar para que Santa se despierte. A Santa no debería importarle
    *por qué* lo están despertando, sino que tiene que despertar a
    hacer *algo* — Bastaría con tener un sólo semáforo
    *despiertaSanta*, que fuera señalizado ya sea por el tercer elfo
    o por el noveno reno en llegar.


## Sebastián Aguilar
* **Archivos:** [Penserbjorne.c](Fuente C)
* **Problema elegido:** El elevador
* **Calificación:** 0
* **Comentarios:** Sin calificación por entrega *muy* extemporánea

   A primera vista, tu implementación se ve completa y bonita... Pero
   no me compiló. Te faltó un `#include <string.h>`

   La ejecución parece ser correcta... Pero dado que no puedo ya darte
   calificación, únicamente anoto la tarea como entregada, y no entro
   a hacer una revisión a detalle.

## Alberto Díaz
* **Archivos:** [Santa_Alberto_Diaz.py](Fuente Python)
* **Problema elegido:** Santa Claus
* **Calificación:** 0
* **Comentarios:** Sin calificación por entrega *muy* extemporánea

   Código bonito, claro, fácil de entender... ¡Me gustó! ¿Por qué no
   entregaste hace un mes? :-(

   La ejecución parece ser correcta... Pero dado que no puedo ya darte
   calificación, únicamente anoto la tarea como entregada, y no entro
   a hacer una revisión a detalle.
