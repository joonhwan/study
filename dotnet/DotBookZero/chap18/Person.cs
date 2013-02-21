using System;
using System.Reflection;
using System.Diagnostics;
using System.Runtime.InteropServices;

partial class Person
{
	public Person()
		: this ("joonhwan", 43)
	{
	}
	public Person(string aName, int anAge)
	{
		Name = aName;
		Age = anAge;
	}
	public string Name
	{
		set
		{
			name = value;
		}
		get
		{
			return name;
		}
	}
	public int Age
	{
		set
		{
			age = value;
		}
		get
		{
			return age;
		}
	}
	public override string ToString()
	{
		return string.Format("{0} : {1}", Name, Age);
	}
	private string name;
	private int age;
}