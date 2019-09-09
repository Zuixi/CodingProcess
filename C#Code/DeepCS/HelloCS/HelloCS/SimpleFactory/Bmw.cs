using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloCS.SimpleFactory
{
    // 具体产品角色
    public class Bmw:ICar
    {
        public  void drive()
        {
            Console.WriteLine("Drive Bmw Car!");
        }
    }

    public class Benz:ICar
    {
        public void drive()
        {
            Console.WriteLine("Drive Benz car!");
        }
    }

    public class Audi:ICar
    {
        public void drive()
        {
            Console.WriteLine("Drive Audi!");
        }
    }
}
