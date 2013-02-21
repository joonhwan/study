// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /out:TestArrayInitialize.exe TestArrayInitialize.cs\
//   && TestArrayInitialize.exe"
// End:
//--------------------------------------------------------
// TestArrayInitialization.cs (c) 2006 by Charles Petzold
//--------------------------------------------------------
using System;
using System.Diagnostics;

class TestArrayInitialization
{
	const int iterations = 10000000;
	static readonly int[] daysCumulativeDays = { 0, 31, 59, 90, 120, 151,
												 181, 212, 243, 273, 304, 334 };
	static readonly string MY_STR_CONST = "CONST";
	public static void Main()
	{
		Stopwatch watch = new Stopwatch();
		Random rand = new Random();
		watch.Start();
		for (int i = 0; i < iterations; i++)
			DayOfYear1(rand.Next(1, 13), rand.Next(1, 29));
		watch.Stop();
		Console.WriteLine("Local array: " + watch.Elapsed);
		watch.Reset();
		watch.Start();
		for (int i = 0; i < iterations; i++)
			DayOfYear2(rand.Next(1, 13), rand.Next(1, 29));
		watch.Stop();
		Console.WriteLine("Static array: " + watch.Elapsed);

		// trying to modify static int []
		daysCumulativeDays[0] = 18;
		foreach (int days in daysCumulativeDays)
		{
			Console.Write("{0}, ", days);
		}
		Console.WriteLine("");

		// MY_STR_CONST = "NOT CONST";
	}
	static int DayOfYear1(int month, int day)
	{
		int[] daysCumulative1 = { 0, 31, 59, 90, 120, 151,
								  181, 212, 243, 273, 304, 334 };
		return daysCumulative1[month - 1] + day;
	}
	static int DayOfYear2(int month, int day)
	{
		return daysCumulativeDays[month - 1] + day;
	}
}