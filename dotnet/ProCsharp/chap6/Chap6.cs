// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /main:Chap6 /out:Chap6.exe *.cs\
//   && Chap6 arg1 \"./arg2\" argA argZ"
// End:
using System;
using System.Linq;
using System.Collections.Generic;

class Chap6
{
	public static int Main(string[] args)
	{
		// ShapeTest.Main();
		// ShadowingTest.Main();
		AsIsKeywordTest();
		return 0;
	}
	public static void AsIsKeywordTest()
	{
		Shape shape = new Circle();
		try {
			Hexagon hex = (Hexagon)shape;
		} catch (InvalidCastException e) {
			// ¿©±â µé¾î¿È
			Console.WriteLine("invalid cast. {0}", e.Message);
		}
		Hexagon asHex = shape as Hexagon;
		if (asHex == null) {
			// ¿©±â µé¾î¿È
			Console.WriteLine("asHex is null.");
		}
		if (!(shape is Hexagon)) {
			// ¿©±â µé¾î¿È
			Console.WriteLine("shape is not Hexagon object!");
		}
	}
}