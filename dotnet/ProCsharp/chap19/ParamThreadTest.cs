// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll			\
//   /main:ParamThreadTest /out:ParamThreadTest.exe ParamThreadTest.cs	\
//   && ParamThreadTest arg1 "arg2""
// End:
using System;
using System.Threading;

class MyThreadParam
{
    public int a, b;
    public MyThreadParam(int a, int b)
    {
        this.a = a;
        this.b = b;
    }
}

class ParamThreadTest
{
    public static void Add (Object param)
    {
        MyThreadParam mtp = param as MyThreadParam;
        if (mtp!=null)
        {
            Console.WriteLine("{0} + {1} = ...", mtp.a, mtp.b);
            Thread.Sleep(2000);
            Console.WriteLine(".... = {0}", (mtp.a + mtp.b) );
        }
    }

    public static void Main()
    {
        MyThreadParam myParam = new MyThreadParam(10, 40);
        Thread myThread = new Thread(Add);
        myThread.Start(myParam);
        myThread.Join();
    }
}
