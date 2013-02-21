using System;

public class CsDatePlus : CsDate
{
	public CsDatePlus()
	{
	}
	public void printPretty()
	{
		Console.WriteLine("Year:{0}, Month:{1}, Day:{2}",
						  m_year, m_month, m_day);
	}
}