
#ifndef MYTIME_H
#define MYTIME_H

#include <iostream>
#include <string>
#include <vector>

class Time
{
    private:
        int hours;
        int minutes;
        int seconds;
    
    public:
        Time();
        Time(int h, int m, int s);
        void AddMin(int m);
        void AddHr(int h);
        void Reset(int h = 0, int m = 0, int s = 0);
        Time Sum(const Time& t) const;
        void show() const;
};


#endif
