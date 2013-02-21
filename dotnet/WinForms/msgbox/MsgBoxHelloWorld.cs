// -*- compile-command:"csc /target:winexe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /out:prog.exe MsgBoxHelloWorld.cs  && prog " -*-
using System;
using System.Threading;
using System.Drawing;
using System.Windows;
using System.Windows.Forms;

class MessageBoxHelloWorld
{
	public static void TestMessageBox()
	{
		string s = "hello";
		s = String.Format("My Environment : {0}", Environment.OSVersion);
		Console.WriteLine(s);
		MessageBox.Show(s, "My First WinForms",
						MessageBoxButtons.OKCancel | MessageBoxButtons.YesNo,
						MessageBoxIcon.Question);
	}
	public static void TestForm()
	{
		Form form = new Form();
		form.Text = "æ»≥Á«œººø‰.";
		form.BackColor = Color.BlanchedAlmond;
		form.Width *= 2;
		form.Height /= 2;
		form.FormBorderStyle = FormBorderStyle.FixedSingle;
		form.Cursor = Cursors.Hand;
		form.StartPosition = FormStartPosition.CenterScreen;n
		form.Paint += new PaintEventHandler(MyPaintEventHandler);
		Application.Run(form);
	}
	public static void MyPaintEventHandler(object objSender, PaintEventArgs pea)
	{
		Form form = (Form)objSender;
		Graphics graphics = pea.Graphics;
		// graphics.Clear(Color.Red);
		graphics.DrawString("π›∞©Ω¿¥œ¥Ÿ.", form.Font, Brushes.Black, 100, 0);
	}
	public static void Main()
	{
		// TestMessageBox();
		TestForm();
	}
}