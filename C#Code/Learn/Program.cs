using System;
using System.Threading.Tasks;


namespace Learn
{
    
    class Program
    {
        public static char PathSperator{get{return '/';}}
        static void Main(string[] args)
        {

            Task t1 = Task.Run(() =>
            {
                for(int i = 0; i < 10; i++)
                {
                    Console.WriteLine("i is " + i);
                    System.Threading.Thread.Sleep(1000);
                }

            });

            Console.WriteLine("T1: " + t1.Status);
            System.Threading.Thread.Sleep(10);
            Console.WriteLine("t1: " + t1.Status);
            Task.WaitAll(t1);

            Task t2 = Task.Factory.StartNew(() =>
            {
                for(int i = 0; i < 10; i++)
                {
                    Console.WriteLine("ii is " + i);
                    System.Threading.Thread.Sleep(1000);
                }
            });
            
              
        }
        public static void SetDisplayName(ref string pathName)
        {
            if(pathName.EndsWith(PathSperator))
            {
                
            }
            
        }
    }
}
