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

def check
	if File.exist?("HardDrive.zip")
	Zip::ZipFile.open('HardDrive.zip') do |zip_arc|
		if zip_arc != "volumec:"
			return true
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
		nuevoarchi.close()
	end
end

def delete(zip,name)
	path="volumec:/"
	if name=="/" || name==""
		puts("No tienes permisos para esto compa")
	else
	zip.file.delete(path+name)
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
		puts "Introduce el contenido para escribir en el archivo"
		cont=gets.chomp
		arch=zip.file.open(path+name, 'w') 
		arch.write(cont)
		arch.close()
	
	end
	end

def addto(zip,nombre)
	path="volumec:/"
	if nombre=="/" || nombre==""
		puts("No tienes permisos para esto compa")
	else
		innercont=zip.read(path+nombre)

		puts "Introduce el contenido para añadir en el archivo"
		cont=gets.chomp
		arch=zip.file.open(path+nombre, 'w')
		arch.write(innercont+cont) 
		arch.close()

	end
end
	if check
	zip= Zip::ZipFile.open('HardDrive.zip')

		nuarch(zip,"gato.txt")
		writeto(zip,"gato.txt")
		addto(zip,"gato.txt")
		readf(zip,"gato.txt")
		delete(zip,"gato.txt")
		listar(zip,"volumec:")

	
	else 
		puts "El volumen no esta disponible"
	end