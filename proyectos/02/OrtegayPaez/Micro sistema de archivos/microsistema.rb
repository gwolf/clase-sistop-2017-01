require "rubygems"
require "zip/zipfilesystem"

=begin
Función que lista los contenidos del volumen
=end
def listar(zip, path='')
	  if zip.file.file? path
	    puts "#{path}".gsub(/volumec:/,"")
	  else
	    unless path.empty?
	      path += '/'
	    end
	    zip.dir.foreach(path) do |filename|
	      listar(zip, path + filename)
	    end
	  end
end
=begin
Funcion que checa si existe el archivo y la carpeta dentro de el
si no lo hace el programa se detendra
=end
	
def check
	if File.exist?("HardDrive.zip")
	Zip::ZipFile.open('HardDrive.zip') do |zip_arc|
		if zip_arc.file.directory?"volumec:"
			return true
		else
			return false
		end
	end
	else
		return false
	end
end

def nuarch(zip,name)
	path="volumec:/"
	if name=="/" || name == ""
		puts "El archivo necesita un nombre"
  else
	  
		nuevoarchi=zip.file.open(path+name, 'w') 
		nuevoarchi.write("")

	end
end

def deletes(zip,name)
	path="volumec:/"
	if name=="/" || name==""
		puts("No tienes permisos para esto compa")
	else
		begin
			zip.file.delete(path+name)
		rescue #=> exception
			puts "no existe el archivo"
		end
			
	end
end

def readf(zip,name)
	path="volumec:/"
	a=zip.file.read(path+name)
	puts a
end

def writeto(zip,name)
	path="volumec:/"
	if name=="/" || name==""
		puts("No tienes permisos para esto compa")
	else
		zip.file.open(path+name, 'w') do |zip1|
		puts "Introduce el contenido para escribir en el archivo"
		cont=gets.chomp
		zip1.write(cont)
		end
	
	
	end
	end

def addto(zip,nombre)
	path="volumec:/"
	if nombre=="/" || nombre==""
		puts("No tienes permisos para esto compa")
	else
		begin
			innercont=zip.read(path+nombre)
			puts "El contenido es :"
			puts innercont
			puts "Introduce el contenido para añadir en el archivo"
			cont=gets.chomp
			arch=zip.file.open(path+nombre, 'w')
			arch.write(innercont+cont) 
			arch.close()
		rescue
			puts"No existe el archivo"
		end

	end
end
def validate(command,list)

	if list.include?command
		return true
	else
		puts"comando no valido"
	end
end


def clear
	puts "\e[H\e[2J"
end

def task(zip,command,name)
	case command
		when "clr"
			clear
		when "newfile"
			nuarch(zip,name)
		when "ld"
			listar(zip,"volumec:")
		when "writeto"
			writeto(zip,name)
		when "delete"
			deletes(zip,name)
		when "addto"
			addto(zip,name)
		when "readf"
			readf(zip,name)
		when "ayuda"
			ayuda
	end
end

def ayuda
	puts("Este es el menú de ayuda")
	puts("ld: Lista los archivos del sistema")
	puts("clr: limpia la consola ")
	puts("exit:cierra el programa ")
	puts("newfile [filename]: crea un archivo con el nombre que sustituyas en [filename]")
	puts("writeto [filename]: Escribe a un archivo con el nombre que sustituyas en [filename]: este también crea un archivo pero con contenido que escribas")
	puts("delete [filename]: Elimina el archivo del nombre que sustituyas en [filename]")
	puts("addto [filename]: Muestra el contenido del archivo que sustituyas en [filename], y permite que le agregues más contenido")
	puts("readf [filename]: Muestra el contenido del archivo que sustituyas en [filename]")
end

	puts "\e[H\e[2J"
	if check
		
		commands=["exit","clr","newfile","writeto","addto","readf","delete","ld","ayuda"]
		string=""
		command=""
		name=""
		zip= Zip::ZipFile.open('HardDrive.zip',Zip::ZipFile::CREATE) do |zip|
		puts("Porfavor ingresa ayuda para ver los comandos si es tu primera vez en este sitio místico")
			while command!="exit"
			print "[deusex@machine]$"
			command,name=gets.chomp.split
				if validate(command,commands) 
					task(zip,command,name)
				end
			end
		end	
	else 
		puts "El volumen no esta disponible"
	end