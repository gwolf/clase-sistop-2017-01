
//	VÁZQUEZ ÁLVAREZ ÁNGEL EDUARDO. Hecho con Swift 3

//  Módulos para generar números aleatorios en Linux y macOS
#if os(Linux)
	import Glibc		//	random()
#else
	import Darwin.C		//	arc4random_uniform()
#endif


//  Para describir el nombre de los procesos.
enum Abecedario : Int
{
	case A = 1, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
}


class Proceso : Hashable
{
	let nombre: Abecedario
	let tiempoDeLlegada: Int
	let duracion: Int
	
	var tiempoRestante: Int
	var ejecuciones: Int
	var tiempoInicio: Int
	var tiempoFin: Int
	
	init(nombre: Abecedario, tiempoDeLlegada: Int, duracion: Int)
	{
		self.nombre = nombre
		self.tiempoDeLlegada = tiempoDeLlegada
		self.duracion = duracion
		
		self.tiempoRestante = self.duracion
		self.ejecuciones = 0
		self.tiempoInicio = -1
		self.tiempoFin = -1
	}
	
	init(with proceso: Proceso)
	{
		self.nombre = proceso.nombre
		self.tiempoDeLlegada = proceso.tiempoDeLlegada
		self.duracion = proceso.duracion
		
		self.tiempoRestante = self.duracion
		self.ejecuciones = 0
		self.tiempoInicio = -1
		self.tiempoFin = -1
	}
	
	func descripcion() -> String
	{
		return "\(self.nombre): \(self.tiempoDeLlegada), t = \(self.duracion)"
	}
	
	func descripcion2() -> String
	{
		return "\(self.nombre): \(self.tiempoDeLlegada), t = \(self.duracion), TR: \(self.tiempoRestante)"
	}
	
	var hashValue: Int
	{
		return nombre.hashValue ^ tiempoDeLlegada.hashValue ^ duracion.hashValue
	}
	
	static func == (left: Proceso, right: Proceso) -> Bool
	{
		return left.nombre == right.nombre && left.tiempoDeLlegada == right.tiempoDeLlegada
			&& left.duracion == right.duracion
	}
}


//  Crea la lista de procesos (MÁXIMO 52, agregar letras a la enumeración para aumentar el número)
let MAX_PROCESOS = 5
var listaProcesosFCFS: [Proceso] = []
var listaProcesosRonda: [Proceso] = []
var listaProcesosSPN: [Proceso] = []

//  Crea el primer proceso con números aleatorios
#if os(Linux)
let A = Proceso(nombre: Abecedario(rawValue: 1)!,tiempoDeLlegada: 0, duracion: Int(random() % 10 + 1))
listaProcesosFCFS.append(Proceso(with: A))
listaProcesosRonda.append(Proceso(with: A))
listaProcesosSPN.append(Proceso(with: A))
#else
let A = Proceso(nombre: Abecedario(rawValue: 1)!, tiempoDeLlegada: 0, duracion: Int(arc4random_uniform(10) + 1))
listaProcesosFCFS.append(Proceso(with: A))
listaProcesosRonda.append(Proceso(with: A))
listaProcesosSPN.append(Proceso(with: A))
#endif

//  Crea los procesos restantes con números aleatorios
for i in 2 ... MAX_PROCESOS
{
	let ultimo = listaProcesosFCFS.last!
	
	#if os(Linux)
		let nuevo = Proceso(nombre: Abecedario(rawValue: i)!,
		                    tiempoDeLlegada: ultimo.tiempoDeLlegada + Int(random() % ultimo.duracion),
		                    duracion: Int(random() % 10 + 1))
		listaProcesosFCFS.append(Proceso(with: nuevo))
		listaProcesosRonda.append(Proceso(with: nuevo))
		listaProcesosSPN.append(Proceso(with: nuevo))
		
	#else
		let nuevo = Proceso(nombre: Abecedario(rawValue: i)!,
		                    tiempoDeLlegada: ultimo.tiempoDeLlegada + Int(arc4random_uniform(UInt32(ultimo.duracion))),
		                    duracion: Int(arc4random_uniform(10) + 1))
		
		listaProcesosFCFS.append(Proceso(with: nuevo))
		listaProcesosRonda.append(Proceso(with: nuevo))
		listaProcesosSPN.append(Proceso(with: nuevo))
	#endif
}

/* //EJEMPLO ESTÁTICO
let A = Proceso(nombre: Abecedario(rawValue: 1)!, tiempoDeLlegada: 0, duracion: 3)
let E = Proceso(nombre: Abecedario(rawValue: 5)!, tiempoDeLlegada: 12, duracion: 5)
let C = Proceso(nombre: Abecedario(rawValue: 3)!, tiempoDeLlegada: 3, duracion: 2)
let B = Proceso(nombre: Abecedario(rawValue: 2)!, tiempoDeLlegada: 1, duracion: 5)
let D = Proceso(nombre: Abecedario(rawValue: 4)!, tiempoDeLlegada: 9, duracion: 5)

listaProcesosFCFS.append(Proceso(with: A))
listaProcesosFCFS.append(Proceso(with: E))
listaProcesosFCFS.append(Proceso(with: C))
listaProcesosFCFS.append(Proceso(with: B))
listaProcesosFCFS.append(Proceso(with: D))

listaProcesosRonda.append(Proceso(with: A))
listaProcesosRonda.append(Proceso(with: E))
listaProcesosRonda.append(Proceso(with: C))
listaProcesosRonda.append(Proceso(with: B))
listaProcesosRonda.append(Proceso(with: D))

listaProcesosSPN.append(Proceso(with: A))
listaProcesosSPN.append(Proceso(with: E))
listaProcesosSPN.append(Proceso(with: C))
listaProcesosSPN.append(Proceso(with: B))
listaProcesosSPN.append(Proceso(with: D))*/

func imprimeListaDeProcesos()
{
	var suma = 0
	print("\n-----\t\tLISTA DE PROCESOS\t\t-----")
	for proceso in listaProcesosFCFS
	{
		suma += proceso.duracion
		print("Proceso \(proceso.descripcion())")
	}
	print("\t>> Total = \(suma)")
}


class FCFS
{
	var listaDeProcesos: [Proceso]
	
	var tiemposDeRespuesta: [Proceso: Double] = [:]
	var tiemposDeEspera: [Proceso: Double] = [:]
	var tiemposDePenalizacion: [Proceso: Double] = [:]
	
	var orden: [Abecedario] = []
	
	init(listaDeProcesos: [Proceso])
	{
		self.listaDeProcesos = listaDeProcesos
		
		//  Ordena los procesos ascendentemente en tiempo de llegada.
		self.listaDeProcesos.sort { $0.tiempoDeLlegada < $1.tiempoDeLlegada }
	}
	
	func imprimeResultados()
	{
		var tiempoDeRespuesta: Double = 0
		var tiempoDeEspera: Double = 0
		var tiempoDePenalizacion: Double = 0
		var tiempoPromedio: Double = 0
		
		print("\n-----\t\tALGORITMO FCFS\t\t-----")
		for proceso in listaDeProcesos
		{
			print("\(proceso.nombre): T = \(tiemposDeRespuesta[proceso]!), E = \(tiemposDeEspera[proceso]!), P = \(tiemposDePenalizacion[proceso]!)")
			
			tiempoDeRespuesta += tiemposDeRespuesta[proceso]! / Double(listaDeProcesos.count)
			tiempoDeEspera += tiemposDeEspera[proceso]! / Double(listaDeProcesos.count)
			tiempoDePenalizacion += tiemposDePenalizacion[proceso]! / Double(listaDeProcesos.count)
			tiempoPromedio += Double(proceso.duracion) / Double(listaDeProcesos.count)
		}
		print("Orden:", terminator: "")
		for nombre in orden
		{
			print(nombre, terminator: "")
		}
		
		print("\n\t>> Totales: t = \(tiempoPromedio), T = \(tiempoDeRespuesta), E = \(tiempoDeEspera), P = \(tiempoDePenalizacion)")
	}
	
	func ejecutar()
	{
		var tiempoTranscurrido: Double = 0
		
		for proceso in listaDeProcesos
		{
			orden.append(proceso.nombre)
			tiempoTranscurrido += Double(proceso.duracion)
			tiemposDeRespuesta[proceso] =  tiempoTranscurrido - Double(proceso.tiempoDeLlegada)
			tiemposDeEspera[proceso] = tiemposDeRespuesta[proceso]! - Double(proceso.duracion)
			tiemposDePenalizacion[proceso] = tiemposDeRespuesta[proceso]! / Double(proceso.duracion)
		}
		imprimeResultados()
	}
}

class Ronda
{
	var listaDeProcesos: [Proceso]
	
	var tiemposDeRespuesta: [Proceso: Double] = [:]
	var tiemposDeEspera: [Proceso: Double] = [:]
	var tiemposDePenalizacion: [Proceso: Double] = [:]
	
	var orden: [Abecedario] = []
	
	let quantum: Int
	
	var listaDeProcesosListos: [Proceso] = []
	var listaTerminados: [Proceso] = []
	
	init(listaDeProcesos: [Proceso], quantum: Int)
	{
		self.listaDeProcesos = listaDeProcesos
		self.quantum = quantum
		
		for proceso in listaDeProcesos
		{
			tiemposDeRespuesta[proceso] = 0
			tiemposDeEspera[proceso] = 0
			tiemposDePenalizacion[proceso] = 0
		}
		
		//  Ordena los procesos ascendentemente en tiempo de llegada.
		self.listaDeProcesos.sort { $0.tiempoDeLlegada < $1.tiempoDeLlegada }
	}
	
	func imprimeResultados()
	{
		var tiempoDeRespuesta: Double = 0
		var tiempoDeEspera: Double = 0
		var tiempoDePenalizacion: Double = 0
		var tiempoPromedio: Double = 0
		
		print("\n-----\t\tALGORITMO RONDA (quantum = \(self.quantum))\t\t-----")
		for proceso in listaDeProcesos
		{
			print("\(proceso.nombre): T = \(tiemposDeRespuesta[proceso]!), E = \(tiemposDeEspera[proceso]!), P = \(tiemposDePenalizacion[proceso]!)")
			
			tiempoDeRespuesta += tiemposDeRespuesta[proceso]! / Double(listaDeProcesos.count)
			tiempoDeEspera += tiemposDeEspera[proceso]! / Double(listaDeProcesos.count)
			tiempoDePenalizacion += tiemposDePenalizacion[proceso]! / Double(listaDeProcesos.count)
			tiempoPromedio += Double(proceso.duracion) / Double(listaDeProcesos.count)
		}
		print("Orden:", terminator: "")
		for nombre in orden
		{
			print(nombre, terminator: "")
		}
		
		print("\n\t>> Totales: t = \(tiempoPromedio), T = \(tiempoDeRespuesta), E = \(tiempoDeEspera), P = \(tiempoDePenalizacion)")
	}
	
	func buscar(proceso: Proceso, in lista: [Proceso]) -> Bool
	{
		for x in lista
		{
			if proceso.nombre == x.nombre
			{
				return true
			}
		}
		return false
	}
	
	func ejecutar()
	{
		var tiempoTranscurrido: Double = 0
		
		while listaTerminados.count < MAX_PROCESOS
		{
			for proceso in listaDeProcesos
			{
				if (Double(proceso.tiempoDeLlegada) <= tiempoTranscurrido) && (proceso.tiempoRestante > 0)
				{
					if proceso.tiempoInicio == -1
					{
						proceso.tiempoInicio = Int(tiempoTranscurrido)
					}
					listaDeProcesosListos.append(proceso)
				}
			}
			
			self.listaDeProcesosListos.sort { $0.ejecuciones < $1.ejecuciones }
			
			while listaDeProcesosListos.isEmpty == false
			{
				let procesoActual = listaDeProcesosListos.removeFirst()
				
				orden.append(procesoActual.nombre)
				//print(procesoActual.nombre, " inicio mi ejecución en: ", tiempoTranscurrido)
				
				if procesoActual.tiempoRestante >= quantum
				{
					procesoActual.tiempoRestante -= quantum
					procesoActual.ejecuciones += 1
					
					tiempoTranscurrido += Double(quantum)
				}
				else
				{
					tiempoTranscurrido += Double(procesoActual.tiempoRestante)
					//let tiempo = Double(procesoActual.tiempoRestante)
					procesoActual.tiempoRestante = 0
					procesoActual.ejecuciones += 1
					
					
					
					procesoActual.tiempoFin = Int(tiempoTranscurrido)
				}
				
				if(procesoActual.tiempoRestante == 0)
				{
					procesoActual.tiempoFin = Int(tiempoTranscurrido)
					listaTerminados.append(procesoActual)
				}
				
			}
		}
		
		//	Calcula T, E y P para todos los procesos.
		for proceso in listaDeProcesos
		{
			// print(proceso.nombre, "Tiempo INICIO: ", proceso.tiempoInicio, "Tiempo FIN: ", proceso.tiempoFin)
			tiemposDeRespuesta[proceso] = Double(proceso.tiempoFin - proceso.tiempoDeLlegada)
			tiemposDeEspera[proceso] = Double((proceso.tiempoFin - proceso.tiempoDeLlegada) - proceso.duracion)
			tiemposDePenalizacion[proceso] = tiemposDeRespuesta[proceso]! / Double(proceso.duracion)
		}
		
		imprimeResultados()
	}
}

class SPN
{
	var listaDeProcesos: [Proceso]
	
	var tiemposDeRespuesta: [Proceso: Double] = [:]
	var tiemposDeEspera: [Proceso: Double] = [:]
	var tiemposDePenalizacion: [Proceso: Double] = [:]
	
	var orden: [Abecedario] = []
	
	var procesosListos: [Proceso] = []
	var procesosTerminados: [Proceso] = []
	
	init(listaDeProcesos: [Proceso])
	{
		self.listaDeProcesos = listaDeProcesos
		
		for proceso in listaDeProcesos
		{
			tiemposDeRespuesta[proceso] = 0
			tiemposDeEspera[proceso] = 0
			tiemposDePenalizacion[proceso] = 0
		}
		
		//  Ordena los procesos ascendentemente en tiempo de llegada.
		self.listaDeProcesos.sort { $0.tiempoDeLlegada < $1.tiempoDeLlegada }
	}
	
	func imprimeResultados()
	{
		var tiempoDeRespuesta: Double = 0
		var tiempoDeEspera: Double = 0
		var tiempoDePenalizacion: Double = 0
		var tiempoPromedio: Double = 0
		
		print("\n-----\t\tALGORITMO SPN\t\t-----")
		for proceso in listaDeProcesos
		{
			print("\(proceso.nombre): T = \(tiemposDeRespuesta[proceso]!), E = \(tiemposDeEspera[proceso]!), P = \(tiemposDePenalizacion[proceso]!)")
			
			tiempoDeRespuesta += tiemposDeRespuesta[proceso]! / Double(listaDeProcesos.count)
			tiempoDeEspera += tiemposDeEspera[proceso]! / Double(listaDeProcesos.count)
			tiempoDePenalizacion += tiemposDePenalizacion[proceso]! / Double(listaDeProcesos.count)
			tiempoPromedio += Double(proceso.duracion) / Double(listaDeProcesos.count)
		}
		
		print("Orden:", terminator: "")
		for nombre in orden
		{
			print(nombre, terminator: "")
		}
		
		print("\n\t>> Totales: t = \(tiempoPromedio), T = \(tiempoDeRespuesta), E = \(tiempoDeEspera), P = \(tiempoDePenalizacion)")
	}
	
	
	func ejecutar()
	{
		var tiempo: Double = 0
		
		while procesosTerminados.count < MAX_PROCESOS
		{
			//	Busca el proceso de menor duración que ya haya empezado.
			for proceso in listaDeProcesos
			{
				if (Double(proceso.tiempoDeLlegada) <= tiempo) && (proceso.tiempoRestante > 0)
				{
					procesosListos.append(proceso)
				}
			}
			//	Ordena los procesos listos en duración
			procesosListos.sort { $0.duracion < $1.duracion }
			
			//	Pone los procesos terminados en la lista de terminados.
			while procesosListos.count > 0
			{
				let proceso = procesosListos.removeFirst()
				
				orden.append(proceso.nombre)
				
				tiempo += Double(proceso.duracion)
				proceso.tiempoRestante = 0
				proceso.tiempoFin = Int(tiempo)
				procesosTerminados.append(proceso)
				
				procesosListos.removeAll()
			}
		}
		
		//	Calcula T, E y P para todos los procesos.
		for proceso in listaDeProcesos
		{
			tiemposDeRespuesta[proceso] = Double(proceso.tiempoFin - proceso.tiempoDeLlegada)
			tiemposDeEspera[proceso] = Double((proceso.tiempoFin - proceso.tiempoDeLlegada) - proceso.duracion)
			tiemposDePenalizacion[proceso] = tiemposDeRespuesta[proceso]! / Double(proceso.duracion)
		}
		
		imprimeResultados()
	}
}

//  Ejecución del programa.
imprimeListaDeProcesos()

let fcfs = FCFS(listaDeProcesos: listaProcesosFCFS)
fcfs.ejecutar()

let ronda = Ronda(listaDeProcesos: listaProcesosRonda, quantum: 4)
ronda.ejecutar()

let spn = SPN(listaDeProcesos: listaProcesosSPN)
spn.ejecutar()
