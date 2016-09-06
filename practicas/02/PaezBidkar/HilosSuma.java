//Programa realizado por Páez Lampón Bidkar Herson
public class HilosSuma implements Runnable
{
	static int suma[]={0,0,0,0,0};
		
	public void run()
	{
		try
		{
			if(Thread.currentThread().getName().equals("suma"))
			{
				System.out.printf("\nLa suma total es: %d",sumarArreglo());
			}
			else
			{
			
				int hilo = Integer.parseInt(Thread.currentThread().getName());
				int value = 100*hilo;
				for (int i=(value+1);i<=(value+100);i++)
					suma[hilo]+=i;
			
			}
		}catch(Exception ex)
		{

		}		
	}

	public static int sumarArreglo()
	{
		int total=0;
		for(int i=0;i<suma.length;i++)
		{
			total+=suma[i];
		}
		return total;
	}

	public static void main(String []args)
	{
		HilosSuma uno = new HilosSuma();
		Thread hilo1 = new Thread(uno,"0");
		hilo1.start();
		HilosSuma dos = new HilosSuma();
		Thread hilo2 = new Thread(dos,"1");
		hilo2.start();
		HilosSuma tres = new HilosSuma();
		Thread hilo3 = new Thread(tres,"2");
		hilo3.start();
		HilosSuma cuatro = new HilosSuma();
		Thread hilo4 = new Thread(cuatro,"3");
		hilo4.start();
		HilosSuma cinco = new HilosSuma();
		Thread hilo5 = new Thread(cinco,"4");
		hilo5.start();
		
		HilosSuma total = new HilosSuma();
		Thread hilototal = new Thread(total,"suma");
		hilototal.start();
		try
		{
			hilototal.sleep(100);
		}
		catch(Exception e)
		{
			
		}

	}

}