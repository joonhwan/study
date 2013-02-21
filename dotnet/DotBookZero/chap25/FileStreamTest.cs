// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /main:FileStreamTest /out:FileStreamTest.exe *.cs\
//   && FileStreamTest \"./FileStreamTest.exe\""
// End:
using System;
using System.IO;
using System.Net;

public class HexDumper
{
	public bool Dump()
	{
		try
		{
			using (FileStream fs = new FileStream(this.FilePath,
												  FileMode.Open,
												  FileAccess.Read,
												  FileShare.Read))
			{
				DumpStream(fs);
				return true;
			}
		}
		catch (Exception e)
		{
			Console.WriteLine("Exception has been caught : {0}", e.GetType());
			return false;
		}
	}
	static void DumpStream(Stream stream)
	{
		byte [] buffer = new byte[16];
		long address = 0;
		int count = 0;

		while ((count = stream.Read(buffer, 0, buffer.Length))>0)
		{
			Console.WriteLine(ComposeLine(address, buffer, count));
			address += buffer.Length;
		}
	}
	static string ComposeLine(long address, byte[] buffer, int count)
	{
		string line = String.Format("{0:X4}-{1:X4}   ", (uint)address / 0xFFFF, (ushort)address);
		for(int i = 0; i < buffer.Length; ++i)
		{
			line += (i < count) ? String.Format("{0:X2}", buffer[i]) : "  ";
			line += (i == 7 && count > 7) ? " - " : " ";
		}
		line += " ";

		for (int i = 0; i < buffer.Length; ++i)
		{
			char ch = (i < count) ? Convert.ToChar(buffer[i]) : ' ';
			line += Char.IsControl(ch) ? "?" : ch.ToString();
		}
		return line;
	}

	public string FilePath
	{
		set
		{
			filePath = value;
		}
		get
		{
			return filePath;
		}
	}
	string filePath;
}

class FileStreamTest
{
	// public static void Main(string[] args)
	// {
	// 	Console.WriteLine("FileTesting : arg = {0}", args.Length > 0 ? args[0] : "???");
	// 	if (args.Length > 0)
	// 	{
	// 		HexDumper dumper = new HexDumper();
	// 		dumper.FilePath = "UnknownFile.exe"; // args[0];
	// 		if (!dumper.Dump())
	// 		{
	// 			Console.WriteLine("Failed to dump file!");
	// 		}
	// 	}
	// }
	public static int Main()
	{
		// Console.WriteLine("{0:#,#}", 148813);
		HtmlDumpTest();

		return 0;
	}

	public static void HtmlDumpTest()
	{
		WebRequest request;
		WebResponse response;

		try
		{
			request = WebRequest.Create(@"https://raw.github.com/joonhwan/dotEmacs/master/my-cc-mode.el");
			response = request.GetResponse();
		} catch (Exception e)
		{
			Console.WriteLine("HtmlDump: {0}", e.Message);
			return;
		}

		if (response.ContentType.Substring(0, 4) != "text")
		{
			Console.WriteLine("HtlmDump: Not a text type response!");
			return;
		}

		Stream stream = response.GetResponseStream();
		StreamReader reader = new StreamReader(stream);
		string line;
		int lineNo = 0;
		while ((line = reader.ReadLine()) != null)
		{
			Console.WriteLine("{0:D4}: {1}", lineNo++, line);
		}
		stream.Close();
		return;
	}
}