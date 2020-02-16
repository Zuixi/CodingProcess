using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MultiThreadLearning.TaskProcess
{
    class SimpleTask
    {
        public static void TestSimple()
        {
            Task<Int32> t = new Task<Int32>(n => Sum((Int32)n),1000000000);

            t.Start();    // 或许现在开始，或许以后执行

            t.Wait();    // 使用wait显示等待线程完成

            Console.WriteLine("The Sum is: " + t.Result);

        }

        private static Int32 Sum(Int32 i)
        {
            Int32 sum = 0;

            for(; i > 0; i--)
            {
                checked { sum += i; }
            }

            return sum;
        }
    }
}
