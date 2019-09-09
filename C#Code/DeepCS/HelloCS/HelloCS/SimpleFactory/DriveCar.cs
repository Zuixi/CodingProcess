using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HelloCS.SimpleFactory;
namespace HelloCS.SimpleFactory
{
    public class DriveCar
    {
        // 工厂类角色，返回类型为抽象产品角色
        public static ICar DriveCarMethod(string s)
        {
            if(s.Equals("Benz"))
                return new Benz();
            else if (s.Equals("Audi"))
            {
                return new Audi();
            }
            else if (s.Equals("Bmw"))
            {
                return new Bmw();
            }
            else 
                return null;

        }
    }
}
