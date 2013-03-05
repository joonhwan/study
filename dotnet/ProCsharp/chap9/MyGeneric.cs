using System;

namespace MyGenerics
{

public static class MyGeneric
{
	public static void Swap<T>(ref T a, ref T b)
	{
		Console.WriteLine("Swaping object of {0} type", a.GetType());
		T temp = a;
		a = b;
		b = temp;
	}
}

}
