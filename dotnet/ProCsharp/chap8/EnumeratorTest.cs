// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll		\
//   /main:EnumeratorTest /out:EnumeratorTest.exe EnumeratorTest.cs	\
//   && EnumeratorTest arg1 "arg2""
// End:
using System;
using System.Collections;

public class Car
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
}

// public class Garage: IEnumerable , IEnumerator
// {
// 	Car[] carArray;
// 	public Garage()
// 	{
// 		carArray = new Car[] {
// 			new Car("Rusty", 30),
// 			new Car("Clunker", 55),
// 			new Car("Shiny", 90),
// 			new Car("OldTred", 10)
// 		};
// 	}
// 	public IEnumerator GetEnumerator()
// 	{
// 		Reset();
// 		return this;
// 	}
// 	private int enumIndex = -1;
// 	public bool MoveNext()
// 	{
// 		return ++enumIndex < carArray.Length;
// 	}
// 	public object Current
// 	{
// 		get
// 		{
// 			return carArray[enumIndex];
// 		}
// 	}
// 	public void Reset()
// 	{
// 		enumIndex = -1;
// 	}
// 	public IEnumerator GetEnumerator()
// 	{
// 	}
// }
public class Garage// : IEnumerable
{
	Car[] carArray;
	public Garage()
	{
		carArray = new Car[] {
			new Car("Rusty", 30),
			new Car("Clunker", 55),
			new Car("Shiny", 90),
			new Car("OldTred", 10)
		};
	}
	public IEnumerator GetEnumerator()
	{
		foreach (Car car in carArray)
		{
			yield return car;
		}
	}
	public IEnumerable CarsFasterThan(int maxSpeed)
	{
		foreach (Car car in carArray)
		{
			if (car.MaxSpeed >= maxSpeed)
			{
				yield return car;
			}
		}
	}
}


class EnumeratorTest
{
	public static void Main()
	{
		Garage myGarage = new Garage();
		foreach (Car car in myGarage)
		{
			Console.WriteLine("{0}", car);
		}

		foreach (Car car in myGarage.CarsFasterThan(40))
		{
			Console.WriteLine("faster {0}", car);
		}
	}
}