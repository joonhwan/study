// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /main:InheritTest /out:InheritTest.exe *.cs\
//   && InheritTest"
// End:
using System;
using System.Reflection;
using System.Diagnostics;
using System.Runtime.InteropServices;

partial class Person : IComparable
{
	public int CompareTo(Object obj)
	{
		if (obj==null)
			return 1;

		Person other = obj as Person;
		if (other==null)
		{
			throw new ArgumentException();
		}

		return this.Age - other.Age;
	}
}

class InheritTest
{
	static void Main()
	{
		try
		{
			// object obj = new ExtendedDate();
			// Type objType = obj.GetType();
			// Console.WriteLine("obj type : {0}", objType);
			// foreach (MemberInfo mi in objType.GetMembers())
			// {
			// 	Console.WriteLine("member : {0}", mi);
			// }
			// Date myBirth = obj as Date;
			// if (myBirth != null)
			// {
			// 	myBirth["Year"] = 1971;
			// 	myBirth.Month = 12;
			// 	myBirth.Day = 11;
			// 	Console.WriteLine("My Birth : {0}", obj);
			// }
			string [] roleList = new string [] {
				"Father",
				"Little Daughter",
				"Big Daughter",
				"Mother",
			};

			Person [] personList  = new Person [] {
				new Person("Joonhwan", 43),
				new Person("Eunseo", 5),
				new Person("Seoyeon", 11),
				new Person("Sinyoung", 38),
			};

			// foreach (Person person in personList)
			for (int i=0; i<4; ++i)
			{
				Console.WriteLine("{0} = {1}", personList[i], roleList[i]);
			}
			Console.WriteLine("Sorting...");
			Array.Sort(personList, roleList);
			for (int i=0; i<4; ++i)
			{
				Console.WriteLine("{0} = {1}", personList[i], roleList[i]);
			}
		}
		catch (Exception e)
		{
			Console.WriteLine("Exception! : {0}", e);
		}
	}
}
