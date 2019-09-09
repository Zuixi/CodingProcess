using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloCS.SimpleFactory
{
    // 抽象产品角色，一般为接口或者类
    public interface ICar
    {
         // 这里的drive函数不能够使用public或者private等属性不然会报错
         void drive();
    }
}
