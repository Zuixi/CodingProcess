using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MultiThreadLearning.TaskProcess;

namespace MultiThreadLearning
{
    class Program
    {
        static void Main(string[] args)
        {

            System.Threading.CancellationTokenSource cts = new System.Threading.CancellationTokenSource();
            //Task<Int32> t = new Task<Int32>(n => Sum((Int32)n), 1000000000);

            Task<Int32> t = new Task<Int32>(() => Sum(cts.Token, 10000), cts.Token);
            t.Start();    // 或许现在开始，或许以后执行

            t.Wait();    // 使用wait显示等待线程完成
;
            cts.Cancel();

            try
            {
                Console.WriteLine("sum is: " + t.Result);
            }
            catch (AggregateException e)
            {
                //e.Handle(e => e is OperationCanceledException);
                Console.WriteLine("Sum was cancelled");
            }
            Console.WriteLine("The Sum is: " + t.Result);
            Console.WriteLine("main is over");
            Console.ReadLine();
        }

        public static void TestSimple()
        {
            Task<Int32> t = new Task<Int32>(n => Sum((Int32)n), 1000000000);

            t.Start();    // 或许现在开始，或许以后执行

            t.Wait();    // 使用wait显示等待线程完成

            Console.WriteLine("The Sum is: " + t.Result);

        }

        private static Int32 Sum(System.Threading.CancellationToken cst, Int32 i)
        {
            Int32 sum = 0;

            for (; i > 0; i--)
            {
                // if cancel, throw a exception
                cst.ThrowIfCancellationRequested();
                checked { sum += i; }
            }

            return sum;
        }
        private static Int32 Sum(Int32 i)
        {
            Int32 sum = 0;

            for (; i > 0; i--)
            {
                checked { sum += i; }
            }

            return sum;
        }
    }
}
