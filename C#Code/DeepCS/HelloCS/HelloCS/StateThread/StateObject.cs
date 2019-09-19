using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
namespace HelloCS.StateThread
{
    public class StateObject
    {
        private int state = 3;
        public void StateChange(int loop)
        {
            if(state == 5)
            {
                state++;
                // 使用断言判断是否=5
                Trace.Assert(state == 6, "race condition occured after " + loop + " loops");
            }
            state = 5;
        }
    }

    public class SampleTask
    {
        public void RaceCondition(object obj)
        {
            Trace.Assert(obj is StateObject, "obj must a StateObject instance");
            StateObject sobj = obj as StateObject;

            int i = 0;
            while(true)
            {
                // 方法一，锁定sobj，防止竞争现象发生
                lock(sobj)
                {
                    sobj.StateChange(i++);
                }
            }
        }
    }
}
