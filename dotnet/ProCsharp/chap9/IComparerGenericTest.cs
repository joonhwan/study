// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:IComparerGenericTest /out:IComparerGenericTest.exe IComparerGenericTest.cs			\
//   && IComparerGenericTest arg1 "arg2""
// End:
using System;
using System.Collections.Generic;

class CarNameComparer : IComparer<Car>
{
	int IComparer<Car>.Compare(Car lhs, Car rhs)
	{
		return String.Compare(lhs.Name, rhs.Name);
	}
}
class CarMaxSpeedComparer : IComparer<Car>
{
	int IComparer<Car>.Compare(Car lhs, Car rhs)
	{
		// object형을 car 로 unboxing할 필요가 없다.
		if (lhs.MaxSpeed > rhs.MaxSpeed) {
			return 1; // out-of-order
		} else if (lhs.MaxSpeed < rhs.MaxSpeed) {
			return -1; // in-order
		} else {
			return 0; // same
		}
	}
}
public class Car : IComparable<Car>
{
	public Car(string name, int maxSpeed)
	{
		Name = name;
		MaxSpeed = maxSpeed;
	}
	public string Name { get; set; }
	public int MaxSpeed { get; set; }
	public override string ToString()
	{
		string s = base.ToString();
		return String.Format("{0} / Name:{1}, MaxSpeed:{2}",
							 s, Name, MaxSpeed);
	}
	// 입력 인자가 Object형이 아니라 Car형이 된다.
	int IComparable<Car>.CompareTo(Car otherCar)
	{
		//return carNameComparer.Compare(this, otherCar);
		return carMaxSpeedComparer.Compare(this, otherCar);
	}
	public static IComparer<Car> SortByName {
		get {
			return carNameComparer;
		}
	}
	public static IComparer<Car> SortByMaxSpeed {
		get {
			return carMaxSpeedComparer;
		}
	}
	static IComparer<Car> carNameComparer = new CarNameComparer();
	static IComparer<Car> carMaxSpeedComparer = new CarMaxSpeedComparer();
}

class IComparerGenericTest
{
	public static void Main()
	{
		Car[] carList = new Car[] {
			new Car("acar", 103),
			new Car("zcar", 10),
			new Car("hcar", 100)
		};
		foreach (Car car in carList)
		{
			Console.WriteLine("{0}", car);
		}

		Console.WriteLine("Sorting by MaxSpeed...");
		Array.Sort(carList, Car.SortByMaxSpeed);
		foreach (Car car in carList)
		{
			Console.WriteLine("{0}", car);
		}

		Console.WriteLine("Sorting by Name...");
		Array.Sort(carList, Car.SortByName);
		foreach (Car car in carList)
		{
			Console.WriteLine("{0}", car);
		}
	}
}