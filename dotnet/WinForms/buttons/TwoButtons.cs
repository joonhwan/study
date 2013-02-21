// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:winexe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /out:TwoButton.exe TwoButton.cs\
//   && TwoButton"
// End:
using System;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

class TwoButton : Form
{
	TwoButton()
	{
	}
	void ButtonClicked(Object sender, EventArgs ea)
	{
		Console.WriteLine("버튼 클릭");
	}
	void ButtonKeyDowned(Object sender, KeyEventArgs ea)
	{
		Console.WriteLine("버튼 키보드 누름.");
	}
	readonly Button m_button;

	public static void Main()
	{
		Application.Run(new TwoButton());
	}
}
