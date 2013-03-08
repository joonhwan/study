// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:OperatorOverloadTest /out:OperatorOverloadTest.exe OperatorOverloadTest.cs 	\
//   && OperatorOverloadTest arg1 "arg2""
// End:
using System;

public struct MyInt
{
	int intValue;
	public MyInt(int aValue)
	{
		intValue = aValue;
	}
	public static MyInt operator+ (MyInt lhs, MyInt rhs)
	{
		return new MyInt(lhs.intValue + rhs.intValue);
	}
	public static MyInt operator- (MyInt lhs, MyInt rhs)
	{
		return new MyInt(lhs.intValue - rhs.intValue);
	}
	public override string ToString()
	{
		return string.Format("MyInt:{0}", this.intValue);
	}
}

class OperatorOverloadTest
{
	public static void Main()
	{
		MyInt a = new MyInt(10);
		MyInt b = new MyInt(3);
		MyInt c = a - b;
		MyInt d = a + b;
		MyInt e = a;
		e += b;
		Console.WriteLine("a={0}, b={1}, c={2}, d={3}, e={4}", a,b,c,d,e);
	}
}