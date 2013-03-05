// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll			\
//   /main:PracticalDelegateTest /out:PracticalDelegateTest.exe PracticalDelegateTest.cs \
//   && PracticalDelegateTest arg1 "arg2""
// End:
using System;

class Car {
	public Car() {
		speed = 0;
	}
	public int Speed {
		get {
			return speed;
		}
		set {
			Console.WriteLine("speed configured : {0}", value);
			if (speed != value) {
				OnSpeedChanged(speed, value);
				speed = value;
			}
		}
	}
	private int speed;

	// 1. Delegate 정의하기(SpeedChangeHandler 라는 클래스가 만들어진다)
	public delegate void SpeedChangeHandler(int beforeSpeed, int afterSpeed);
	// 2. Delegate 객체 정의하기(private 필드 + 접근메소드)
	private SpeedChangeHandler speedChangeHandler;
	public void RegisterSpeedChangeHandler(SpeedChangeHandler handler) {
		speedChangeHandler += handler;
	}
	public void UnregisterSpeedChangeHandler(SpeedChangeHandler handler) {
		speedChangeHandler -= handler;
	}
	// 3. 어떤 상황에서 호출되어 Delegate를 호출하는 함수 만들기.
	public virtual void OnSpeedChanged(int beforeSpeed, int afterSpeed) {
		if (speedChangeHandler != null) {
			speedChangeHandler(beforeSpeed, afterSpeed);
		}
	}
}

class PracticalDelegateTest {
	// 4. 핸들러 만들기
	public static void LogSpeedChange(int beforeSpeed, int afterSpeed) {
		Console.WriteLine("speed change : {0} --> {1}", beforeSpeed, afterSpeed);
	}
	public static void Main() {
		Car tucson = new Car();

		tucson.Speed = 10;
		// 5. 핸들러 등록하기
		Car.SpeedChangeHandler handler = new Car.SpeedChangeHandler(LogSpeedChange);
		tucson.RegisterSpeedChangeHandler(handler);

		tucson.Speed = 20;
		tucson.Speed = 30;

		// 5.1 핸들러 등록 해제하기
		tucson.UnregisterSpeedChangeHandler(handler);

		tucson.Speed = 40;
	}
}