// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /main:PointyTest /out:IPointy.exe IPointy.cs\
//   && IPointy arg1 "arg2""
// End:
using System;

public interface IPointy
{
	int GetNumberOfPoints();
	string Name { get; set; }
}

class Pointy : IPointy
{
	public int GetNumberOfPoints()
	{
		return 12;
	}
	public string Name { get; set; }
}

class NonPointy
{
	public int GetNumberOfPoints()
	{
		return 12;
	}
	public string Name { get; set; }
}

class PointyTest
{
	public static void DoSomethingOnPointy(IPointy pointy)
	{
		Console.WriteLine("pointy : {0}", pointy.Name);
	}
	public static void Main()
	{
		Pointy pointy = new Pointy();
		pointy.Name = "Hello";

		NonPointy nonpointy = new NonPointy();
		nonpointy.Name = "NonPointy Hello";

		DoSomethingOnPointy(pointy);
		// DoSomethingOnPointy(nonpointy);
	}
}