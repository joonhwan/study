// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:CustomGenericMethodTest /out:CustomGenericMethodTest.exe CustomGenericMethodTest.cs MyGeneric.cs	\
//   && CustomGenericMethodTest arg1 "arg2""
// End:
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using MyGenerics;

class Person
{
	public Person(string name = null, int? age=null)
	{
		this.Name = name ?? "무명씨";
		this.Age = age ?? 1;
	}
	public string Name { get; set; }
	public int Age { get; set; }
	public override string ToString()
	{
		return String.Format("Name:{0}, Age:{1}",
							 Name, Age);
	}
	public void Swap<T>(ref T a, ref T b)
	{
		Console.WriteLine("Instance Swaping object of {0} type", a.GetType());
		T temp = a;
		a = b;
		b = temp;
	}
}

class CustomGenericMethodTest
{
	public static void Main()
	{
		var nonamer = new Person(age:21);
		Console.WriteLine(nonamer);

		var consumer = new Person("준환", 42);
		var incomer = new Person("신영", 38);

		Console.WriteLine("consumer={0}, incomer={1}",
						  consumer, incomer);

		Console.WriteLine("changing..");
		var swapper = new Person("스와퍼");
		Console.WriteLine(swapper);

		swapper.Swap(ref consumer, ref incomer);
		Console.WriteLine("consumer={0}, incomer={1}",
						  consumer, incomer);

		
		MyGeneric.Swap<Person>(ref consumer, ref incomer);

		Console.WriteLine("consumer={0}, incomer={1}",
						  consumer, incomer);

		int a = 10;
		int b = 20;
		Console.WriteLine("a={0}, b={1}", a, b);
		MyGeneric.Swap<int>(ref a, ref b);
		Console.WriteLine("a={0}, b={1}", a, b);
	}
}
