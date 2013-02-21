// compile: csc /target:exe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /out:ArrayProp.exe ArrayProp.cs && ArrayProp.exe
//   && ArrayProp.exe"
// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /out:ArrayProp.exe ArrayProp.cs\
//   && ArrayProp.exe"
// End:
//--------------------------------------------------------
// TestArrayInitialization.cs (c) 2006 by Charles Petzold
//--------------------------------------------------------
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

class DateClass
{
	static string[] strMonths = new string[] {
		"January", "Feburary", "March", "April"
	};
	public static string[] MonthName
	{
		get
		{
			return strMonths;
		}
	}
	public string this[int index]
	{
		get
		{
			return strMonths[index];
		}
	}
}
class ArrayProp
{
	static void Main()
	{
		Console.WriteLine("DateClass.Month[2] = {0}", DateClass.MonthName[2]);
		foreach (string monthName in DateClass.MonthName)
		{
			Console.WriteLine("{0}", monthName);
		}

		DateClass date = new DateClass();
		Console.WriteLine("Indexer:{0}", date[2]);
	}
}
