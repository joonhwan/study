// compile: csc /target:exe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /out:PartialClass.exe PartialClass.cs && PartialClass.exe
//   && PartialClass.exe"
// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /out:PartialClass.exe PartialClass.cs\
//   && PartialClass.exe"
// End:
//--------------------------------------------------------
// TestArrayInitialization.cs (c) 2006 by Charles Petzold
//--------------------------------------------------------
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

partial class Customer
{
	string name;
	public string Name
	{
		get
		{
			return name;
		}
		set
		{
			OnNameChanging(value);
			name = value;
			OnNameChanged();
		}
	}
	public override string ToString()
	{
		Console.WriteLine("tostring is called.");
		return string.Format("고객:이름={0}", name);
	}
	partial void OnNameChanging(string name);
	partial void OnNameChanged();
}

partial class Customer
{
	partial void OnNameChanging(string name)
	{
		Console.WriteLine("OnNameChanging({0})", name);
	}
	partial void OnNameChanged()
	{
		Console.WriteLine("OnNameChanged()");
	}
}

class PartialClassTest
{
	static void Main()
	{
		Console.WriteLine("Partial 클래스 테스트...");
		Customer customer = new Customer();
		customer.Name = "이준환";
		// Console.WriteLine("객체 정보 : {0}", customer);
	}
}
