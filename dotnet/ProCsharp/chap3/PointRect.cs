using System;

class Point
{
	public int X { get; set; }
	public int Y { get; set; }
}
class Rectangle
{
	public Point TopLeft { get; set; }
	public Point BottomRight { get; set; }
	public Rectangle()
	{
		TopLeft = new Point();
		TopLeft = new Point();
	}
	public void PrintInfo()
	{
		Console.WriteLine("({0},{1}) ~ ({2},{3})",
						  TopLeft.X, TopLeft.Y,
						  BottomRight.X, BottomRight.Y);
	}
}
