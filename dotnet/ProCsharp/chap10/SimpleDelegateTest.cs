// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:SimpleDelegateTest /out:SimpleDelegateTest.exe SimpleDelegateTest.cs 	\
//   && SimpleDelegateTest arg1 "arg2""
// End:
using System;
using System.Collections.ObjectModel;

public delegate int BinaryOp(int x, int y);

class SimpleMath {
	public static int Add (int a, int b) {
		return a + b;
	}
	public static int Subtract(int a, int b) {
		return a - b;
	}
}
class SimpleDelegateTest {
	public static void Main() {
		BinaryOp b = new BinaryOp(SimpleMath.Add);
		// b(10,5) 하면 실제로는 b.Invoke(15,5) 가 수행
		Console.WriteLine("b(10,5) = {0}",b(10,5)); // = 15
		b = new BinaryOp(SimpleMath.Subtract);
		Console.WriteLine("b(10,5) = {0}", b(10,5)); // = 5
	}
}
