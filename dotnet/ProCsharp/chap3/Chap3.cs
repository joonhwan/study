// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /main:Chap3 /out:Chap3.exe *.cs\
//   && Chap3 arg1 \"./arg2\" argA argZ"
// End:
using System;
using System.Linq;
using System.Collections.Generic;

enum MyEnum
{
	Farther = 0,
	Mother = 100,
	Daughter,
	Son,
}

class Chap3
{
	public static int Main(string[] args)
	{
		// EnumTest();
		// LetterTest();
		// CheckedTest();
		// LinqQueryInts();
		// SwitchOnString();
		// CalcAvg(10, 1, 2, 3, 4, 5, 6, 7, 8, 9);
		// VarArrayTest();
		// ObjectArrayTest();
		EvaluateEnum(MyEnum.Farther);
		return 0;
	}
	static void EvaluateEnum(Enum e)
	{
		Type enumType = e.GetType();
		Console.WriteLine("Enum Type Name: {0} (underlying type={1}",
						  enumType.Name, Enum.GetUnderlyingType(enumType));
		var enumValueList = Enum.GetValues(enumType);
		Console.WriteLine("--> has {0} values.", enumValueList.Length);
		foreach (var enumValue in enumValueList)
		{
			Console.WriteLine("Name:{0}, Value:{0:D}", enumValue);
		}
	}
	static void ObjectArrayTest()
	{
		object[] myObjects = new object[3];
		myObjects[0] = 10;
		myObjects[1] = new DateTime(1971,12,11);
		myObjects[2] = "hello";
		foreach (object obj in myObjects)
		{
			Console.WriteLine("object = {0}(type:{1})",
							  obj, obj.GetType());
		}
	}
	static void VarArrayTest()
	{
		var data = new[] { 1, 10, 100, 10000000000000 };
		data[2] = 10000;
		Console.WriteLine("typeof(b) = {0}", data.GetType());
		foreach (var i in data)
		{
			Console.WriteLine("i = {0}", i);
		}

		var b = new[] { 1, 4.3, 10 };
		Console.WriteLine("typeof(b) = {0}", b.GetType());
		foreach (var i in b)
		{
			Console.WriteLine("i = {0}", i);
		}
		
	}
	static void CalcAvg(double multiplier, params double [] values)
	{
		double avg = 0;
		foreach (double value in values)
		{
			avg += (value * multiplier);
		}
		avg = avg / values.Length;
		Console.WriteLine("average = {0}", avg);
	}
	static void EnumTest()
	{
		MyEnum e = MyEnum.Farther;
		Console.WriteLine("Enum value : {0}", e.ToString());
		Console.WriteLine("Underlying Enum : {0}", Enum.GetUnderlyingType(e.GetType()));
		Array enumData = Enum.GetValues(e.GetType());
		for (int i = 0; i < enumData.Length; ++i)
		{
			object o = enumData.GetValue(i);
			int value = (int)o;
			Console.WriteLine("{0} = {1:D}", o.ToString(), value);
		}
		int value18 = 18;
		Console.WriteLine("int.ToString() = {0}", value18.ToString());
	}
	static void LetterTest()
	{
		Console.WriteLine("'a' isLetter ? : {0}", char.IsLetter('a'));
	}
	static void CheckedTest()
	{
		try
		{
			checked
			{
				int myInt = 100000;
				var myShort = checked (myInt);
				Console.WriteLine("myShort = {0}", myShort);
			}
		} catch (Exception ex)
		{
			Console.WriteLine(ex.Message);
		}
	}

	static void LinqQueryInts()
	{
		// LINQ !
		int [] numbers = {10, 20, 30, 40, 50 };
		var subset = from i in numbers where i < 30 select i;
		foreach (int number in subset)
		{
			Console.WriteLine("{0}", number);
		}
	}
	static void SwitchOnString()
	{
		string lang = "c#";
		switch (lang)
		{
		case "c#":
			Console.WriteLine("detected c#");
			break;
		case "c++":
			Console.WriteLine("detected c++");
			break;
		default:
			Console.WriteLine("detected unknown");
			break;
		}
	}
	static void ListT_Test()
	{

		List<Person> persons = new List<Person>(20);
		Console.WriteLine("persons count = {0}", persons.Count);
		Console.WriteLine("persons capacity = {0}", persons.Capacity);

		persons.Add (new Person("Joonhwan", 43));
		persons.Add (new Person("Sinyoung", 38));
		persons.Add (new Person("Seoyeon", 11));
		persons.Add (new Person("Eunseo", 5));
		// persons.Add ("Gaeon");

		Console.WriteLine("persons count = {0}", persons.Count);
		Console.WriteLine("persons capacity = {0}", persons.Capacity);

		foreach (var person in persons)
		{
			Console.WriteLine("--> {0}", person);
		}
	}
}