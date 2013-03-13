// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:MyDisposable /out:MyDisposable.exe MyDisposable.cs	\
//   && MyDisposable arg1 "arg2""
// End:
using System;

class MyDisposable : IDisposable
{
	public void Dispose()
	{
		Console.WriteLine("***** In Dispose ! ********");
	}
	public void DoSomething()
	{
		Console.WriteLine("MyDisposable is doing something.");
	}
	static void Main()
	{
		Console.WriteLine("* Fun with Dispose *");

		MyDisposable obj = new MyDisposable();
		obj.DoSomething();
		obj.Dispose();
	}
}