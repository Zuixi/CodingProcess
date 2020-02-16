#include "OverrideFun.h"

Time::Time()
{
    hours = minutes = seconds = 0;
}

Time::Time(int h, int m, int s)
{
    hours = h;
    minutes = m;
    seconds = s;
}

void Time::AddMin(int m)
{
    minutes += m;
    hours += minutes / 60;
    minutes %= 60;
}

void Time::AddHr(int h)
{
    hours += h;
}

void Time::Reset(int h, int m, int s)
{
    hours = h;
    minutes = m;
    seconds = s;
}

Time Time::Sum(const Time & t) const
{
    Time sum;
    sum.seconds = seconds + t.seconds;
    sum.minutes = minutes + t.minutes + sum.seconds / 60;
    sum.hours = hours + t.hours + sum.minutes / 60;
    sum.minutes %= 60;
    sum.seconds %= 60;
    return sum;

}

void Time::show() const{
    std::cout << hours << "hours ：" << minutes << "minutes : " << seconds << "seconds." << std::endl;
}

