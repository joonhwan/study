// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll			\
//   /main:ExplicitInterfaceImpl /out:ExplicitInterfaceImpl.exe ExplicitInterfaceImpl.cs \
//   && ExplicitInterfaceImpl arg1 "arg2""
// End:
using System;

public interface IGdiDrawer {
	void Draw();
}
public interface IQtDrawer {
	void Draw();
}
public interface IWxDrawer {
	void Draw();
}

class UltraDrawer : IGdiDrawer, IQtDrawer, IWxDrawer
{
	void IGdiDrawer.Draw() {
		Console.WriteLine("IGdiDrawer.Draw()");
	}
	void IQtDrawer.Draw() {
		Console.WriteLine("IQtDrawer.Draw()");
	}
	void IWxDrawer.Draw() {
		Console.WriteLine("IWxDrawer.Draw()");
	}
}

class ExplicitInterfaceImpl {
	static void DrawQt(IQtDrawer drawer) {
		drawer.Draw();
	}
	public static void Main() {
		UltraDrawer drawer = new UltraDrawer();
		DrawQt(drawer);
	}
}