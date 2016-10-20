# Los límites de lo aceptable tras un `malloc`

1. Datos de replicar el experimento:
   1. **Sistema operativo:** Linux version 4.4.0-42-generic (buildd@lcy01-01) (gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04.3) ) #62~14.04.1-Ubuntu SMP Fri Oct 7 23:15:48 UTC 2016
   2. **Compilador:** gcc (Ubuntu 4.8.5-2ubuntu1~14.04.1) 4.8.5
   3. **Biblioteca de C:** N/A
   4. **Número de iteraciones logrado antes del `segmentation fault`:** 33787
   5. **¿Hay algún contenido *interesante* en la memoria? ¿Qué pueden inferir de él? ¿Pueden influir *indirectamente* en él?  (esto es, ¿pueden modificarlo de alguna manera que no sea escribiendo directamente a dichos bytes de memoria?):** En todos los datos impresos en pantalla solamente el valor 18 mostro un contenido distinto a cero (La palabra #18 es: 135089), de ahi en mas, solo se obtuvieron ceros. Seria interesante buscar un mejor metodo de lectura sobre la memoria en donde pudieramos obtener una interpretacion mas completa de la informacion que hay en memoria, numericamente como lo estamos haciendo no detecto nada interesante en los datos obtenidos. Creo que no hay manera en que podriamos pegarle a los valores de memoria que estamos usando sin escribir directamente en dichos bytes de memoria.
2. **¿Cuánto mide `datos` en sus sistemas? ¿Cambia el resultado si emplean un tipo de datos diferente? ¿Un número diferente de elementos?:** Segun `limits.h` el tamaño maximo para un entero signado es `2147483647`. Por lo que `datos` mide `2147483647*n_elementos` y de ahi se hace la correspondiente conversion a bits. El valor numerico tomado anteriormente si cambia dependiendo del tipo de dato que se utilice para el apuntador.

##Modificacion propia

Me di la pequeña libertad de modificar el programa, añadiendo apuntadores de distintos tipos para ver que sucedia asi como opcion para ir hacia adelante (indices positivos) y hacia atras (indices negativos) en los apuntadores.

###Apuntador de caracteres
1. Tope superior alcanzado: 135,151
2. Tope inferior alcanzado: -16

###Apuntador de flotantes
1. Tope superior alcanzado: 33,787
2. Tope inferior alcanzado: -4

###Apuntador de double
1. Tope superior alcanzado: 16,893
2. Tope inferior alcanzado: -2
