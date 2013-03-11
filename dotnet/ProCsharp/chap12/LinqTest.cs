// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:LinqTest /out:LinqTest.exe LinqTest.cs				\
//   && LinqTest arg1 "arg2""
// End:
using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;

public struct ProductInfo
{
	public string Name { get; set;}
	public string Description { get; set;}
	public int Weight { get; set;}
	public ProductInfo(string name, string desc, int weight)
		: this ()
	{
		Name = name; Description = desc; Weight = weight;
	}
	public override string ToString()
	{
		return string.Format("Name:{0}, Desc:{1}, Weight:{2}");
	}
}

class LinqTest
{
	public static Array GetLinqVar(ProductInfo[] pi)
	{
		return (from p in pi
				where p.Weight > 13
				select new
					{
						p.Name,
						p.Description
					}).ToArray();
	}
	public static void Main()
	{
		ProductInfo[]  pi = new ProductInfo[] {
			new ProductInfo("제품1", "첫제품이다", 11),
			new ProductInfo("제품2", "<제품이다", 12),
			new ProductInfo("제품A", "OP제품이다", 13),
			new ProductInfo("제품B", "LKJ제품이다", 14),
			new ProductInfo("제품C", "jasdf제품이다", 15),
		};

		foreach (var v in GetLinqVar(pi))
		{
			Console.WriteLine(v);
		}

		// LINQ Enumerable 의 확장메소드를 사용해 보기

		// - 확장 메소드 Reverse<T>()
		// 추가 사용예로
		//    - 인덱스를 포함하여 select하기
		//    - 명시적으로 Linq 의 IEnumerable<T>.Select() 함수 쓰기
		var result = (from p in pi where p.Weight <= 12
					  select p).ToArray();
		foreach (var prod in result.Select ((p, index) =>
											new {
												Index = index,
												Name = p.Name,
											}).Reverse())
		{
			Console.WriteLine(prod);
		}

		List<string> myCars = new List<String> { "Yugo", "Aztec", "BMW" }; 
		List<string> yourCars = new List<String> { "BMW", "Saab", "Aztec" };

		// - 확장 메소드 Except(), Union(), Intersect(), Concat(), Distinct()
		//   --> 서연이가 발표한 벤 다이어그램 !!!!
		var allMyCar = (from car in myCars select car);
		var allYourCars = (from car in yourCars select car);

		var concatUniqueCar = allMyCar.Concat(allYourCars).Distinct();
		PrintAll("concatUnique", concatUniqueCar);
		
		var carUnion = allMyCar.Union(allYourCars);
		PrintAll("union", carUnion);

		var carIntersect = allMyCar.Intersect(allYourCars);
		PrintAll("intersect", carIntersect);

		var carExceptYours = allMyCar.Except(allYourCars);
		PrintAll("Mine except Yours", carExceptYours);
	}
	public static void PrintAll(string desc, IEnumerable enumurable)
	{
		Console.WriteLine("\nPrinting [{0}] {1}...",
						  desc, enumurable.GetType());
		foreach (var item in enumurable)
		{
			Console.WriteLine(item);
		}
	}
}