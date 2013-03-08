// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll		\
//   /main:ExtensionTest /out:ExtensionTest.exe ExtensionTest.cs	\
//   && ExtensionTest arg1 "arg2""
// End:
using System;

// namespace 내에 정의된 Extension Method 를
// 사용하기 위해 꼭 필요한 using!!!!!
using MyExtension;

namespace MyExtension
{

// Extension Method 는 반드시 static class 에 정의되어야 함.
public static class MyExtensionClass
{
	// 모든 Extension Method 는 결국 static임.
	// (static class 에 정의되므로....)
	public static void DoSomeExtension(
			// 이 메소드는 System.Object 에 추가되는 메소드임을 알림
			this Object obj,
			// 실제 메소드의 첫번째 인자
			int additionalArg
		)
	{
		Console.WriteLine("Type:{0}, AdditionalArg:{1}",
						  obj.GetType().Name, additionalArg);
	}
}

}

class ExtensionTest
{
	public static void Main()
	{
		int myInt = 10;
		myInt.DoSomeExtension(12);
	}
}