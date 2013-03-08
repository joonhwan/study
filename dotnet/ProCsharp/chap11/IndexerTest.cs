// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:IndexerTest /out:IndexerTest.exe IndexerTest.cs 	\
//   && IndexerTest arg1 "arg2""
// End:
using System;

public interface ICategoryKeyValueProvider
{
	string this[string aCategory, string aKey] { get; set; }
}
      
public class SomeContainer : ICategoryKeyValueProvider 
{
	// ICategoryKeyValueProvider 인터페이스의 메소드 정의
	public string this[string aCategory, string aKey] {
		get { return string.Format("카테고리:{0} 키:{1} 의 값", aCategory, aKey); }
		set { Console.WriteLine(@"카테고리:{0} 키:{1} 의 값을 ""{2}""로 설정", aCategory, aKey, value); }
	}
	// 읽기 전용 인덱서
	public int this[int row, int col] {
		get { return row * 1000 + col; }
	}
	// 문자열을 인자로 받는 덱서
	public int this[string rowColExpr] {
		get { return this[Convert.ToInt32(rowColExpr.Substring(1,2)),
						  Convert.ToInt32(rowColExpr.Substring(4,2))]; }
		set { Console.Write("{0}의 값을 {1}로 설정합니다.", rowColExpr, value); }
	}
}
      
class IndexerTest {
	public static void Main() {
		SomeContainer c = new SomeContainer();
		Console.WriteLine("c[18,17]={0}", c[18,17]);
		Console.WriteLine("c[\"1817\"]={0}", c["r18c17"]);
		c["r19c20"] = 1004;

		Console.WriteLine("사업아이템-3차원프린터의 값: {0}", c["사업아이템", "3차원프린터"]);
		c["배사장회사", "업무지원"] = "만빵";
	}
}