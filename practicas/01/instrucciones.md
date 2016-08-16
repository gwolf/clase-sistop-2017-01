# Práctica 1: Uso de Git y de Github

Esta práctica busca que tengas las herramientas básicas mínimas para
utilizar tanto Git como GitHub, y sirve como base para todas las
prácticas futuras.

Te recuerdo que, para comprender el funcionamiento de Git y la forma
de colaboración de GitHub, les dí una serie de ligas en la
[página principal del repositorio](https://github.com/gwolf/clase-sistop-2017-01).

## 1. Tu cuenta de usuario

Entra a https://github.com y crea una cuenta de usuario. Si ya tienes
una, puedes (y te recomiendo) utilizar la ya existente.

## 2. Un *fork* del repositorio principal

El repositorio principal desde el que estaremos trabajando es
https://github.com/gwolf/clase-sistop-2017-01; lo primero que debes
hacer es copiar el repositorio a tu espacio personal (hacer un "fork"
— Una bifurcación). Para esto, oprime el botón en la parte superior
derecha:

!(https://raw.githubusercontent.com/gwolf/clase-sistop-2017-01/master/img/fork.png)

Notarás que, en la parte superior izquierda, en vez de mostrar
`gwolf/clase-sistop-2017-01`, ahora lo mostrará con tu nombre de
usuario.

## 3. *Clona* el repositorio

El siguiente paso es llevar una copia del repositorio a tu
computadora, para que puedas trabajar en él localmente. Hazlo con la
dirección que ofrece el botón verde, *clone or download*, en la parte
derecha de la pantalla.

Ojo, esto deberás hacerlo con el programa que elijas para manejar
*Git* en tu computadora. Hay muchos programas que manejan Git, y cada
uno de ustedes puede elegir el que prefiera. La
[página de descargas de Git](https://git-scm.com/downloads) ofrece
clientes para Windows, MacOS, Linux y Solaris; en Linux, te recomiendo
fuertemente utilizar el que ya viene *empaquetado* para tu
distribución.

Las instrucciones que doy en esta práctica asumen que estás usando una
interfaz Git de línea de comando; si prefieres usar una basada en
interfaz gráfica, queda para tí el convertir las instrucciones en
*ratonazos* ;-)

Si tu nombre de usuario es `alumno01`, tendrás que hacer algo como:

`    $ git clone https://github.com/alumno01/clase-sistop-2017-01.git`

Eso traerá una copia del repositorio a tu computadora, desde donde
podrás trabajar.

## 4. Crea un archivo dentro del directorio de esta práctica

Lo único que te pido en esta práctica es que crees un archivo de texto
con tu nombre de usuario y nombre real. Para esto, entra (desde tu
computadora) al directorio `practicas/01` dentro de tu copia del
repositorio, y crea un archivo de texto con tu nombre de
usuario. Volviendo al ejemplo del usuario `alumno01`, crea el archivo
`practicas/01/alumno01.txt`, e indícame en él tu nombre:

`    $ cd practicas/01
    $ echo "Hola! Me llamo Fulano De Tal" > alumno01.txt`

