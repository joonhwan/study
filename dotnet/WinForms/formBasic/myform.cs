// -*- compile-command:"csc /target:winexe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /out:prog.exe myform.cs  && prog " -*-
using System;
using System.Drawing;
using System.Windows.Forms;

class Prog
{
	static void Main()
	{
		Application.Run(new MyInheritedForm());
	}
}

class MyForm : Form
{
	public MyForm()
	{
		this.Text = "안녕하세요.";
		this.BackColor = Color.BlanchedAlmond;
		this.Width *= 2;
		this.Height /= 2;
		this.FormBorderStyle = FormBorderStyle.FixedSingle;
		this.Cursor = Cursors.Hand;
		this.StartPosition = FormStartPosition.CenterScreen;
	}
	protected override void OnPaint(PaintEventArgs pea)
	{
		base.OnPaint(pea);
		Graphics graphics = pea.Graphics;
		graphics.DrawString("이준환입니다.", this.Font, Brushes.Black, 50, 50);
	}
}

class MyInheritedForm : MyForm
{
	public MyInheritedForm()
	{
		this.Paint += new PaintEventHandler(MyEventHandler);
	}
	static void MyEventHandler(Object objSender, PaintEventArgs pea)
	{
		MyForm form = (MyForm)objSender;
		Graphics graphics = pea.Graphics;
		graphics.DrawString("명신영입니다.", form.Font, Brushes.Black, 50, 100);
	}
}