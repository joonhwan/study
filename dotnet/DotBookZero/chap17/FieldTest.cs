// compile: csc /target:exe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /out:FieldTest.exe FieldTest.cs && FieldTest.exe
//   && FieldTest.exe"
// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /out:FieldTest.exe FieldTest.cs\
//   && FieldTest.exe"
// End:
//--------------------------------------------------------
// TestArrayInitialization.cs (c) 2006 by Charles Petzold
//--------------------------------------------------------
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

class PropertyClass
{
	
}

class FieldTest
{
	static void Main()
	{
		Console.WriteLine("test...");
	}
}
