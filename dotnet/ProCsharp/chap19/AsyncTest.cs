// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:AsyncTest /out:AsyncTest.exe AsyncTest.cs			\
//   && AsyncTest arg1 "arg2""
// End:

using System;
using System.Threading;

class Adder
{
	public int Bias { get; set; }
	public int Add (int a, int b)
	{
		Console.WriteLine("Add({1},{2}) [bias={3}]: Thread {0}",
						  Thread.CurrentThread.ManagedThreadId,
						  a, b, this.Bias);
		Thread.Sleep(2000);
		return a + b + this.Bias;
	}
}

class AsyncTest
{
	public delegate int BinaryOp(int a, int b);
	public static void OnDone(IAsyncResult iar)
	{
		Console.WriteLine("OnDone() : Thread {0}", Thread.CurrentThread.ManagedThreadId);
	}
	public static void Main()
	{
		Adder adder = new Adder();
		adder.Bias = 5;
		BinaryOp op = new BinaryOp(adder.Add);
		IAsyncResult iar = op.BeginInvoke(10, 12, OnDone, null);
		int waitCount = 0;
		while (!iar.IsCompleted)
		{
			Console.WriteLine("waiting end {0} time", waitCount++);
			Thread.Sleep(200);
		}
		int result = op.EndInvoke(iar);
		Console.WriteLine("Done. result = {0}", result);
	}
}