#include <thread>
#include <iostream>
#include <string>

void fun()
{
    using namespace std;
    cout << "Hello world!!!"<< endl;

}

int main()
{
    using namespace std;
    
    thread TestFun(fun);

    TestFun.join();

    cout << "Hello ,Main thread" << endl;

    return 0;
}