// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll			\
//   /main:GenericDelegateTest /out:GenericDelegateTest.exe GenericDelegateTest.cs \
//   && GenericDelegateTest arg1 "arg2""
// End:
using System;

class GenericDelegateTest
{
	public delegate void MyGenericDelegate<T>(T arg);
	public static void Main()
	{
		var intFunction = new MyGenericDelegate<int>(functionForInt);
		var stringFunction = new MyGenericDelegate<string>(functionForString);
		var doubleFunction = new MyGenericDelegate<double>(functionForAny);

		intFunction(18);
		stringFunction("hello");
		doubleFunction(18.1818);
	}
	static void functionForAny<T>(T arg)
	{
		Console.WriteLine("functionFor {0} ({1})", arg.GetType(), arg);
	}
	static void functionForInt(int arg)
	{
		Console.WriteLine("functionForInt({0})", arg);
	}
	static void functionForString(string arg)
	{
		Console.WriteLine("functionForString({0})", arg);
	}
}