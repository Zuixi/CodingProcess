
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HelloCS.TemplateDe.TNullableDe;
using HelloCS.MathOperations.Math;
using HelloCS.SimpleFactory;
namespace HelloCS
{
    class Program
    {
      


       
        static void Main(string[] args)
          {
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
        }

    }
}
