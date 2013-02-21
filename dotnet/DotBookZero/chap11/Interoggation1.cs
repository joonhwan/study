// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /out:Interoggation1.exe Interoggation1.cs\
//   && Interoggation1.exe"
// End:
using System;

class MyClass
{
	public static readonly int MY_CONST = 10;
	//static readonly string MY_STRING_CONST = "Hello World";
	public const string MY_STRING_CONST = "Hello Const World";

	public static void HandleNumber(long value)
	{
		Console.WriteLine("Long:{0}", value);
	}
	public static void HandleNumber(double value)
	{
		Console.WriteLine("Double:{0}", value);
	}
}

class PassByReference
{
	public static void AlterInteger(ref int i)
	{
		Console.WriteLine("Before Process : {0}", i);
		i = 55;
		Console.WriteLine("After Process : {0}", i);
	}
	public static void AlterArray(int [] myArray)
	{
		myArray[0] = 15;
	}
	public static void AlterArrayRef(ref int [] myArray)
	{
		myArray[0] = 15;
	}
	public static void AllocArray(int [] myArray)
	{
		myArray = new int [] { 1000, 2000, 3000 };
	}
	public static void AllocArrayRef(ref int [] myArray)
	{
		myArray = new int [] { 1000, 2000, 3000 };
	}
	public static void DumpArray(string desc, int [] myArray)
	{
		Console.Write(desc);
		for (int i=0; i<myArray.Length; ++i)
		{
			Console.Write("{0}, ", myArray[i]);
		}
		Console.WriteLine("");
	}
}

class Prog
{
	public static void Main()
	{
		int intValue = 10;
		float floatValue = 10.0F;
		MyClass.HandleNumber(intValue);
		MyClass.HandleNumber(floatValue);

		Console.WriteLine("MyConst={0}, MyStringConst={1}",
						  MyClass.MY_CONST, MyClass.MY_STRING_CONST);

		int i = 10;
		PassByReference.AlterInteger(ref i);
		Console.WriteLine("Finally : {0}", i);

		int [] myArray = new int [] { 401, 301, 20, 30, 40 };
		PassByReference.DumpArray("Before AlterArray:", myArray);
		PassByReference.AlterArray(myArray);
		PassByReference.DumpArray("After AlterArray:", myArray);

		myArray[0] = 1000;
		PassByReference.DumpArray("Before AlterArrayRef:", myArray);
		PassByReference.AlterArrayRef(ref myArray);
		PassByReference.DumpArray("After AlterArrayRef:", myArray);

		PassByReference.DumpArray("Before AllocArray:", myArray);
		PassByReference.AllocArray(myArray);
		PassByReference.DumpArray("After AllocArray:", myArray);

		myArray[0] = 1000;
		PassByReference.DumpArray("Before AllocArrayRef:", myArray);
		PassByReference.AllocArrayRef(ref myArray);
		PassByReference.DumpArray("After AllocArrayRef:", myArray);
	}
}