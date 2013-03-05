// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll		\
//   /main:SortedSetTest /out:SortedSetTest.exe SortedSetTest.cs	\
//   && SortedSetTest arg1 "arg2""
// End:
using System;
using System.Collections.Generic;

class SortByNameComparer : IComparer<Person>
{
	int IComparer<Person>.Compare(Person lhs, Person rhs)
	{
		return String.Compare(lhs.Name, rhs.Name);
	}
}

class SortByAgeComparer : IComparer<Person>
{
	int IComparer<Person>.Compare(Person lhs, Person rhs)
	{
		if (lhs.Age < rhs.Age)
			return -1; // in order
		else if (lhs.Age > rhs.Age)
			return 1; // out of order
		else
			return 0; // same
	}
}

class Person : IComparable<Person>
{
	public Person(string name, int age)
	{
		this.Name = name;
		this.Age = age;
	}
	public string Name { get; set; }
	public int Age { get; set; }
	int IComparable<Person>.CompareTo(Person other)
	{
		return SortByName.Compare(this, other);
	}
	static SortByNameComparer sortByName = new SortByNameComparer();
	static SortByAgeComparer sortByAge = new SortByAgeComparer();
	public IComparer<Person> SortByName {
		get {
			return sortByName;
		}
	}
	public IComparer<Person> SortByAge {
		get {
			return sortByAge;
		}
	}
	public override string ToString()
	{
		return String.Format("Name:{0}, Age:{1}",
							 Name, Age);
	}
}

class SortedSetTest
{
	public static void Main()
	{
		//SortedSet<Person> personSet = new SortedSet<Person>() {
		SortedSet<Person> personSet = new SortedSet<Person>(new SortByAgeComparer()) {
			new Person("준환", 42),
			new Person("신영", 38),
			new Person("서연", 11),
			new Person("은서", 5)
		};
		foreach (Person person in personSet)
		{
			Console.WriteLine("{0}", person);
		}
		Console.WriteLine("Sorted..");
		foreach (Person person in personSet)
		{
			Console.WriteLine("{0}", person);
		}
	}
}