# Los límites de lo aceptable tras un `malloc`

En clase, ilustramos el comportamiento de la memoria segmentada viendo
los límites de lo que el sistema nos autorizaba leer después de
realizar un `malloc`. El código ejemplo en C, titulado `fisgon.c`, era
el siguiente:

    #include <stdio.h>
    #include <stdlib.h>
    
    int main () {
      int *datos;
      int i;
      datos = malloc(16 * sizeof(int));
      for (i=0; i<65536; i++)
        printf("La palabra #%d es: %d\n", i, datos[i]);
	  free(datos);
      return 0;
    }

Esto es, solicitamos la asignación de un espacio equivalente a 16
enteros, recibiendo su apuntador en la variable `datos`, y avanzamos
apartir de `i` hacia adelante hasta donde el sistema nos permita
llegar.

Cabe mencionar que este programa tiene *dos* importantes errores, que
no quieren ver en ningún programa en producción:

1. Imprime valores no inicializados. `malloc()` no garantiza que el
   espacio que entrega esté inicializado a ningún valor, por lo que
   podríamos encontrar *cualquier cosa* en la memoria; en el caso que
   les ilustré, *da la casualidad* (?) que estamos *nadando* en un mar
   de ceros — A excepción de la palabra #18, que contiene el
   valor 135089.
2. Obviamente, estamos leyendo *mucho más allá* de los límites de lo
   solicitado. Esto lo hice para demostrar que `malloc()` hace su
   solicitud de espacio dejando un amplio márgen para no incurrir en
   repetidas llamadas al sistema.

Dicho lo anterior... Para esta práctica, ¿qué quiero que hagan?

1. Repliquen el experimento en su equipo. Reporten:
   1. Sistema operativo (nombre, versión)
   2. Compilador (nombre, versión)
   3. Biblioteca de C, si la conocen (nombre, versión)
   4. Número de iteraciones logrado antes del `segmentation fault`
   5. ¿Hay algún contenido *interesante* en la memoria? ¿Qué pueden
      inferir de él? ¿Pueden influir *indirectamente* en él?  (esto
      es, ¿pueden modificarlo de alguna manera que no sea escribiendo
      directamente a dichos bytes de memoria?)
2. ¿Cuánto mide `datos` en sus sistemas? ¿Cambia el resultado si
   emplean un tipo de datos diferente? ¿Un número diferente de
   elementos?
    1. Tip: En Linux, pueden típicamente encontrar un archivo
       `/usr/include/limits.h` que presenta el rango representable por
       los diferentes tipos de datos especificados en el estándar ISO
       C99.
    3. ¿Cuanto espacio asignó efectivamente el sistema operativo para
    satisfacer la solicitud del `malloc`?

Como un breve tip de comparación, les dejo una comparación que yo
realicé; la abordaremos y replicaremos en clase.

    --- primero	2016-10-13 21:51:23.692704426 -0500
    +++ segundo	2016-10-13 21:51:34.292610120 -0500
    @@ -1,6 +1,7 @@
     4890:   ./a.out
     0000000000400000      4K r-x-- a.out
     0000000000600000      4K rw--- a.out
    +0000000001297000    132K rw---   [ anon ]
     00007ff727130000   1672K r-x-- libc-2.19.so
     00007ff7272d2000   2044K ----- libc-2.19.so
     00007ff7274d1000     16K r---- libc-2.19.so
    @@ -8,7 +9,7 @@
     00007ff7274d7000     16K rw---   [ anon ]
     00007ff7274db000    128K r-x-- ld-2.19.so
     00007ff7276cd000     12K rw---   [ anon ]
    -00007ff7276f9000      8K rw---   [ anon ]
    +00007ff7276f8000     12K rw---   [ anon ]
     00007ff7276fb000      4K r---- ld-2.19.so
     00007ff7276fc000      4K rw--- ld-2.19.so
     00007ff7276fd000      4K rw---   [ anon ]
    @@ -16,4 +17,4 @@
     00007fff22b44000      8K r----   [ anon ]
     00007fff22b46000      8K r-x--   [ anon ]
     ffffffffff600000      4K r-x--   [ anon ]
    - total             4076K
    + total             4212K

Les recuerdo que esta práctica es para entregar y comentar el día
*martes 18 de octubre*.
