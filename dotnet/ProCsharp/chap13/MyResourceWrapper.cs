// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll			\
//   /main:MyResourceWrapper /out:MyResourceWrapper.exe MyResourceWrapper.cs \
//   && MyResourceWrapper arg1 "arg2""
// End:
using System;

class MyResourceWrapper
{
	public MyResourceWrapper()
	{
		Console.WriteLine("ctor MyResourceWrapper.");
	}
	~MyResourceWrapper()
	{
		Console.WriteLine("dtor MyResourceWrapper.");
	}
	public static void TestClass()
	{
		Console.WriteLine("creating wrapper...");
		MyResourceWrapper wrapper = new MyResourceWrapper();
		Console.WriteLine("using wrapper...");
	}
	public static void Main()
	{
		TestClass();
		Console.WriteLine("after called TestClass...");
	}
}