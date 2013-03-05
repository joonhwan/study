// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll		\
//   /main:DefaultValueT /out:DefaultValueT.exe DefaultValueT.cs	\
//   && DefaultValueT arg1 "arg2""
// End:
using System;
using System.Collections.Generic;

public struct Point<T>
{
	public T X;
	public T Y;
	public Point(T aX, T aY)
	{
		X = aX;
		Y = aY;
	}
	public override string ToString()
	{
		return string.Format("({0}, {1})", X, Y);
	}
}

class DefaultValueT
{
	public static void Main()
	{
		var intPoint = new Point<int>(10, 20);
		Console.WriteLine(intPoint);
		var defaultPoint = default (Point<int>);
		Console.WriteLine(defaultPoint);
		int defaultInt = default (int);
		Console.WriteLine(defaultInt);
	}
}