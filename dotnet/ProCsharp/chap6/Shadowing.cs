using System;

class SuperClass {
	public virtual void DoSomething() {
		Console.WriteLine("Super is doing!");
	}
}
class ChildClass : SuperClass {
	public new void DoSomething() {
		Console.WriteLine("Child is doing!");
	}
}
class ShadowingTest {
	public static void Main() {
		SuperClass obj = new ChildClass();
		obj.DoSomething(); // --> Super is doing!
		((ChildClass)obj).DoSomething(); // --> Child is doing!
	}
}
