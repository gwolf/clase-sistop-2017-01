require "rubygems"
require "zip/zipfilesystem"

=begin
Función que lista los contenidos del volumen
zip:apuntador al archivo
ruta: string que es la ruta al archivo
=end
def listar(zip, ruta='')
	  if zip.file.file? ruta#si la ruta hace referencia a una archivo
	    puts "#{ruta}".gsub(/volumec:/,"")#imprime el nombre del archivo sin mostrar el nombre de lo que seria la raiz
	  else#si no
	    unless ruta.empty?#si el directorio referido no esta vacio
	      ruta += '/'#agregale una raiz 
	    end
	    zip.dir.foreach(ruta) do |arch|#Bloque que itera sobre los archivos presentes en el directorio
	      listar(zip, ruta + arch)#se llama a la funcion de manera recursiva para revisar todos los directorios
		  #Esta funcion funcionaria incluso si fuera permitido crear directorios y no solo archivos
	    end
	  end
end
=begin
Funcion que checa si existe el archivo y la carpeta dentro de el
si regresa false el programa no se ejecutará
=end
	
def check
	if File.exist?("HardDrive.zip")#Funcion checa si existe el archivo
	Zip::ZipFile.open('HardDrive.zip') do |zip_arc|#Bloque en el que zip_arc fungira como el objeto que apuntara al archivo abierto
		if zip_arc.file.directory?"volumec:"#Revisa si existe en el directorio el archivo volumec:
			return true# si se cumple regresa true
		else
			return false#si no regresa false
		end
	end
	else
		return false# si el archivo no existe regresa false
	end
end

=begin
Función que crea un archivo nuevo sin ningun contenido 	
zip:recibe el apuntador a archivo zip 
nombre:nombre del archivo
=end
def nuarch(zip,nombre)
	ruta="volumec:/"
	if nombre=="/" || nombre == "" #sie el nombre es / o cadena vacia o nulo
		puts "Nombre no disponible"#
	else
	  begin
			nuevoarchi=zip.file.open(ruta+nombre, 'w') #abre el nuevo archivo, lo crea
			nuevoarchi.write("")#escribe una cadena vacia en el 
			nuevoarchi.close()#cierra el archivo recien creado
		rescue
			puts "No se pudo crear el archivo"	
		end
	end
end
=begin
Función que borra un archivo recibe:
zip: apuntador al archivo zip
nombre:nombre del archivo que desea borrarse
=end
def deletes(zip,nombre)
	ruta="volumec:/"
	if nombre=="/" || nombre==""#si el nombre del archivo es la raiz o es vacío 
		puts("No tienes permisos para esto compa")
	else
		begin# manejo posibles excepciones
			zip.file.delete(ruta+nombre)#comando para eliminar un archivo del diretorio, recibe una ruta 
		rescue # si se presenta una excepción
			puts "No existe el archivo"
		end
			
	end
end
=begin
Función que permite la lectura de un archivo y lo muestra en la consola como si fuera una especie de "cat"
las secciones son muy parecidas a la de creacion de un archivo a excepción de que aqui se hace solo lectura,recibe: 
zip:apuntador a archivo zip
nombre: nombre del archivo a leer
=end
def readf(zip,nombre)
	ruta="volumec:/"
	if nombre=="/" || nombre==""
		puts("No tienes permisos para esto compa")
	else
		begin
			a=zip.file.read(ruta+nombre)# se lee el archivo y se pasa el resultado a un objeto
			puts a #imprime el resultado de la lectura
		rescue
			puts "No existe el archivo"
		end
	end
end
=begin
Funcion de escritura a un archivo, esta permite reasignar contenido de un archivo lo que significa que lo sobreescribira.
Esta función también crea un archivo nuevo si se coloca nombre de un archivo no existente, pero con un contenido recibe:
Muy parecida a nuarch pero esta permite insertar contenido para el archivo
zip: apuntador a archivo zip
nombre: nombre del archivo en el que se quiere escribir
=end
def writeto(zip,nombre)
	ruta="volumec:/"
	if nombre=="/" || nombre==""
		puts("No tienes permisos para esto compa")
	else
		begin
			zip1=zip.file.open(ruta+nombre, 'w')
			puts "Introduce el contenido para escribir en el archivo"
			cont=gets.chomp#lee el contenido
			zip1.write(cont)#lo escribe al archivo 
			zip1.close()#cierra el archivo
		rescue
			puts "El archivo no existe"
		end	
		end
	
	
	end
=begin
	
=end

=begin
Función que permite agregar texto a un archivo respetando su contenido. Primero meustra su contenido y luego pide agergar el texto deseado
este será escrito al final del documento. Tiene una estructura muy parecida a las demas funciones , recibe:
zip:apuntador a archivo zip
nombre:nombre del archivo
=end
def addto(zip,nombre)
	ruta="volumec:/"
	if nombre=="/" || nombre==""
		puts("No tienes permisos para esto compa")
	else
		begin
			innercont=zip.read(ruta+nombre)#lee el documento
			puts "El contenido es :"#imprime su cntenido
			puts innercont#imprime el contenido del archivo
			puts "Introduce el contenido para añadir en el archivo"
			cont=gets.chomp#recibe contenido a aagregar al final del archivo
			arch=zip.file.open(ruta+nombre, 'w')#abre archivo para escritura
			arch.write(innercont+cont)#escribe el contenido anterior y el nuevo sobre el archivo
			arch.close()#cierra archivow
		rescue
			puts"No existe el archivo"
		end

	end
end

=begin
Función que valida el comando escrito recibe
command: cadena introducida por el usario, que sera el comando
list:arreglo de cadenas, las cuales son los comandos validos
=end
def validate(command,list)

	if list.include?command#si la lista contiene el comando regresa true
		return true
	else
		puts"comando no valido"#si no imprime comando no valido
	end
end
=begin
Función que limpia la pantalla de la shell para la comodidad de uno B)
=end
def clear
	puts ("\e[H\e[2J")#este comando lo saqué de internet 
end
=begin
Función dependiendo del comando llama a la función correspondiente utilizadon un case, recibe:
zip:apuntadora a archivo zip
command:cadena de caracteres introducida por el usuario, representa el comando
nombre: nombre del archivo sobre el que se queire operar
=end
def task(zip,command,nombre)
	case command
		when "clr"
			clear
		when "newfile"
			nuarch(zip,nombre)
		when "ld"
			listar(zip,"volumec:")
		when "writeto"
			writeto(zip,nombre)
		when "delete"
			deletes(zip,nombre)
		when "addto"
			addto(zip,nombre)
		when "readf"
			readf(zip,nombre)
		when "ayuda"
			ayuda
	end
end
=begin
Función que despliega la ayuda del programa e imprime todos los comandos y lo qye hacen
=end
def ayuda
	puts"Este es el menú de ayuda "
	puts
	puts"Lista de comandos"
	puts
	puts"ld: Lista los archivos del sistema "
	puts"clr: limpia la consola "
	puts"exit:cierra el programa "
	puts"newfile [nombrearchivo]: crea un archivo con el nombre que sustituyas en [nombrearchivo] "
	puts"writeto [nombrearchivo]: Escribe a un archivo con el nombre que sustituyas en [nombrearchivo], este también crea un archivo pero con contenido "
	puts"delete [nombrearchivo]: Elimina el archivo del nombre que sustituyas en [nombrearchivo] "
	puts"addto [nombrearchivo]: Muestra el contenido del archivo que sustituyas en [nombrearchivo], y permite que le agregues más contenido "
	puts"readf [nombrearchivo]: Muestra el contenido del archivo que sustituyas en [nombrearchivo] "
	puts
end

=begin
Funcion principal que realiza Lo principal del programa	

	
=end
def main
	puts "\e[H\e[2J"#limpia la pantalla
	if check#checa si existen los archivos
		commands=["exit","clr","newfile","writeto","addto","readf","delete","ld","ayuda"]#arreglo de comandos
		command=""#cadena que introducirá el usuario
		nombre=""#nombre del archivo qeu introducira el usuario
		Zip::ZipFile.open('HardDrive.zip',Zip::ZipFile::CREATE) do |zip| #bloque utilizando el resultado de la funcion como zip
		puts("Porfavor ingresa ayuda para ver los comandos si es tu primera vez en este sitio místico")
			while command!="exit"#mientras el comando sea distinto de exit
			print "[deusex@machine]$"
			command,nombre=gets.chomp.split#lee una cadena y la parte por los espacios , la primera mitad se asigna a comando y la segunda a nombre
			
				if validate(command,commands) #si se valida el comando
					task(zip,command,nombre)#ejecutar tarea
				end
			end
		end	
	else 
		puts "El volumen no esta disponible"#si no existen lso archivos termina
	end
end

main