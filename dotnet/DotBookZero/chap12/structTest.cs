// compile: csc /target:exe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /out:structTest.exe structTest.cs && structTest.exe
//   && structTest.exe"
// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /out:structTest.exe structTest.cs\
//   && structTest.exe"
// End:
//--------------------------------------------------------
// TestArrayInitialization.cs (c) 2006 by Charles Petzold
//--------------------------------------------------------
using System;
using System.Diagnostics;

struct MyDate
{
	public int year;
	public int month;
	public int day;
	// public MyDate()
	// {
	// 	year = month = day = 1;
	// }
	public MyDate(int year, int month, int day)
	{
		this.year = year;
		this.month = month;
		this.day = day;
	}
	public override string ToString()
	{
		return String.Format("Date:{0}/{1}/{2}", year, month, day);
	}
}

class StructTest
{
	public static void Main()
	{
		string myString = "Hello";
		Console.WriteLine("MyString : {0}", myString);
		{
			MyDate myBirth = new MyDate(1971,12,11);
			Console.WriteLine("My Birthday : {0}",
							  myBirth);
		}
		{
			MyDate yourBirth;
			yourBirth = new MyDate();
			yourBirth.year = 1975;
			// yourBirth.month = 09;
			// yourBirth.day = 08;
			Console.WriteLine("Her Birthday : {0}",
							  yourBirth);
		}
	}
}