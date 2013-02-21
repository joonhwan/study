// -*- compile-command:"csc /target:exe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /out:pointTest.exe pointTest.cs  && pointTest " -*-
using System;
using System.Drawing;

class PointTest
{
	static void Main()
	{
		{
			Point pt = new Point();
			pt.X = 10;
			pt.Y = 20;
			Console.WriteLine("Point(x={0},y={1})", pt.X, pt.Y);
		}
		{
			Point pt = new Point(30,40);
			Console.WriteLine("Point(x={0},y={1})", pt.X, pt.Y);
		}
		{
			Point pt = new Point(0x1000010);
			Console.WriteLine("Point(x={0},y={1})", pt.X, pt.Y);
			Console.WriteLine("{0}", pt);
		}
	}
}