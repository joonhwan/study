using System;

public class CsDate
{
    public CsDate()
    {
		m_year = 1930;
		m_month = 8;
		m_day = 30;
    }

	public static bool isLeapYear(int year)
	{
		return (year % 4 == 0) && ((year % 100 !=0) || (year % 400 == 0));
	}
	public int dayOfYear
	{
		get
		{
			return monthDays[month-1] + day + ((month > 2) && isLeapYear(year) ? 1 : 0);
		}
	}

	public int year
	{
		set
		{
			Console.WriteLine("set year {0}..", value);
			m_year = value;
		}
		get
		{
			Console.WriteLine("get year as {0}...", m_year);
			return m_year;
		}
	}
	public int month
	{
		set
		{
			if (value > 12)
			{
				value = 12;
			}			Console.WriteLine("set month {0}..", value);
			m_month = value;
		}
		get
		{
			Console.WriteLine("get month as {0}...", m_month);
			return m_month;
		}
	}
	public int day
	{
		set
		{
			Console.WriteLine("set day {0}..", value);
			m_day = value;
		}
		get
		{
			Console.WriteLine("get day as {0}...", m_day);
			return m_day;
		}
	}
	public void print()
	{
		Console.WriteLine("{0}/{1}/{2}", m_year, m_month, m_day);
	}
	protected int m_year;
	protected int m_month;
	protected int m_day;
	static int [] monthDays = new int[] { 0,    31,  59,  90, 120, 151,
										  181, 212, 243, 273, 304, 334 };

	static void Main()
	{
		try
		{
			CsDatePlus date = new CsDatePlus();
			date.print();

			date.year = 1971;
			date.month = 11;
			date.month += 2;
			date.day = 11;
			date.print();
			date.printPretty();
			Console.WriteLine("the day of year was {0}", date.dayOfYear);
		}
		catch (IndexOutOfRangeException exc)
		{
			Console.WriteLine("You idiot!. Out of range excpetion!");
			Console.WriteLine(exc);
		}
		catch (Exception exc)
		{
			Console.WriteLine(exc);
			Console.WriteLine("General Exception.");
		}
	}
}
