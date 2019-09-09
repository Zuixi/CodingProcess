using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloCS.SimpleFactory
{
    public class Magnate
    {
        public Magnate()
        {
            ICar car = DriveCar.DriveCarMethod("Benz");
            car.drive();
        }
    }
}
