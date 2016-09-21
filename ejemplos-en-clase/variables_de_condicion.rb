#!/usr/bin/ruby
# coding: utf-8
#
# El ejemplo mencionado en el final de la presentación 6, un ejemplo
# NO funcional de manejo de variables de condición. ¿Puedes encontrar
# el error?

# coding: utf-8
class EjemploHilos
  require 'thread'
  def initialize
    @x = 0; @estado = 0
    @mut = Mutex.new
    @cv = ConditionVariable.new
  end
  def run
    @estado = 0
    t1 = Thread.new {f1}
    t2 = Thread.new {f2}
    sleep 0.1; @mut.lock
    @cv.wait(@mut) while (@estado != 2)
    puts 'run. Estado: %d' % [@estado]
    puts '%d ' % @x
    @mut.unlock
  end
  def f1
    sleep 0.1; @mut.lock
    @cv.wait(@mut) while (@estado != 0)
    @x += 3; @estado += 1
    puts 'Saliendo de la parte crítica para F1 - %d; %d' % [@x, @estado]
    @cv.broadcast(@mut)
    @mut.unlock
  end
  def f2
    sleep 0.1; @mut.lock
    @cv.wait(@mut) while (@estado != 1)
    @x *= 2; @estado += 1
    puts 'Saliendo de la parte crítica para F2 - %d; %d' % [@x, @estado]
    @cv.broadcast(@mut)
    @mut.unlock
  end
  e = EjemploHilos.new;10.times{e.run}
end
