// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:CompareTest /out:CompareTest.exe CompareTest.cs		\
//   && CompareTest arg1 "arg2""
// End:

using System;

public class MyPoint : IComparable<MyPoint>
{
	public int X  { get; set; }
	public int Y  { get; set; }
	public int CompareTo(MyPoint other)
	{
		int v = this.X.CompareTo(other.X);
		if (0==v) 
			return this.Y.CompareTo(other.Y);
		return v;
	}
	public static bool operator < (MyPoint lhs, MyPoint rhs)
	{
		return lhs.CompareTo(rhs) < 0;
	}
	public static bool operator > (MyPoint lhs, MyPoint rhs)
	{
		return lhs.CompareTo(rhs) > 0;
	}
	public static bool operator <= (MyPoint lhs, MyPoint rhs)
	{
		return lhs.CompareTo(rhs) <= 0;
	}
	public static bool operator >= (MyPoint lhs, MyPoint rhs)
	{
		return lhs.CompareTo(rhs) >= 0;
	}
	public override string ToString()
	{
		return string.Format("(X={0}, Y={1})", X, Y);
	}

}

class CompareTest
{
	public static void Main()
	{
		MyPoint p1 = new MyPoint {
			X = 10,
			Y = 20,
		};;
		MyPoint p2 = new MyPoint {
			X = 30,
			Y = 5,
		};

		Console.WriteLine("p1={0}, p2={1}, p1 > p2 ({2}), p1 <= p2 ({3})", p1, p2, p1 > p2, p1 <= p2);
	}
}