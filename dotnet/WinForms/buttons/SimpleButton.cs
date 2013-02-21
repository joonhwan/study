// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:winexe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /out:SimpleButton.exe SimpleButton.cs\
//   && SimpleButton"
// End:
using System;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

class SimpleButton : Form
{
	SimpleButton()
	{
		this.Text = "테스트 윈도우";
		this.BackColor = Color.DarkOrange;
		m_button = new Button();
		m_button.Text = "내 버튼";
		m_button.BackColor = Color.Red;
		m_button.Parent = this;
		m_button.Location = new Point(100,50);
		m_button.Click += new EventHandler(ButtonClicked);
		m_button.KeyDown += new KeyEventHandler(ButtonKeyDowned);
	}
	void ButtonClicked(Object sender, EventArgs ea)
	{
		Console.WriteLine("버튼 클릭");
	}
	void ButtonKeyDowned(Object sender, KeyEventArgs ea)
	{
		Console.WriteLine("버튼 키보드 누름.");
	}
	protected Button m_button;

	public static void Main()
	{
		Application.Run(new SimpleButton());
	}
}
