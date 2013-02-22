using System;

abstract class Shape
{
	public Shape()
		: this ("A Shape")
	{
	}
	public Shape(string petName)
	{
		PetName = petName ?? "A Non-null Shape";
	}
	public abstract void Draw();
	public string PetName { get; set; }
}

class Circle : Shape
{
	public Circle()
		: this (10, "A Circle")
	{
	}
	public Circle(int radius, string petName = null)
		: base (petName)
	{
		Radius = radius;
	}
	public override void Draw()
	{
		Console.WriteLine("Drawing Circle (name:{0}, radius:{1}).",
						  this.PetName, this.Radius);
	}
	public int Radius { get; set; }
}

class ThreeDCircle : Circle
{
	public ThreeDCircle()
		: this (12, "A 3D Circle")
	{
	}
	public ThreeDCircle(int radius, string PetName)
		: base (radius, PetName)
	{
	}
	public override void Draw()
	{
		Console.WriteLine("Hey!");
	}
}

class Hexagon : Shape
{
	public Hexagon(int edgeLength, string petName)
		: base (petName)
	{
		EdgeLength = edgeLength;
	}
	public override void Draw()
	{
		Console.WriteLine("Drawing Hexagon(name:{0}, edgeLen:{1}",
						  this.PetName, this.EdgeLength);
	}
	public int EdgeLength { get; set; }
}

class ShapeTest
{
	public static void Main()
	{
		Console.WriteLine("-- AbstractClassTest() --");
		// Shape s = new Shape();
		Circle circle = new Circle();
		circle.Draw();
		Shape s = new Circle(25);
		s.Draw();
	}
}