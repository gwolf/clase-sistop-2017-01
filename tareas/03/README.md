# Tarea: Algoritmos de planificación

Vimos varios algoritmos de planificación de procesos en clase. De
estos algoritmos, les pido que –para el *martes 11 de octubre*–
implementen tres. Un par de tips al respecto:

- Los más sencillos: *FCFS*/*FIFO*, ronda (*RR*), el más corto a
  continuación (*SPN*)
- Los más interesantes: Retroalimentación multinivel (*FB*), Ronda
  egoísta (*SRR*)
- Otros que les puede entretener implementar: *HPRN*, *SPN* preventivo
  (*PSPN*), *Lotería*

Elijan los tres que quieran implementar. Claro está, para implementar
el planificador, se sobreentiende que únicamente será un simulador —
No hace falta que hagan cambios de contexto, manejen multihilos ni
nada por el estilo. Por poner un ejemplo, la siguiente es una
implementación completa de FIFO; está escrita a propósito de forma
bastante *idiomática* en Ruby; no espero que usen el mismo *dialecto*
que yo, pero sí que vean la longitud total de programa esperado:

    #!/usr/bin/ruby
    class Proceso
      attr_reader(:name, :arrive, :length)
      def initialize(name, arrive, length)
        @name = name
        @arrive = arrive
        @length = length
      end
    end
    class ProcList < Array; end
    class FIFOSched
      def initialize(proclist)
        @plist = proclist
        @done = []
        @results = {}
        @time = 0
      end
      def go
        # Start by printing out a summary
        @plist.sort_by {|p| p.arrive}.each do |proc|
          print "%s: %d, t=%d; " % [proc.name, proc.arrive, proc.length]
        end
        puts '(Tot: %d)' % @plist.map{|p| p.length}.reduce(:+)
        run
        # Results: Average T, E and P across all of the processes
        puts "FCFS: T=%2.2f, E=%2.2f, P=%2.2f" %
             [ @results.values.map{|v| v[:T].to_f}.reduce(:+) / @results.values.size,
               @results.values.map{|v| v[:E].to_f}.reduce(:+) / @results.values.size,
               @results.values.map{|v| v[:P].to_f}.reduce(:+) / @results.values.size
               ]
      end
      private
      def run
        @plist.sort_by {|p| p.arrive}.each do |proc|
          @results[proc.name] = {}
          @results[proc.name][:E] = @time - proc.arrive
          @results[proc.name][:T] = @results[proc.name][:E] + proc.length
          @results[proc.name][:P] = @results[proc.name][:T] / proc.length.to_f
          @time += proc.length
          puts "  %s: T=%d, E=%d, P=%2.2f; now t=%d" %
               [proc.name, @results[proc.name][:T], @results[proc.name][:E],
                @results[proc.name][:P], @time]
        end
      end
    end
	
	# Generate the list of processes we will run
    plist = ProcList.new
    # First process should start at t=0
    plist << Proceso.new('A', 0, (1 + 10*rand).to_i)
    (10*rand).to_i.times do |i|
      last = plist.last
      plist << Proceso.new( ('A'.ord + i + 1).chr, # 'B', 'C', etc.
                            # Ensure no empty spaces are left: Processes should overlap
                            last.arrive + (rand(last.length).to_i),
                            (1 + 10*rand).to_i
                          )
    end
	
	# And go with the simulation!
    fifo = FIFOSched.new(plist)
    fifo.go

Mi ejemplo cubre únicamente un algoritmo, y las estructuras podrían no
ser adecuadas para ningún otro (¿o sí?)

Ejecuten el programa varias veces, generando aleatoriamente un
conjunto de procesos a comparar, para que les indique los resultados,
como en el siguiente ejemplo:

	$ compara_planif 
    - Primera ronda: A: 0, t=3; B: 1, t=5; C: 3, t=2; D: 9, t=5; E: 12, t=5 (tot:20) 
     FCFS: T=6.2, E=2.2, P=1.74 
     RR1: T=7.6, E=3.6, P=1.98 
     RR4: T=7.2, E=3.2, P=1.88 
     SPN: T=5.6, E=1.6, P=1.32 
    - Segunda ronda A: 0, t=5; B: 3, t=3; C: 3, t=7; D: 7, t=4; E:8, t=4 (tot:23) 
     (...) 

Presenten junto con el código el resultado de varias ejecuciones; les
sugiero que verifiquen manualmente algunas de ellas para asegurarse
que implementa correctamente al algoritmo en cuestión.

Un refinamiento, en caso de que les interese "pulirse" con el
programa, es que el programa presente gráficamente cada una de las
ejecuciones, como podría ser:

    - Segunda ronda A: 0, t=5; B: 3, t=3; C: 3, t=7; D: 7, t=4; E:8, t=4 (tot:23) 
     FCFS: AAAAABBBCCCCCCCDDDDEEEE T=... E=... P=... 
     RR(1): AAABCABCDEABCDECDECDECC T=... E=... P=... 
    (...) 

O como les resulte más sencillo; puede ayudarlos a comprender el
resultado de la planificación a la hora de verificarlo.

Entreguen la tarea de forma *individual* en este directorio.
