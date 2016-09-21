#!/usr/bin/ruby
# coding: utf-8
#
# El ejemplo mencionado en el final de la presentación 6, un ejemplo
# NO funcional de manejo de variables de condición — Ahora
# funcionando, gracias al trabajo en grupo y a la buena vista
# particularmente de Alberto Díaz! :-D

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
    puts '%d ' % @x
    @mut.unlock
  end
  def f1
    sleep 0.1; @mut.lock
    @cv.wait(@mut) while (@estado != 1)
    @x += 3; @estado += 1
    @cv.broadcast
    @mut.unlock
  end
  def f2
    sleep 0.1; @mut.lock
    @cv.wait(@mut) while (@estado != 0)
    @x *= 2; @estado += 1
    @cv.broadcast
    @mut.unlock
  end
  e = EjemploHilos.new;10.times{e.run}
end
