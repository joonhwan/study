using System;

namespace StructInheritTest
{

// ¿Ã∑±∞« æ»µ .
struct Point
{
	Point(int aX, int aY) {
		x = aX; y = aY;
	}
	// // error CS0573: 'StructInheritTest.Point.x': cannot have
	// instance field initializers in structs
	// 
	// public int x = 0;
	public int x;
	public int y;
}
// struct Point3d : Point
// {
// 	public int z;
// }

} // StructInheritTest

// --------------------------------------

namespace ClassInheritTest
{

class Point
{
	// warning CS0649: Field 'ClassInheritTest.Point.x' is never
	// assigned to, and will always have its default value 0
	//
	// 	public int x;
	public int x = 0;
	public int y = 0;
}
class Point3d : Point
{
	public int z = 0;
}

} // ClassInheritTest