// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:ThreadTest /out:ThreadTest.exe ThreadTest.cs			\
//   && ThreadTest arg1 "arg2""
// End:
using System;
using System.Threading;

public class MyWorker
{
	private int m_count;
	public MyWorker()
		: this (10)
	{
	}
	public MyWorker(int count)
	{
		m_count = count;
	}
	public void PrintNumbers()
	{
		for (int i = 0; i < m_count; ++i)
		{
			Random r = new Random();
			var number = r.Next(5);
			// Console.Write("number {0} : ", number);
			Thread.Sleep(100 * r.Next(10));
			Console.Write("{0}, ", i);
		}
		Console.WriteLine();
	}	
}

public class ThreadTest
{
	public static void Main()
	{
		MyWorker worker = new MyWorker(20);
		Thread myThread = new Thread(worker.PrintNumbers);
		myThread.Start();
		// PrintNumbers();
		myThread.Join();
		Console.WriteLine("End.");
	}
}