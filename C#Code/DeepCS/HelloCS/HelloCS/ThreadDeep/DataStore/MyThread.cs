using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
namespace HelloCS.ThreadDeep.DataStore
{
    public class MyThread
    {
        private string message;
        private double time;

        public MyThread(string message,double time)
        {
            this.message = message;
            this.time = time;
        }
        public MyThread(string message)
        {
            this.message = message;
        }
        public MyThread(double time)
        {
            this.time = time;
        }
        public MyThread()
        { }

        // 用来实现在线程中传递数据
        public void ThreadMain()
        {
            Console.WriteLine("parameter in this object is {0},{1}", this.message, this.time);
        }
    }
}
