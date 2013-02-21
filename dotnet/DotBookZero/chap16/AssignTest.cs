// compile: csc /target:exe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /out:AssignTest.exe AssignTest.cs && AssignTest.exe
//   && AssignTest.exe"
// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /out:AssignTest.exe AssignTest.cs\
//   && AssignTest.exe"
// End:
//--------------------------------------------------------
// TestArrayInitialization.cs (c) 2006 by Charles Petzold
//--------------------------------------------------------
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

struct PointStruct
{
	public PointStruct(int x, int y)
	{
		this.x = x;
		this.y = y;
	}
	public int x;
	public int y;
	public override string ToString()
	{
		return string.Format("x={0},y={1}", this.x, this.y);
	}
	public override int GetHashCode()
	{
		return (this.x << 8) | (this.y & 0x0000FFFF);
	}
	public override bool Equals(object obj)
	{
		return Equals((PointStruct)obj);
	}
	public bool Equals(PointStruct other)
	{
		return x==other.x && y==other.y;
	}
	public static bool operator==(PointStruct lhs, PointStruct rhs)
	{
		return lhs.Equals(rhs);
	}
		public static bool operator!=(PointStruct lhs, PointStruct rhs)
	{
		return !lhs.Equals(rhs);
	}
}

class PointClass
{
	public PointClass(int x, int y)
	{
		this.x = x;
		this.y = y;
	}
	public int x;
	public int y;
	public override string ToString()
	{
		return string.Format("x={0},y={1}", this.x, this.y);
	}
}

class StructTest
{
	public static void Main()
	{
		// Console.WriteLine("sizeof(IntPtr)={0}", sizeof (PointClass));
		{
			PointStruct ps1 = new PointStruct(10, 11);
			PointStruct ps2 = ps1;

			ps2.x = 20;
			ps2.y = 21;

			Console.WriteLine("sizeof(ps1)={0}", Marshal.SizeOf(ps1));
			Console.WriteLine("ps1 = {0}", ps1);
			Console.WriteLine("ps2 = {0}", ps2);
			Console.WriteLine("ps2.Equals(ps1) = {0}", ps2.Equals(ps1));
			Console.WriteLine("ps2 == ps1 = {0}", (ps2 == ps1));
		}
		{
			PointClass pc1 = new PointClass(10, 11);
			PointClass pc2 = new PointClass(10, 11);

			pc2.x = 20;
			pc2.y = 21; // 추가 주석

			Console.WriteLine("sizeof(ps1)={0}", Marshal.SizeOf(pc1));
			Console.WriteLine("pc1 = {0}", pc1);
			Console.WriteLine("pc2 = {0}", pc2);
			Console.WriteLine("pc2.Equals(pc1) = {0}", pc2.Equals(pc1));
			Console.WriteLine("pc2 == pc1 = {0}", (pc2 == pc1));
		}
		{
			PointClass pc1 = new PointClass(10, 11);
			PointClass pc2 = pc1;

			pc2.x = 20;
			pc2.y = 21;

			Console.WriteLine("pc1 = {0}", pc1);
			Console.WriteLine("pc2 = {0}", pc2);
			Console.WriteLine("pc2.Equals(pc1) = {0}", pc2.Equals(pc1));
			Console.WriteLine("pc2 == pc1 = {0}", (pc2 == pc1));
		}
	}
}