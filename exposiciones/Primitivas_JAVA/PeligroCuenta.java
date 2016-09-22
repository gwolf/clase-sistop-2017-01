class CuentaBanco
{
	private int balance = 50;
	
	public int getBalance()
	{
		return balance;
	}
	
	public void retiroBancario(int retiro)
	{
		balance = balance - retiro;
	}
}

public class PeligroCuenta implements Runnable
{
	private CuentaBanco cb = new CuentaBanco();
	
	public void run()
	{
		for(int x=0;x<10;x++)
			hacerRetiro(10);
		if(cb.getBalance()<0)
			System.out.println("La cuenta está sobre girada.");
	}
	
	private synchronized void hacerRetiro(int cantidad)
	{	
		if(cb.getBalance()>=cantidad)
		{
			System.out.println(Thread.currentThread().getName()+" va a hacer un retiro.");
			try
			{
				Thread.sleep(1000);
			} 
			catch (InterruptedException ex)
			{
				ex.printStackTrace();
			}
			
			cb.retiroBancario(cantidad);
			System.out.println(Thread.currentThread().getName()+" realizó el retiro con éxito.");
		}
		else
		{
			System.out.println("No hay suficiente dinero en la cuenta para realizar el retiro Sr. "+Thread.currentThread().getName());
			System.out.println("Su saldo actual es de "+cb.getBalance());
			try
			{
				Thread.sleep(1000);
			}
			catch (InterruptedException ex)
			{
				ex.printStackTrace();
			}
		}
	}
	
	public static void main(String[] args)
	{
		PeligroCuenta pl = new PeligroCuenta();
		Thread uno = new Thread(pl);
		Thread dos = new Thread(pl);
		uno.setName("Bidkar");
		dos.setName("Abraham");
		
		uno.start();
		dos.start();
	}
}
