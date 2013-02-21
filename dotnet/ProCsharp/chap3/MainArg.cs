// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /main:MainArgTest /out:MainArgTest.exe MainArgTest.cs\
//   && MainArgTest arg1 \"./arg2\" argA argZ"
// End:
using System;

class MainArgTest
{
	public static int Main(string[] args)
	{
		Console.WriteLine("Pure args...");
		foreach (string arg in args)
		{
			Console.WriteLine("Arg:{0}", arg);
		}

		Console.WriteLine("CommandLine Args...");
		foreach (string arg in Environment.GetCommandLineArgs())
		{
			Console.WriteLine("Arg:{0}", arg);
		}
		return 0;
	}
}