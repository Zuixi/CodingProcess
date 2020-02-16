#include <iostream>
#include <thread>
//#include "OverrideFun.h"

class MyTime{
    private:
        int hours;
        int minutes;
        int secondes;
    
    public:
        void show() const
        {
            std::cout << "now time is " << hours << " : " << minutes << " : " << secondes << std::endl;
        }
        MyTime(int h, int m, int s)
        {
            hours = h;
            minutes = m;
            secondes = s;
        }
        MyTime()
        {
            std::cout << " i will do nothing\n";
        }
        int getHours() const
        {
            return hours;
        }
};

void outputsomething()
{
    using namespace std;
    cout << "this is a new thread!" << endl;
    
}

int main()
{
    using namespace std;
    thread m_thread(outputsomething);
    m_thread.join();

    cout << "Hello" << endl;

    MyTime planing(2, 12, 23);
    planing.show();
    cout << "hours of planing is " << planing.getHours() << endl;

    //Time planing;

    /*
    Time planing;
    Time coding(2,23,12);
    Time fixing(3,43,12);
    Time total;

    cout << "planing time = ";
    planing.show();
    cout << endl;

    cout << "coding time = ";
    coding.show();
    cout<< endl;

    cout << "fixing time = ";
    fixing.show();
    cout << endl;

    total = coding.Sum(fixing);
    cout <<"total time = ";
    total.show();
    cout << endl;
     */

    return 0;
}