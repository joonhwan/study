// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /main:TimerEventTest /out:TimerEventTest.exe *.cs\
//   && TimerEventTest"
// End:
using System;
using System.Timers;
class TimerHandlingClass {
	public void OnElapsed(Object sender, ElapsedEventArgs e) {
		Console.WriteLine("object handled event(data={0}) handled event!", data);
	}
	public int data;
}
class TimerEventTest {
	static void Main() {
		TimerHandlingClass thc = new TimerHandlingClass();
		thc.data = 18; // 객체가 그 객체가 맞는지 확인.
		Timer timer = new Timer();
		timer.Interval = 500;

		// 객체의 멤버함수
		timer.Elapsed += thc.OnElapsed;
		// 익명 메소드(anonymous method) - full version
		timer.Elapsed += delegate (Object sender, ElapsedEventArgs e) {
			Console.WriteLine("Lambda delegator handled event!!!");
		};
		// 익명 메소드 - short version
		timer.Elapsed += delegate {
			Console.WriteLine("Simple Lambda delegator handled event!!!");
		};
		// 정적함수
		timer.Elapsed += TesterHandler;

		timer.Start();
		Console.ReadLine();
	}
	public static void TesterHandler(Object sender, ElapsedEventArgs e) {
		Console.WriteLine("TesterHandler handled event!!!");
	}
}
