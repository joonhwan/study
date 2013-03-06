// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:LambdaMultiTest /out:LambdaMultiTest.exe LambdaMultiTest.cs 	\
//   && LambdaMultiTest arg1 "arg2""
// End:
using System;

class SimpleMath {
	public delegate void MathMessage(string msg, int result);
	public event MathMessage mmDelegate;
	public event Action addHook;

	public int Add (int a, int b) {
		int c = a + b;
		if (mmDelegate != null)
		{
			mmDelegate("Adding has completed", c);
		}
		if (addHook != null)
		{
			addHook();
		}
		return c;
	}
}
class LambdaMultiTest {
	public static void Main() {
		SimpleMath sm = new SimpleMath();
		// 인자의 형이 암시적으로 결정
		sm.mmDelegate += ( (msg, result) => {
				Console.WriteLine(msg);
				Console.WriteLine("result : {0}", result);
			});
		// 인자의 형이 명시적으로 지정
		sm.mmDelegate += ( (string msg, int result) => {
				Console.WriteLine("2:{0}", msg);
				Console.WriteLine("2:result : {0}", result);
			});

		// 인자 갯수가 다름 (오류!!!)
		// sm.mmDelegate += ( (string msg) => {
		// 		Console.WriteLine("2:{0}", msg);
		// 	});

		// 인자 갯수가 일부만 명시적(오류!!!)
		// sm.mmDelegate += ( (string msg, result) => {
		// 		Console.WriteLine("2:{0}", msg);
		// 		Console.WriteLine("2:result : {0}", result);
		// 	});

		sm.addHook += ( () => {
				Console.WriteLine("AddWork is hooked!");
			});

		sm.Add (10, 11);
	}
}
