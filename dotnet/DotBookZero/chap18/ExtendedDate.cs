using System;
using System.Reflection;
using System.Diagnostics;
using System.Runtime.InteropServices;

class ExtendedDate : Date
{
	public ExtendedDate()
	{
	}
	public ExtendedDate(int aYear, int aMonth, int aDay)
		: base (aYear, aMonth, aDay)
	{
	}
	public int CommonEraDay
	{
		get
		{
			return DaysBeforeYear() + DayOfYear();
		}
	}
	int DaysBeforeYear()
	{
		int yv = Year - 1;
		return (int)(365.25m * yv) - yv/100 + yv/400;
	}
}