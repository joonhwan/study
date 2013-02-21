// -*- compile-command:"csc /target:exe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /main:Prog /out:sysinfo.exe SysInfoString.cs SysInfoList.cs  && sysinfo " -*-
using System;

class SysInfoList : Form
{
	SysInfoList()
	{
	}
}

class Prog
{
	public static void Main()
	{
		Form form = new SysInfoList();

		SysInfoString sis;
		float maxLabelWidth = sis.MaxLabelWidth();
		float maxValueWidth = sis.MaxValueWidth();
		Console.WriteLine("sis w:{0}, h:{1}", maxLabelWidth, maxValueWidth);
	}
}