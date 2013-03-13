// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:MyLazyTest /out:MyLazyTest.exe MyLazyTest.cs			\
//   && MyLazyTest arg1 "arg2""
// End:
using System;
using System.Threading;

// Represents all songs on a player. 
class AllTracks {
	public AllTracks() : this (100) {
	}
	public AllTracks(int maxTracks) : base () { 
		// Assume we fill up the array of Song objects here.
		Console.WriteLine("트랙 {0} 생성중...", maxTracks);
		Thread.Sleep(10 * maxTracks);
	} 
} 

// The MediaPlayer has-an AllTracks object.
class MediaPlayer {
	private AllTracks allSongs = new AllTracks();
	public AllTracks GetAllTracks() { 
		// Return all of the songs. 
		return allSongs; 
	}
}

class LazyMediaPlayer { 
	private Lazy<AllTracks> allSongs = new Lazy<AllTracks>(); 
	public AllTracks GetAllTracks() { 
		// Return all of the songs. 
		return allSongs.Value; 
	}
}

class LazyBigMediaPlayer {
	private Lazy<AllTracks> allSongs = new Lazy<AllTracks>( () =>
		{
			Console.WriteLine("명시적 생성자를 호출중..");
			return new AllTracks(500);
		}
		);
	public AllTracks GetAllTracks() { 
		// Return all of the songs. 
		return allSongs.Value; 
	}
}

class MyLazyTest
{
	public static void Print(string msg)
	{
		Console.WriteLine(DateTime.Now + ": " + msg);
	}
	public static void NonLazyTest()
	{
		Print("Non-Lazy Player 생성시작.");
		MediaPlayer player = new MediaPlayer();
		Print("Non-Lazy Player 생성완료.");
		AllTracks yourMusic = player.GetAllTracks();
		Print("Non-Lazy Player 트랙정보확인완료");
		Print("");
	}
	public static void NonBigLazyTest()
	{
		Print("Non-Big-Lazy Player 생성시작.");
		LazyBigMediaPlayer player = new LazyBigMediaPlayer();
		Print("Non-Big-Lazy Player 생성완료.");
		AllTracks yourMusic = player.GetAllTracks();
		Print("Non-Big-Lazy 트랙정보확인완료");
		Print("");
	}
	public static void LazyTest()
	{
		Print("Lazy Player 생성시작.");
		LazyMediaPlayer player = new LazyMediaPlayer();
		Print("Lazy Player. 생성완료.");
		AllTracks yourMusic = player.GetAllTracks();
		Print("Lazy Player. 트랙정보확인완료");
		Print("");
	}
	public static void Main()
	{
		NonLazyTest();
		LazyTest();
		NonBigLazyTest();
	}
}