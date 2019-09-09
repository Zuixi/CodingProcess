//
// Created by wqz on 2019/6/16.
//

#include "test.h"
#include <cmath>
void showDifferentofDoubleAndFloat(){
    using  namespace std;
    cout.setf(ios_base::fixed,ios_base::floatfield);

    double  tub = 10.0 / 3.0;
    float mint = 10.0 / 3.0;

    cout << "as cout will print 6 point ,so tub is same with mint: ";
    cout << "is mint same with tub? " << (mint == tub) << endl;

    const  float million = 1e6;
    cout << "both mint and tub mutiply million ,will them still same?"<<endl;
    cout << "tub * million = " << tub * million<<endl;
    cout << "mint * million = " << mint * million << endl;
    cout << "as you see ,float and double is not same!" << endl;

    cout << "all is end!" << endl;
}

void showCarrots(){
    using namespace std;
    int carrots = 0;
    cout << "How many carrots do you have?" << endl;
    cin >> carrots;
    cout << "Here are " << carrots << " carrots!" << endl;
    carrots += 2;
    cout << "Now you have " << carrots << " carrots!" << endl;
}


void  showUnicodeChar(){
    using namespace std;

    cout << "test unicode char set with simple instance" << endl;

    cout << "let's them eat g\u00E2teau.\n";
    cout << "different char after g ,as you see!"<< endl;

}

void showArea(){
    using namespace std;
    double  area;
    cout << "Enter your area of your home in square: ";
    cin >> area;
    double  side;
    side = sqrt(area);
    cout << "That's the equipment of a square: " << side
         << "feet to the side!" << endl;
    cout << "how fascinating!"<<endl;
}

void showSwitch(){
    using namespace std;

    cout << "Enter color code (0-6)：";
    int code;

    cin >> code;

    while (code >= red &&  code <= indigo){

        switch (code){
            case red:
                cout << " her lips were red!"<< endl;
                break;
            case orange:
                cout << "her lips were orange!"<<endl;
                break;
            case yellow:
                cout << "her lips were yellow!"<<endl;
                break;
            case violet:
                cout << "her lips were violet"<<endl;
                break;
        }
    }

}




