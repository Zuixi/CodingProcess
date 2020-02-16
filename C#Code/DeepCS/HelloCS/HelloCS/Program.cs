
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HelloCS.TemplateDe.TNullableDe;
using HelloCS.MathOperations.Math;
using HelloCS.SimpleFactory;
using HelloCS.ThreadDeep.DataStore;
using System.Threading;
using HelloCS.StateThread;
namespace HelloCS
{
    class Program
    {
      
        // 使用委托调用这个函数
        public static void ThreadMain()
        {
            Console.WriteLine("This is a sub Thread and started!");
            Thread.Sleep(3000);
            Console.WriteLine("sub Thread ended");
        }

        // 用于测试线程传递数据
        public static void ThreadDataSend(object parameter)
        {
            // 类型转换
            DataThread obj = parameter as DataThread;
            Console.WriteLine("Running in a thread,receiving a parameter {0}", obj.message);
        }

        static void JobForAThread(object state)
        {
            for ( int i = 0; i < 3; i++)
            {
                Console.WriteLine("loop{0},runing thread in a pool {1}",i,Thread.CurrentThread.ManagedThreadId);
                Thread.Sleep(50);
            }
        }

        static void Main(string[] args)
        {
            /*
            TemplateDe.TNullableDe.Nullable<int> x;
            x = 4;
            // x += 3;

            if (x.HasValue)
            {
                int y = x.Value;
                Console.WriteLine("if value of x is true; y = " + y.ToString());
            }

            // 测试简单工厂模式

            Magnate magnate = new Magnate();
            */
            char[][] grid = { {'1' },{'1' } };

            var threadOne = new Thread(ThreadMain);
            threadOne.Start();
            Console.WriteLine("ThreadMain is completed!");

            // 线程传递数据
            DataThread oData = new DataThread { message = "Hello", count = 1 };
            var threadReceiveData = new Thread(ThreadDataSend);
            threadReceiveData.Start(oData);
            Console.WriteLine("data received!");

            MyThread mythread = new MyThread("newthread", 12.2);

            var threadClass = new Thread(mythread.ThreadMain);
            threadClass.Start();

            // 判断是否是前台线程还是后台线程
            var bgThread = new Thread(ThreadMain) { Name = "My New Thread", IsBackground = true };
            bgThread.Start();
            Console.WriteLine("Hello, Main Thread completed!");

            int nWorkThreadMax = 0;
            int nCompletePortThreads = 0;
            // 获取最大线程数
            ThreadPool.GetMaxThreads(out nWorkThreadMax, out nCompletePortThreads);
            Console.WriteLine("Max work Thread sum = {0}" + "IO complete sum = {1}", nWorkThreadMax,nCompletePortThreads);

            for (int i = 0; i <5;i++)
            {
                ThreadPool.QueueUserWorkItem(JobForAThread);
            }

            Thread.Sleep(2000);

            // 判断线程中的竞争条件
            var shareStateObj = new StateObject();

            // 10个线程共享一个数据变量
            for (int i = 0; i < 10; i++)
            {
                new Task(new SampleTask().RaceCondition, shareStateObj).Start();
            }

            Thread.Sleep(1000);



            Console.ReadKey(true);
        }

        // leetcode 200

        public int NumIslands(char[][] grid)
        {

            // nothing return 0
            if (grid.GetLength(0) == 0 || grid[0].GetLength(0) == 0)
                return 0;

            int m = grid.GetLength(0), n = grid[0].GetLength(0), islandCount = 0;
            int[] dirX = { -1, 0, 1, 0 };
            int[] dirY = { 0, 1, 0, -1 };

            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {

                    if (grid[i][j] == '0' || grid[i][j] == '2') continue;
                    islandCount++;

                    Queue<int> q = new Queue<int>();
                    q.Enqueue(i * n + j);
                    while (q.Count > 0)
                    {
                        int t = q.Dequeue();
                        for (int k = 0; k < 4; k++)
                        {
                            int x = t / n + dirX[k], y = t % n + dirY[k];
                            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == '0' || grid[x][y] == '2') continue;
                            grid[x][y] = '2';
                            q.Enqueue(x * n + y);
                        }
                    }
                }
            }
            return islandCount;
        }
    
            }

    }
}
