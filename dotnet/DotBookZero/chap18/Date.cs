// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /main:InheritTest /out:InheritTest.exe *.cs\
//   && InheritTest"
// End:
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

class Date
{
	public Date()
	{
	}
	public Date(int year, int month, int day)
	{
		Year = year;
		Month = month;
		Day = day;
	}
	// public prop
	public int Year
	{
		set
		{
			if (!IsConsistent(value, Month, Day))
				throw new ArgumentOutOfRangeException("Year");
			year = value;
		}
		get
		{
			return year;
		}
	}
	public int Month
	{
		set
		{
			if (!IsConsistent(Year, value, Day))
				throw new ArgumentOutOfRangeException("Month");
			month = value;
		}
		get
		{
			return month;
		}
	}
	public int Day
	{
		set
		{
			if (!IsConsistent(Year, Month, value))
				throw new ArgumentOutOfRangeException("Day");
			day = value;
		}
		get
		{
			return day;
		}
	}
	static bool IsConsistent(int year, int month, int day)
	{
		if ( (year < 1)
			 || (month < 1 || month > 12)
			 || (day < 1 || day > 31)
			 || (day == 31 && (month==4 || month==6 || month==9 || month==11))
			 || (day > 29 && month==2)
			 || (day == 29 && month==2 && !IsLeapYear(year)) )
		{
			return false;
		}
		return true;
	}
	public static bool IsLeapYear(int year)
	{
		return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
	}
	static int[] daysCumulative = {
		0,  31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
	};
	public int DayOfYear()
	{
		return daysCumulative[Month-1] + Day + (Month > 2 && IsLeapYear(Year) ? 1 : 0);
	}
	static string [] strMonths = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
	};
	public override string ToString()
	{
		return String.Format("{0}/{1}/{2}", Year, strMonths[Month-1], Day);
	}

	public int this[string str]
	{
		get
		{
			switch (str.ToLower())
			{
			case "year":
				return Year;
			case "month":
				return Month;
			case "day":
				return Day;
			default:
				throw new ArgumentOutOfRangeException("index = " + str);
			}
		}
		set
		{
			switch(str.ToLower())
			{
			case "year":
				Year = value;
				break;
			case "month":
				Month = value;
				break;
			case "day":
				Day = value;
				break;
			default:
				throw new ArgumentOutOfRangeException("index = " + str);
			}
		}
	}

	// private field
	int year = 1;
	int month = 1;
	int day = 1;
}
