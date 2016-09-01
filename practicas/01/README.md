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
— Una bifurcación). Para esto, oprime el botón "Fork" en la parte
superior derecha.

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

Te recomiendo que ubiques a esta copia en un lugar donde puedas
mantenerlo a largo plazo, dado que seguiremos utilizando este
repositorio a lo largo del cursado de la materia.

Ahora, vamos a estar trabajando desde *dentro* de tu directorio
*clonado*:

    $ cd clase-sistop-2017-01

## 4. Crea un archivo dentro del directorio de esta práctica

Lo único que te pido en esta práctica es que crees un archivo de texto
con tu nombre de usuario y nombre real. Para esto, entra (desde tu
computadora) al directorio `practicas/01` dentro de tu copia del
repositorio, y crea un archivo de texto con tu nombre de
usuario. Volviendo al ejemplo del usuario `alumno01`, crea el archivo
`practicas/01/alumno01.txt`, e indícame en él tu nombre:

    $ cd practicas/01
    $ echo "Hola! Me llamo Fulano De Tal" > alumno01.txt

Puedes observar que Git todavía no sabe qué hacer con el archivo que
acabas de crear:

    $ git status
	On branch master
	Your branch is up-to-date with 'origin/master'.
	Untracked files:
	  (use "git add <file>..." to include in what will be committed)

        	practicas/01/alumno01.txt

    nothing added to commit but untracked files present (use "git add" to track)

## 5. Agrega tu archivo a Git y envíalo al servidor

Primero indica a Git que vas a agregar el archivo que creaste:

    $ git add alumno01.txt

Y ahora crea un *commit*. Recuerda darle una descripción acorde:

    $ git commit -m 'Agrego el nombre de Fulano de Tal'

Git es un sistema *distribuido* de control de cambios. Esto significa
que tus cambios están ya registrados en la historia de Git, pero
únicamente en tu computadora. Para enviarlos a GitHub, basta con que
los *empujes* o *publiques* en el servidor:

    $ git push

## 6. Notifica de tus cambios con un *pull request*

¡Bien! Si vamos hasta aquí, lograste publicar tus cambios en
GitHub. La práctica, sin embargo, no ha sido *entregada*: Yo aún no se
nada al respecto. Si ves la página de tu repositorio en GitHub
(https://github.com/alumno01/clase-sistop-2017-01/ substituyendo,
claro, alumno01 por tu nombre de usuario), verás que GitHub te
notifica en el área central que estás *adelantado* al repositorio
central: *This branch is 1 commit ahead of
gwolf/clase-sistop-2017-01*.

En esa misma línea, del lado derecho, haz click en *Pull
request*. GitHub te mostrará un resumen de las diferencias entre mi
versión y la tuya, y si te parece correcta, te permite seleccionar el
botón verde, *Create pull request*.

Describe los cambios que hiciste, confirma tu mensaje, y GitHub te
mostrará que la solicitud ha sido creada.

¡Felicidades! Entregaste la práctica. La pelota ahora está ya en mi
cancha, me toca a mi revisar los cambios.

## 7. Configura tu copia local para seguir al repositorio raiz

A lo largo del cursado de la materia, vamos a seguir usando este
repositorio. Para poder actualizar el repositorio con las
instrucciones relevantes cuando haya nuevas prácticas, tareas o
proyectos, te recomiendo indicarle que estarás siguiendo una *rama
remota*. Pongámosle mi nombre de usuario, `gwolf`:

    $ git remote add --track master gwolf git://github.com/gwolf/clase-sistop-2017-01

Esto significa, *agrega una fuente remota en la dirección mencionada,
siguiendo la rama maestra, y dale localmente el nombre `gwolf`*.

Haz la prueba: un par de días después de haber entregado esta
práctica, entra al directorio de tu repositorio e indícale:

    $ git pull gwolf master

Esta instrucción significa, *trae la rama principal del repositorio
remoto `gwolf`*. Cuando vuelvas a comenzar a trabajar con tu
repositorio, recuerda hacer esto para sincronizar con los últimos
cambios que yo haya enviado.
