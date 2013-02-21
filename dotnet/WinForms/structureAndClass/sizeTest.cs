// -*- compile-command:"csc /target:exe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /out:sizeTest.exe sizeTest.cs  && sizeTest " -*-
using System;
using System.Drawing;
using System.Windows.Forms;

class SizeTest
{
	static void Main()
	{
		{
			Size size = new Size();
			size.Width = 10;
			size.Height = 20;
			Console.WriteLine("Size(x={0},y={1})", size.Width, size.Height);
		}
		{
			Size size = new Size(30,40);
			Console.WriteLine("Size(x={0},y={1})", size.Width, size.Height);
		}
		{
			Form form = new Form();
			Console.WriteLine("Form Size : {0}", form.Size);
			Size formSize = form.Size;
			formSize.Width = 100;
			Console.WriteLine("Form Size : {0}", formSize);
			Console.WriteLine("Form ClienSize : {0}", form.ClientSize);
			// 프로퍼티의 프로퍼티 설정은 안된단다.
			// form.Size.Width = 140;
			// Console.WriteLine("Form Size : {0}", form.Size);
		}
	}
}