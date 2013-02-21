using System;

struct Person
{
	public Person(string aName)
		: this (aName, 0)
	{
	}
	public Person(string aName, int anAge)
	{
		name = aName;
		age = anAge;
	}
	public string Name
	{
		get
		{
			return name;
		}
	}
	public int Age
	{
		get
		{
			return age;
		}
	}
	public override string ToString()
	{
		return string.Format("Name:{0}, Age:{1:#00}", name, age);
	}
	string name;
	int age;
}