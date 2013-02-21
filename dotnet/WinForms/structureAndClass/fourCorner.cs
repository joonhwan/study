// -*- compile-command:"csc /target:exe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /out:fourCorner.exe fourCorner.cs  && fourCorner " -*-
using System;
using System.Drawing;
using System.Windows.Forms;

class FourCornerTest
{
	static void Main()
	{
		Application.Run(new FourCorner());
	}
}

class FourCorner : Form
{
	public FourCorner()
	{
		this.ResizeRedraw = true;
	}
	// protected override void OnResize(EventArgs ea)
	// {
	// 	base.OnResize(ea);
	// 	this.Invalidate();
	// }
	protected override void OnPaint(PaintEventArgs pea)
	{
		Graphics graphics = pea.Graphics;
		graphics.Clear(Color.Aqua);

		drawByMeasureString(pea.Graphics);
		// drawByStringFormat(pea.Graphics);
	}
	protected void drawByMeasureString(Graphics graphics)
	{
		Rectangle cr = this.ClientRectangle;
		string s = "Á¤Áß¾Ó";
		SizeF textSize = graphics.MeasureString(s, this.Font);
		graphics.DrawString(s, this.Font, new SolidBrush(this.ForeColor),
							cr.X+cr.Width/2-textSize.Width/2,
							cr.Y+cr.Height/2-textSize.Height/2);
	}
	protected void drawByStringFormat(Graphics graphics)
	{
		Rectangle cr = this.ClientRectangle;

		Brush brush = new SolidBrush(this.ForeColor);
		graphics.DrawString("ÁÂ»ó´Ü", this.Font, brush, cr.Left, cr.Top);

		StringFormat sf = new StringFormat();
		sf.Alignment = StringAlignment.Far;
		sf.LineAlignment = StringAlignment.Far;
		graphics.DrawString("¿ìÇÏ´Ü", this.Font, brush, cr.Right, cr.Bottom, sf);

		sf.Alignment = StringAlignment.Center;
		sf.LineAlignment = StringAlignment.Center;
		graphics.DrawString("Á¤È®È÷ Áß¾Ó?", this.Font, brush, cr.X + cr.Width/2, cr.Y+cr.Height/2, sf);
	}
}