// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:ObserverTest /out:ObserverTest.exe ObserverTest.cs	\
//   && ObserverTest arg1 "arg2""
// End:
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

class Person
{
	public Person(string name, int age)
	{
		this.Name = name;
		this.Age = age;
	}
	public string Name { get; set; }
	public int Age { get; set; }
	public override string ToString()
	{
		return String.Format("Name:{0}, Age:{1}",
							 Name, Age);
	}
}

class People : ObservableCollection<Person>
{
	public People()
	{
		CollectionChanged += LogChange;
	}
	public void LogChange(object sender,
						  System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
	{
		// e.Action -> NotifyCollectionChangedAction.Add/Remove/Replace/Move/Reset..
		Console.WriteLine("CollectionChanged : reason={0}", e.Action.ToString());
		var people = sender as ObservableCollection<Person>;
		foreach (var person in people)
		{
			Console.WriteLine("{0}", person);
		}
	}
}

class ObserverTest
{
	public static void Main()
	{
		var people = new People() {
			new Person("준환", 42),
			new Person("신영", 38),
			new Person("서연", 11),
			new Person("은서", 5)
		};
		foreach (var person in people) {
			Console.WriteLine("{0}", person);
		}

		Console.WriteLine("가족을 추가합니다..");
		people.Add (new Person("가은", 7));

		Console.WriteLine("가족을 삭제합니다..");
		people.RemoveAt(people.Count-1);

		Console.WriteLine("가족을 클리어합니다...");
		people.Clear();
	}
}